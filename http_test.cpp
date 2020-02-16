#include "doctest.h"
#include <iostream>

import http;

TEST_CASE("http health check") {
   Http h = {};
   h.Start(8080);
   h.Stop();

   h.Start(8080);
   h.Stop();
}
