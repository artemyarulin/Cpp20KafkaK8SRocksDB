#include <cassert>
#include <functional>
#include <iostream>

#include "doctest.h"

import kafka;

TEST_CASE("kafka open") {
  auto log = [](std::string m) { printf("%s\n", m.c_str()); };
  Kafka s1("srv", "id", log);
}
