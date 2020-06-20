gccV := $(shell gcc -dumpversion)
libV := lib_v2

matrix_library:
	g++ matrix.cpp -o fail
# fix weird behaviour

install: $(libV)/matrix.h $(libV)/matrix.cpp $(libV)/matrix
		mkdir -p /usr/include/c++/$(gccV)/extended
		cp $(libV)/matrix /usr/include/c++/$(gccV)/extended
		chmod 0755 /usr/include/c++/$(gccV)/extended/matrix
		cp $(libV)/matrix.h /usr/include/c++/$(gccV)/extended
		chmod 0755 /usr/include/c++/$(gccV)/extended/matrix.h
		cp $(libV)/matrix.cpp /usr/include/c++/$(gccV)/extended
		chmod 0755 /usr/include/c++/$(gccV)/extended/matrix.cpp

test: test.cpp
	g++ test.cpp -o test.out -std=c++17