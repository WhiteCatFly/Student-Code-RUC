main: main.o crawl.o download.o extract.o
	g++ -o main main.o crawl.o download.o extract.o -std=c++11

main.o: main.cc crawl.h
	g++ -c main.cc -std=c++11 -g

crawl.o: crawl.cc crawl.h download.h extract.h
	g++ -c crawl.cc -std=c++11 -g

download.o: download.cc download.h
	g++ -c download.cc -std=c++11 -g

extract.o: extract.cc extract.h
	g++ -c extract.cc -std=c++11 -g

clean:
	rm main main.o craw.o download.o extract.o

