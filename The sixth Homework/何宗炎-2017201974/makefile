#mkfile
obj = main.o MyNumString.o MyString.o

work: $(obj)
	g++ -o work $(obj) -g -Wall --std=c++11

main.o: main.cpp
	g++ -c main.cpp -g -Wall --std=c++11

MyNumString.o: MyNumString.cpp MyNumString.h 
	g++ -c MyNumString.cpp MyNumString.h -g -Wall --std=c++11

MyString.o: MyString.cpp MyString.h
	g++ -c MyString.cpp MyString.h -g -Wall --std=c++11

sweep:
	rm work $(obj)
