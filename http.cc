#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>

export module http;

export class Http {
public:
  Http(int port, std::function<void(std::string)> log) : port(port), log(log) {}

  void Start() {
    log("Openning socket on port " + std::to_string(port));
    sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock > 0 && "Socket creation");
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    assert(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0 &&
           "Socket bind");
    assert(listen(sock, SOMAXCONN) == 0 && "Socket listen");
    t = std::thread(startAccepting, sock);
  }

  void Stop() {
    log("Closing socket");
    close(sock);
    t.join();
  }

private:
  int sock;
  int port;
  std::thread t = {};
  std::function<void(std::string)> log;

  static void startAccepting(int sock) {
    sockaddr_in client_addr{};
    socklen_t client_len;
    while (true) {
      int con = accept(sock, (struct sockaddr *)&client_addr, &client_len);
      std::string resp = "HTTP/1.1 200 OK\nContent-Length: 0\n\n";
      write(con, resp.c_str(), resp.size());
      if (con == -1) {
        return;
      }
      close(con);
    }
  }
};
