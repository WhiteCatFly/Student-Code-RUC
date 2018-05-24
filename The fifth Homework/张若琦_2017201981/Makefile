objects = Main.o String.o

String : $(objects)
	g++ -std=c++11 -o String $(objects)
	
Main.o : Main.cpp String.h
	g++ -std=c++11 -c Main.cpp

String.o : String.cpp String.h
	g++ -std=c++11 -c String.cpp

.PHONY : clean
clean :
	-rm String $(objects)
