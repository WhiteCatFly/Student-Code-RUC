OBJ = main.o search_engine.o
CPP = g++ -std=gnu++11 -g

main: $(OBJ)
	$(CPP) -o main $(OBJ)

main.o: main.cc include/thulac.h search_engine.h
	$(CPP) -c main.cc

search_engine.o: search_engine.cc search_engine.h
	$(CPP) -c search_engine.cc

.PHONY: clean
clean:
	-rm main $(OBJ)

