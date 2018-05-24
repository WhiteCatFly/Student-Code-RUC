Mystring: Mystring.o main.o MystringOperator.o
	g++ -o Mystring Mystring.o main.o MystringOperator.o
	rm -f *.o
Mystring.o: Mystring.cpp Mystring.h
	g++ -c Mystring.cpp -std=gnu++11
MystringOperator.o: MystringOperator.cpp Mystring.h
	g++ -c MystringOperator.cpp -std=gnu++11
main.o:main.cpp Mystring.h
	g++ -c main.cpp -std=gnu++11
