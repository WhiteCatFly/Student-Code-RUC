OBJ = main.o crawl.o download.o extract.o
CPP = g++ -std=c++11 -g

main: $(OBJ)
	$(CPP) -o main $(OBJ)

main.o: crawl.h
	$(CPP) -c main.cc

crawl.o: crawl.h download.h extract.h
	$(CPP) -c crawl.cc

download.o: download.h
	$(CPP) -c download.cc

extract.o: extract.h
	$(CPP) -c extract.cc

.PHONY: clean
clean:
	-rm main $(OBJ)

