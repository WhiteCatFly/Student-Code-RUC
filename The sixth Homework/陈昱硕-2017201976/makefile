objects = main.o my_string.o number_string.o

run : main
	reset && ./main

main : $(objects)
	g++ $(objects) -o main -Wall -g --std=c++11

main.o : main.cpp my_string.h
	g++ -c main.cpp -Wall -g --std=c++11

my_string.o : my_string.cpp my_string.h
	g++ -c my_string.cpp -Wall -g --std=c++11

number_string.o : number_string.cpp number_string.h
	g++ -c number_string.cpp -Wall -g --std=c++11


clean :
	rm main $(objects) -rf