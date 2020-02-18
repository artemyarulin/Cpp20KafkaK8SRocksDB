#include "doctest.h"
#include <iostream>
#include <functional>
#include <cassert>

import storage;

TEST_CASE("storage open") {
  auto log = [](std::string m) { printf("%s\n", m.c_str()); };

  Storage s1("/tmp/db", log);
  s1.Write("hello", "world");
  assert("world" == s1.Read("hello"));
  s1.Close();

  Storage s2("/tmp/db", log);
  assert("world" == s2.Read("hello"));
  s2.Close();
}
