run : main
	rm -rf error.log origin.log
	reset && gdb ./main
	
objects = main.o crawl.o filter.o view_source.o convert.o kbhit.o

main : $(objects)
	g++ -o main $(objects) -Wall -lcurl -g
	
main.o : main.cpp crawl.h
	g++ -c main.cpp -Wall -g
	
crawl.o : crawl.cpp crawl.h filter.h view_source.h kbhit.h
	g++ -c crawl.cpp -Wall -DCRAWL_CPP -g
	
filter.o : filter.cpp filter.h
	g++ -c filter.cpp -Wall -DFILTER_CPP -g
	
view_source.o : view_source.cpp view_source.h convert.h
	g++ -c view_source.cpp -Wall -lcurl -DVIEW_SOURCE_CPP -g
	
convert.o : convert.cpp convert.h
	g++ -c convert.cpp -Wall -DCONVERT_CPP -g

kbhit.o : kbhit.cpp kbhit.h
	g++ -c kbhit.cpp -Wall -DKBHIT_CPP -g
	

clean :
	rm -rf $(objects) main
