objects = HMM.o main.o
pattern = -Wall -g --std=c++11 -O3

run : main
	reset && ./main

main : $(objects)
	g++ -o main $(objects)

main.o : main.cpp HMM.h
	g++ -c main.cpp $(pattern)

HMM.o : HMM.h HMM.cpp
	g++ -c HMM.cpp $(pattern)


clean :
	rm $(objects) main -rf