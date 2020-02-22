#include <time.h>

#include <csignal>
#include <functional>
#include <iostream>
#include <mutex>

import http;
import storage;
import kafka;

using std::string;

std::mutex m;

string env(string name, string fallback) {
  string val(std::getenv(name.c_str()));
  return val.empty() ? fallback : val;
}

int main() {
  auto log = [](string msg) {
    time_t now = time(NULL);
    printf("[%.19s] %s\n", ctime(&now), msg.c_str());
  };
  log("Started");
  Http server(8080, log);
  Storage db("/tmp/db", log);
  Kafka kafka(log, log);
  kafka.Start(env("KAFKA", "kafka:9092"), "client-1", "topic-1");
  server.Start();
  std::signal(SIGTERM, [](int) { m.unlock(); });
  std::signal(SIGINT, [](int) { m.unlock(); });
  m.lock();

  m.lock();
  log("SIGTERM received, stopping");
  server.Stop();
  kafka.Stop();
  db.Close();
  log("Stoped");
}
