obj = main.o build.o init.o query.o searchengine.o

se: $(obj)
	g++ -o se $(obj) -g -std=c++11

main.o: programs/main.cpp include/searchengine.h include/const.h
	g++ -c programs/main.cpp -g -std=c++11

searchengine.o: programs/searchengine.cpp include/searchengine.h include/const.h
	g++ -c programs/searchengine.cpp -g -std=c++11

init.o: programs/init.cpp include/searchengine.h include/const.h
	g++ -c programs/init.cpp -g -std=c++11

build.o: programs/build.cpp include/searchengine.h include/const.h
	g++ -c programs/build.cpp -g -std=c++11

query.o: programs/query.cpp include/searchengine.h include/const.h
	g++ -c programs/query.cpp -g -std=c++11

clean:
	rm *.o
