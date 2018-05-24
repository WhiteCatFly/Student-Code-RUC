Numstring: Numstring.o NumstringOperator.o Mystring.o MystringOperator.o main.o
	g++ -o Numstring Numstring.o NumstringOperator.o Mystring.o MystringOperator.o main.o
	rm -f *.o
Numstring.o: Numstring.cpp Numstring.h
	g++ -c Numstring.cpp -std=gnu++11
NumstringOperator.o: NumstringOperator.cpp Numstring.h
	g++ -c NumstringOperator.cpp -std=gnu++11
Mystring.o: Mystring.cpp Mystring.h
	g++ -c Mystring.cpp -std=gnu++11
MystringOperator.o: MystringOperator.cpp Mystring.h
	g++ -c MystringOperator.cpp -std=gnu++11
main.o: main.cpp Numstring.h
	g++ -c main.cpp -std=gnu++11
