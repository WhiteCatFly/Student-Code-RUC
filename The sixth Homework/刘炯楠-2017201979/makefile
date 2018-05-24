main: main.o String.o number_string.o
	g++ -o main main.o number_string.o String.o
main.o: main.cpp number_string.h
	g++ -c main.cpp
number_string.o: number_string.cpp number_string.h String.h
	g++ -c number_string.cpp
String.o: String.cpp String.h
	g++ -c String.cpp
clean:
	rm main main.o String.o
