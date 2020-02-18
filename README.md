# Cpp20KafkaK8SRocksDB

Experimenting with C++20 in writing stateful RocksDB Kafka consumer for Kubernetes.
Never wrote C++ before. My main language is Go, so trying to mimic things I get used to do there

- [Modules](https://docs.microsoft.com/en-us/cpp/cpp/modules-cpp) -  rather poor support across compilers and IDE. clang++ works, but complition involves many manual steps and even then crashing sometimes. But no headers files, nice

- [doctest](https://github.com/onqtam/doctest) - fast, simple utility for running unit tests. Allows Go test style organisation `app.cpp` and `app_test.cpp` or even one file for code and tests. Mast have for TDD

```
$ time make test
clang++ -std=c++2a -fmodules-ts --precompile http.cppm -o http.pcm
clang++ -std=c++2a -fmodules-ts -c http.pcm -o http.o
clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. http.o http_test.cpp main_test.cpp -o test
./test
[doctest] doctest version is "2.3.6"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:      1 |      1 passed |      0 failed |      0 skipped
[doctest] assertions:      0 |      0 passed |      0 failed |
[doctest] Status: SUCCESS!

real	0m2.571s
user	0m2.179s
```

- Kubernetes HTTP health check without dependencies with pure [sockets](http.cpp). For Kafka consumer we don't usually need HTTP stack, but k8s health check is still a must

- Alpine based Docker image
```
$ docker build . -t img > /dev/null && docker images | grep img
img    latest    480ccc17d485    Less than a second ago    8.96MB
```

## TODO

- [ ] Kafka
- [ ] Logger - glog looks nice with stacktraces and `CHECK` macros which is much better than assert (std::cout is not thread safe)
- [ ] googletest - doctest is nice, but googletest is a mainstream, worth checking that at least
- [ ] google benchmark - looks solid. Overall I guess adopting google set of C++ tools is not a bad idea
- [ ] Style, linter, formatter, etc. - important but I worry how many tools supports C++20 modules
- [ ] CMake is a community choice, replace hand crafted make script with that
- [ ] Socket based health checks passes k8s check, but it logs warnings as it doesn't consume the request
- [ ] fmt string library is very much desired
- [ ] Production build with optimisation. Check addr2line for stacktraces
- [ ] Why on alpine it asks to add <functional> and <cassert> includes, but locally it works fine?
