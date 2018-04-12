run : main
	reset && ./main -s info.ruc.edu.cn --key-word=ruc,info --timeout=10

objects = main.o crawl.o filter.o view_source.o convert.o kbhit.o global_settings.o

main : $(objects)
	g++ -o main $(objects) -Wall -lcurl -g

main.o : main.cpp crawl.h
	g++ -c main.cpp -Wall --std=c++11 -g

crawl.o : crawl.cpp crawl.h filter.h view_source.h kbhit.h
	g++ -c crawl.cpp -Wall -DCRAWL_CPP --std=c++11 -g

filter.o : filter.cpp filter.h
	g++ -c filter.cpp -Wall -DFILTER_CPP --std=c++11 -g

view_source.o : view_source.cpp view_source.h convert.h
	g++ -c view_source.cpp -Wall -lcurl -DVIEW_SOURCE_CPP --std=c++11 -g

convert.o : convert.cpp convert.h
	g++ -c convert.cpp -Wall -DCONVERT_CPP --std=c++11 -g

kbhit.o : kbhit.cpp kbhit.h
	g++ -c kbhit.cpp -Wall -DKBHIT_CPP --std=c++11 -g

global_settings.o : global_settings.cpp global_settings.h
	g++ -c global_settings.cpp -Wall -DGLOBAL_SETTINGS_CPP --std=c++11 -g


clean :
	rm -rf $(objects) main
