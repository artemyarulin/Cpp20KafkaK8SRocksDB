#include <atomic>
#include <cassert>
#include <cstdio>
#include <functional>
#include <map>
#include <string>
#include <thread>

#include "librdkafka/rdkafkacpp.h"

export module kafka;

using std::string, std::function;

export class Kafka {
public:
  Kafka(function<void(string)> log, function<void(string)> onMsg)
      : log(log), onMsg(onMsg) {}

  void Start(string server, string id, string topic) {
    log("Kafka consumer starting " + server + ":" + id);
    consumer = configure(topic, std::map<string, string>{
                                    {"bootstrap.servers", server},
                                    {"group.id", id},
                                    {"auto.offset.reset", "earliest"},
                                    {"queued.max.messages.kbytes", "100000"}});
    t = std::thread(&Kafka::startConsuming, this);
  }

  void Stop() {
    keepWorking = false;
    t.join();
    consumer->close();
  }

private:
  function<void(string)> log;
  function<void(string)> onMsg;
  std::thread t = {};
  std::unique_ptr<RdKafka::KafkaConsumer> consumer;
  std::atomic<bool> keepWorking = true;

  std::unique_ptr<RdKafka::KafkaConsumer>
  configure(string topic, std::map<string, string> options) {
    string err;
    auto config = std::unique_ptr<RdKafka::Conf>(
        RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    for (auto [k, v] : options) {
      if (config->set(k, v, err) != RdKafka::Conf::CONF_OK) {
        log("Error configuring Kafka: " + err);
        assert(!"Kafka configuration error");
      }
    }
    auto consumer = std::unique_ptr<RdKafka::KafkaConsumer>(
        RdKafka::KafkaConsumer::create(config.get(), err));
    if (!consumer) {
      log("Error creating consumer: " + err);
      assert(!"Kafka configuration error");
    }
    auto subsErr = consumer->subscribe(std::vector<string>{topic});
    if (subsErr) {
      log("Error subscribing consumer: " + RdKafka::err2str(subsErr));
      assert(!"Kafka configuration error");
    }
    return consumer;
  }

  void startConsuming() {
    while (keepWorking) {
      auto msg = std::unique_ptr<RdKafka::Message>(consumer->consume(500));
      switch (msg->err()) {
      case RdKafka::ERR__TIMED_OUT:
        log("Kafka timeout");
        break;
      case RdKafka::ERR_NO_ERROR:
        onMsg("ok");
        log("Kafka no error");
        break;
      default:
        log("Error in kafka consumer: " + msg->errstr());
      }
    }
  }
};
