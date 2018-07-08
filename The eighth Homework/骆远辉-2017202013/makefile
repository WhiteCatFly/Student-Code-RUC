objects = main.o index.o score.o document.o

ir : $(objects)
	g++ -std=c++11 -o ir $(objects)

index.o : document.h index.h index.cpp
	g++ -c index.cpp -std=c++11 -o index.o -Wall -g

score.o : score.h index.h document.h score.cpp
	g++ -c score.cpp -std=c++11 -o score.o -Wall -g

document.o : document.h document.cpp
	g++ -c document.cpp -std=c++11 -o document.o -Wall -g

main.o : index.h score.h document.h main.cpp
	g++ -c main.cpp -std=c++11 -o main.o -Wall -g

.PHONY : clean
clean : 
	-rm ir $(objects)
