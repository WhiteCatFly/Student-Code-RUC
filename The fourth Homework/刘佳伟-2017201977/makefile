parser: parser.o main.o extract.o
	g++ -o parser parser.o main.o extract.o
	rm -f *.o
parser.o: parser.h parser.cpp
	g++ -c parser.cpp -std=gnu++11
main.o: parser.h main.cpp
	g++ -c main.cpp -std=gnu++11
extract.o: extract.h extract.cpp
	g++ -c extract.cpp -std=gnu++11
