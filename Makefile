app: http.o main.cc
	clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. http.o main.cc -o app

test: http.o http_test.cc main_test.cc
	clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. http.o http_test.cc main_test.cc -o test
	./test

http.o: http.cc
	clang++ -std=c++2a -fmodules-ts --precompile -x c++-module http.cc -o http.pcm
	clang++ -std=c++2a -fmodules-ts -c http.pcm -o http.o
