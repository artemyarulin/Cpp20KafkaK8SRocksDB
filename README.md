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
