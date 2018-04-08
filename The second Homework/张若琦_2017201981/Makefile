objects = Main.o crawl.o ExtractURL.o ReadFile.o DisposeStr.o clean.o

crawl : $(objects)
	g++ -std=c++11 -o crawl $(objects)

DisposeStr.o : DisposeStr.cc DisposeStr.h
	g++ -std=c++11 -c DisposeStr.cc

.PHONY : clean
clean :
	-rm crawl $(objects)