main : initialization.o search.o make_wtd.o main.o Info_Ret.h
	g++ main.o initialization.o search.o make_wtd.o -Wall -O3 -std=c++11 -Wl,-dn -L /home/steventang/Search/ltp-3.4.0/lib -lsegmentor -lboost_regex -Wl,-dy -o main
	
search.o : search.cpp Info_Ret.h segment_dll.h
	g++ search.cpp -Wall -O3 -std=c++11 -I /home/steventang/Search/ltp-3.4.0/include/ltp/ -I /home/steventang/Search/ltp-3.4.0/thirdparty/boost/include/boost/ -c

main.o : main.cpp Info_Ret.h
	g++ main.cpp -Wall -O3 -std=c++11 -c

make_wtd.o : make_wtd.cpp Info_Ret.h
	g++ make_wtd.cpp -Wall -O3 -std=c++11 -c
	
initialization.o : initialization.cpp Info_Ret.h
	g++ initialization.cpp -Wall -O3 -std=c++11 -c
