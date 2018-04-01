obj = main.o spider.o bfs.o findurl.o set.o

spider : $(obj)
	g++ -o spider $(obj) -g -Wall

main.o : main.cpp spider.h
	g++ -c main.cpp -g -Wall

spider.o : spider.cpp spider.h
	g++ -c spider.cpp -g -Wall

bfs.o : bfs.cpp spider.h
	g++ -c bfs.cpp -g -Wall

findurl.o : findurl.cpp spider.h
	g++ -c findurl.cpp -g -Wall

set.o : set.cpp spider.h set.h
	g++ -c set.cpp -g -Wall

clean :
	rm *.o


