objects = main.cpp bfs.cpp find_url.cpp
objects_o = main.o bfs.o find_url.o 
find_url.o : find_url.cpp find_url.h standardize.h
	g++ -c find_url.cpp
bfs.o : bfs.cpp craw.h find_url.h
	g++ -c bfs.cpp
main.o : main.cpp craw.h
	g++ -c main.cpp
a : $(objects_o)
	g++ -o a $(objects)
clean :
	rm a objects_o
