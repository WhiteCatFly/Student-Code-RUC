objects = main.cpp parser.cpp get_html.cpp
objects_o = main.o parser.o get_html.o 
parser.o :parser.cpp parser.h standardize.h
	g++ -c parser.cpp
get_html.o : get_html.cpp parser.h standardize.h
	g++ -c get_html.cpp
main.o : main.cpp parser.h standardize.h
	g++ -c main.cpp
a : $(objects_o)
	g++ -o a $(objects)
clean :
	rm  a main.o parser.o get_html.o 
