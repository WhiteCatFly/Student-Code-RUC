objects = Main.o String.o print.o

Print : $(objects)
	g++ -std=c++11 -o Print $(objects)
	
Main.o : Main.cpp print.h
	g++ -std=c++11 -c Main.cpp
	
print.o : print.cpp print.h String.h
	g++ -std=c++11 -c print.cpp

String.o : String.cpp String.h
	g++ -std=c++11 -c String.cpp

.PHONY : clean
clean :
	-rm Print $(objects)
