#include <functional>
#include <iostream>

#include "doctest.h"

import http;

TEST_CASE("http health check") {
  Http h(8080, [](std::string) {});
  h.Start();
  h.Stop();

  h.Start();
  h.Stop();
}
