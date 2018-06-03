main.o : HMM.h initialization.o POS.o CWS.o
	g++ main.cpp initialization.o POS.o CWS.o -Wall -O3 -o main

initialization.o : HMM.h initialization.cpp
	g++ initialization.cpp -Wall -O3 -c
	
POS.o : HMM.h POS.cpp
	g++ POS.cpp -Wall -O3 -c
	
CWS.o : HMM.h CWS.cpp
	g++ CWS.cpp -Wall -O3 -c
