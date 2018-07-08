main: main.o posting_list.o document.o dictionary.o Hits.o index_search.o
	g++ -std=c++11 -O3  main.o posting_list.o document.o dictionary.o Hits.o index_search.o -o main
main.o: dictionary.o index_search.o
	g++ -std=c++11 -O3 -c main.cpp
posting_list.o: posting_list.cpp posting_list.h
	g++ -std=c++11 -O3 -c posting_list.cpp
document.o: document.cpp ~/THULAC/include/*.h
	g++ -std=c++11 -O3 -march=native -I ~/THULAC/include -c document.cpp
dictionary.o: dictionary.cpp dictionary.h posting_list.o document.o
	g++ -std=c++11 -O3 -c dictionary.cpp
Hits.o: Hits.cpp Hits.h 
	g++ -std=c++11 -O3 -c Hits.cpp
index_search.o: index_search.cpp index_search.h Hits.o dictionary.o document.o posting_list.o
	g++ -std=c++11 -O3 -c index_search.cpp
clean:
	rm *.o
