obj = main.o bfs.o findurl.o set.o

spider : $(obj)
	g++ -o spider $(obj) -g -Wall
main.o : main.cpp main.h
	g++ -c main.cpp -g -Wall
bfs.o : bfs.cpp bfs.h
	g++ -c bfs.cpp -g -Wall
findurl.o : findurl.cpp findurl.h
	g++ -c findurl.cpp -g -Wall
set.o : set.cpp set.h
	g++ -c set.cpp -g -Wall
clean :
	rm *.o


