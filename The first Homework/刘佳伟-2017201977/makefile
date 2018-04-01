all:crawl
	rm -f *.o
crawl:crawl.o crawl_url.o crawl_gethtml.o
	g++ -o crawl crawl.o crawl_url.o crawl_gethtml.o
crawl.o:crawl.cpp crawl.h
	g++ -c crawl.cpp
crawl_url.o:crawl_url.cpp crawl.h
	g++ -c crawl_url.cpp
crawl_gethtml.o:crawl_gethtml.cpp crawl.h
	g++ -c crawl_gethtml.cpp
