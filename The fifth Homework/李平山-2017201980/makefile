objects = main.o String.o
String.o : String.cc String.h
	g++ -c String.cc
main.o : main.cc String.h
	g++ -c main.cc
tmp : $(objects)
	g++ -o tmp $(objects)
run:
	./tmp
clean:	
	rm $(objects) tmp
