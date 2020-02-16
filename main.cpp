#include <iostream>
#include <csignal>
#include <mutex>

import http;

std::mutex m;

int main() {
   printf("Started\n");
   Http server = {};
   server.Start(8080);
   printf("Listening on 8080\n");
   std::signal(SIGTERM, [](int s) { m.unlock(); });
   std::signal(SIGINT, [](int s) { m.unlock(); });
   m.lock();

   m.lock();
   printf("SIGTERM received, stopping\n");
   server.Stop();
   printf("Stoped\n");
}
