gccV := $(shell gcc -dumpversion)

install:
	make install_matrix
	make install_vector

install_matrix: matrix/matrix.h matrix/matrix.cpp matrix/matrix
	g++ matrix/test.cpp -o matrix/matrix.out
	mkdir -p /usr/include/c++/$(gccV)/extended
	cp matrix/matrix /usr/include/c++/$(gccV)/extended
	chmod 0755 /usr/include/c++/$(gccV)/extended/matrix
	cp matrix/matrix.h /usr/include/c++/$(gccV)/extended
	chmod 0755 /usr/include/c++/$(gccV)/extended/matrix.h
	cp matrix/matrix.cpp /usr/include/c++/$(gccV)/extended
	chmod 0755 /usr/include/c++/$(gccV)/extended/matrix.cpp

install_vector: vector/vector vector/vector.cpp vector/vector.hpp
	g++ vector/test.cpp -o vector/matrix.out
	mkdir -p /usr/include/c++/$(gccV)/extended
	cp vector/vector /usr/include/c++/$(gccV)/extended
	chmod 0755 /usr/include/c++/$(gccV)/extended/vector
	cp vector/vector.hpp /usr/include/c++/$(gccV)/extended
	chmod 0755 /usr/include/c++/$(gccV)/extended/vector.hpp
	cp vector/vector.cpp /usr/include/c++/$(gccV)/extended
	chmod 0755 /usr/include/c++/$(gccV)/extended/vector.cpp