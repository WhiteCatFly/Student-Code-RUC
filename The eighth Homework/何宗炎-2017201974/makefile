#mkfile
obj = main.o Init.o InputDeal.o Search.o

work: $(obj)
	g++ -o work $(obj) -g -Wall --std=c++11

main.o: main.cpp
	g++ -c main.cpp -g -Wall --std=c++11

Init.o: Init.cpp Init.h
	g++ -c Init.cpp Init.h -g -Wall --std=c++11

InputDeal.o: InputDeal.cpp InputDeal.h
	g++ -c InputDeal.cpp InputDeal.h -g -Wall --std=c++11

Search.o: Search.cpp Search.h
	g++ -c Search.cpp Search.h -g -Wall --std=c++11

sweep:
	rm work $(obj)
