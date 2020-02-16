app: http.o main.cpp
	clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. http.o main.cpp -o app

test: http.o http_test.cpp main_test.cpp
	clang++ -std=c++2a -fmodules-ts -fprebuilt-module-path=. http.o http_test.cpp main_test.cpp -o test
	./test

http.o: http.cpp
	clang++ -std=c++2a -fmodules-ts --precompile -x c++-module http.cpp -o http.pcm
	clang++ -std=c++2a -fmodules-ts -c http.pcm -o http.o
