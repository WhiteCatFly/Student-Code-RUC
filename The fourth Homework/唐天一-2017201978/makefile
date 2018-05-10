HTMLParser : main.o initialize.o parser_function.o user_interface.o HTMLParser.h
	g++ main.o initialize.o parser_function.o user_interface.o -std=c++11 -Wall -o HTMLParser
	
main.o : main.cpp HTMLParser.h
	g++ main.cpp -std=c++11 -c
	
initialize.o : initialize.cpp HTMLParser.h
	g++ initialize.cpp -std=c++11 -c
	
parser_function.o : parser_function.cpp HTMLParser.h
	g++ parser_function.cpp -std=c++11 -c

user_interface.o : user_interface.cpp HTMLParser.h
	g++ user_interface.cpp -std=c++11 -c
	
