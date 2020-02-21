#include <time.h>

#include <csignal>
#include <functional>
#include <iostream>
#include <mutex>

import http;
import storage;

std::mutex m;

int main() {
  auto log = [](std::string msg) {
    time_t now = time(NULL);
    printf("[%.19s] %s\n", ctime(&now), msg.c_str());
  };
  log("Started");
  Http server(8080, log);
  Storage db("/tmp/db", log);
  server.Start();
  std::signal(SIGTERM, [](int) { m.unlock(); });
  std::signal(SIGINT, [](int) { m.unlock(); });
  m.lock();

  m.lock();
  log("SIGTERM received, stopping");
  server.Stop();
  db.Close();
  log("Stoped");
}
