objects = my_string.o main.o

run : main
	reset && ./main

main : $(objects)
	g++ $(objects) -o main -Wall -g

main.o : main.cpp my_string.h
	g++ -c main.cpp -Wall -g

my_string.o : my_string.cpp my_string.h
	g++ -c my_string.cpp -Wall -g


clean :
	rm main $(objects) -rf