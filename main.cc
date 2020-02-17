#include <iostream>
#include <csignal>
#include <mutex>
#include <time.h>

import http;

std::mutex m;

int main() {
  auto log = [](std::string msg) {
    time_t now = time(NULL);
    printf("[%.19s] %s\n", ctime(&now), msg.c_str());
  };
  log("Started");
  Http server(8080, log);
  server.Start();
  std::signal(SIGTERM, [](int s) { m.unlock(); });
  std::signal(SIGINT, [](int s) { m.unlock(); });
  m.lock();

  m.lock();
  log("SIGTERM received, stopping");
  server.Stop();
  log("Stoped");
}
