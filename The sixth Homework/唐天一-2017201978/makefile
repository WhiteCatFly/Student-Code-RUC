main : main.cpp MyString.o Format_Print.o
	g++ main.cpp MyString.o Format_Print.o -Wall -std=c++11 -o main

MyString.o : MyString.cpp MyString.h
	g++ MyString.cpp -Wall -std=c++11 -c
	
Format_Print.o : Format_Print.cpp Format_Print.h MyString.h
	g++ Format_Print.cpp -Wall -std=c++11 -c
