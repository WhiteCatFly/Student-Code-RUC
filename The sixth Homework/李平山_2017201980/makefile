objects = main.o String.o Stringout.o
String.o : String.cc String.h 
	g++ -c String.cc
Stringout.o : Stringout.cc String.h Stringout.h 
	g++ -c Stringout.cc
main.o : main.cc String.h Stringout.h
	g++ -c main.cc
tmp : $(objects)
	g++ -o tmp main.o Stringout.o String.o 
run:
	./tmp
clean:	
	rm $(objects) tmp
