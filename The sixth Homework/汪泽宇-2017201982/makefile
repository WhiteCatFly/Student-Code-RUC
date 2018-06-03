CPP = g++ -std=c++17 -g

digitstring.o: mystring.h digitstring.hpp
	$(CPP) -c digitstring.cc

mystring.o: mystring.h
	$(CPP) -c mystring.cc

.PHONY: clean
clean:
	-rm mystring.o digitstring.o

