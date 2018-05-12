goodstring: goodstring.o main.o goodstring.h
	g++ -o goodstring goodstring.o main.o -g -Wall

goodstring.o: goodstring.cpp goodstring.h
	g++ -c goodstring.cpp -g -Wall

main.o: main.cpp goodstring.h
	g++ -c main.cpp -g -Wall

clean:
	rm *.o
