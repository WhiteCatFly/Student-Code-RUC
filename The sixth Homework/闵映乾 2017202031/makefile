
mystring.o : mystring.cpp mystring.h 
	g++ -c mystring.cpp
mygoodstring.o : mygoodstring.cpp mystring.h mygoodstring.h  
	g++ -c mygoodstring.cpp
main.o : main.cpp mygoodstring.cpp mygoodstring.h  mystring.h
	g++ -c main.cpp
tmp : main.o mygoodstring.o mystring.o 
	g++ -o tmp main.o mygoodstring.o mystring.o 

