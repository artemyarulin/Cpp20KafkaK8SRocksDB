app: http.o storage.o main.cc
	clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. -l rocksdb http.o storage.o main.cc -o app

test: http.o http_test.cc storage.o storage_test.cc main_test.cc
	clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. -l rocksdb http.o http_test.cc storage.o storage_test.cc main_test.cc -o test
	./test

http.o: http.cc
	clang++ -std=c++2a -fmodules-ts --precompile -x c++-module http.cc -o http.pcm
	clang++ -std=c++2a -fmodules-ts -c http.pcm -o http.o

storage.o: storage.cc
	clang++ -std=c++2a -fmodules-ts --precompile -x c++-module storage.cc -o storage.pcm
	clang++ -std=c++2a -fmodules-ts -c storage.pcm -o storage.o
