dstring: dstring.o main.o dstring.h
	g++ -o dstring dstring.o main.o -g -Wall

dstring.o: dstring.cpp dstring.h
	g++ -c dstring.cpp -g -Wall

main.o: main.cpp dstring.h
	g++ -c main.cpp -g -Wall

clean:
	rm *.o
