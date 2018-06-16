objects = main.o search_engine.o index.o document.o search_result.o query.o kbhit.o
pattern = --std=c++11 -g -Wall -O3 -pg
ltp_path = /home/cys/ltp/ltp-3.4.0
cws_pattern = -I $(ltp_path)/include/ltp/ -I $(ltp_path)/thirdparty/boost/include
cws_link = -Wl,-dn -L $(ltp_path)/lib/ -lsegmentor -lboost_regex -Wl,-dy

run : main
	reset && ./main

main : $(objects)
	g++ -o main $(objects) $(cws_link) $(pattern)

main.o : main.cpp search_engine.h
	g++ -c main.cpp $(pattern)

search_engine.o : search_engine.cpp search_engine.h document.h index.h search_result.h query.h kbhit.h
	g++ -c search_engine.cpp $(pattern) $(cws_pattern)

index.o : index.cpp index.h document.h
	g++ -c index.cpp $(pattern)

document.o : document.cpp document.h
	g++ -c document.cpp $(pattern)

search_result.o : search_result.cpp search_result.h index.h document.h query.h set_color.h
	g++ -c search_result.cpp $(pattern)

query.o : query.cpp query.h set_color.h
	g++ -c query.cpp $(pattern) $(cws_pattern)

kbhit.o : kbhit.cpp kbhit.h set_color.h
	g++ -c kbhit.cpp $(pattern)


clean :
	rm -rf main $(objects)