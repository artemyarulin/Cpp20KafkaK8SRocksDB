#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <thread>
#include <cassert>

export module http;

export class Http {
public:
    void Start(int port) {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            assert(sock > 0 && "Socket creation");
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = INADDR_ANY;
            addr.sin_port = htons(port);
            assert(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0 && "Socket bind");
            assert(listen(sock, SOMAXCONN) == 0 && "Socket listen");
            t = std::thread(startAccepting, sock);
          };
    void Stop() {
      close(sock);
      t.join();
    }
private:
    int sock = 0;
    std::thread t = {};

    static void startAccepting(int sock) {
        sockaddr_in client_addr{};
        socklen_t client_len;
        while (true)
        {
            int con = accept(sock, (struct sockaddr *) &client_addr, &client_len);
            char *hello = "HTTP/1.1 200 OK\nContent-Length: 0\n\n";
            write(con , hello , strlen(hello));
            std::cout << "Response\n";
            if (con == -1) {
              return;
            }
            close(con);
        }
    }
};
