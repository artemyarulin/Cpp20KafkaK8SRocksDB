#include "doctest.h"
#include <iostream>
#include <functional>

import http;

TEST_CASE("http health check") {
   Http h(8080, [](std::string m) { });
   h.Start();
   h.Stop();

   h.Start();
   h.Stop();
}
