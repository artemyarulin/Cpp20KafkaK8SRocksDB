CC := clang++ -Werror -Wall -Wextra -std=c++2a -fmodules-ts -fprebuilt-module-path=.

app: kafka.o http.o storage.o main.cc
	$(CC) -l rocksdb -l rdkafka++ kafka.o http.o storage.o -O2 main.cc -o app

test: kafka.o kafka_test.cc http.o http_test.cc storage.o storage_test.cc main_test.cc
	$(CC) -l rocksdb -l rdkafka++ kafka.o http.o storage.o *_test.cc -o test
	./test

http.o: http.cc
	$(CC) --precompile -x c++-module http.cc -o http.pcm
	$(CC) -c http.pcm -o http.o

storage.o: storage.cc
	$(CC) --precompile -x c++-module storage.cc -o storage.pcm
	$(CC) -c storage.pcm -o storage.o

kafka.o: kafka.cc
	$(CC) --precompile -x c++-module kafka.cc -o kafka.pcm
	$(CC) -c kafka.pcm -o kafka.o

lint: *.cc #clang-tidy unfortunately doesn't support modules yet
	docker run --rm -v $$PWD:/tmp alpine:3.11.3 sh -c "apk add -Uq clang && clang-format -i /tmp/*.cc"
