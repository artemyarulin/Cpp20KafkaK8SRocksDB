#include <cassert>
#include <functional>
#include <iostream>

#include "doctest.h"

import kafka;

using std::string;

TEST_CASE("kafka open") {
  auto log = [](string m) { printf("%s\n", m.c_str()); };
  auto onMsg = [](string) {};
  Kafka k(log, onMsg);
  k.Start("server", "id", "topic");
  k.Stop();
}
