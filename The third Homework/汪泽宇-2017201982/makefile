OBJ = main.o crawl.o
CPP = g++ -std=c++11 -g

main: $(OBJ)
	$(CPP) -o main $(OBJ)

main.o: crawl.h
	$(CPP) -c main.cc

crawl.o: crawl.h
	$(CPP) -c crawl.cc

.PHONY: clean
clean:
	-rm main $(OBJ)

