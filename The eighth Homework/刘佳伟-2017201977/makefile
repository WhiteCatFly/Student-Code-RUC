main: main.o search.o preprocess.o preprocess.o tfidf.o queryprocess.o
	g++ -o IR main.o search.o preprocess.o tfidf.o queryprocess.o -Wl,-dn -L ltp-master/lib/ -lsegmentor -lboost_regex -Wl,-dy 
	rm -f *.o
main.o: main.cpp main.h
	g++ -O3 -c main.cpp -I ltp-master/include/ltp/ -I ltp-master/thirdparty/boost/include/  -std=gnu++11
preprocess.o: preprocess.cpp preprocess.h
	g++ -O3 -c preprocess.cpp -std=gnu++11
tfidf.o: tfidf.cpp tfidf.h
	g++ -O3 -c tfidf.cpp -std=gnu++11
queryprocess.o: queryprocess.cpp queryprocess.h
	g++ -O3 -c queryprocess.cpp -I ltp-master/include/ltp/ -I ltp-master/thirdparty/boost/include/ -std=gnu++11
search.o: search.cpp search.h
	g++ -O3 -c search.cpp -std=gnu++11
