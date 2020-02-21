#include <cassert>
#include <cstdio>
#include <functional>
#include <string>

#include "librdkafka/rdkafkacpp.h"

export module kafka;

export class Kafka {
public:
  Kafka(std::string server, std::string id,
        std::function<void(std::string)> log) {
    auto config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    auto conf = [&config, &log](std::string key, std::string val) {
      std::string err;
      if (config->set(key, val, err) != RdKafka::Conf::CONF_OK) {
        log("Error configuring Kafka: " + err);
        assert(0 && "Kafka configuration error");
      }
    };
    conf("bootstrap.servers", server);
    conf("group.id", id);
    conf("auto.offset.reset", "earliest");
    conf("queued.max.messages.kbytes", "100000");
    log("Kafka server " + server + ":" + id);
  }
};
