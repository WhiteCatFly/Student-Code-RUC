CWSPOS: main.o Initialize.o CWS.o POS.o
	g++ -o CWSPOS main.o Initialize.o CWS.o POS.o
	rm -f *.o
main.o: CWSPOS.h main.cpp
	g++ -c main.cpp -std=gnu++11
Initialize.o: CWSPOS.h Initialize.cpp
	g++ -c Initialize.cpp -std=gnu++11
CWS.o: CWSPOS.h CWS.cpp
	g++ -c CWS.cpp -std=gnu++11
POS.o: CWSPOS.h POS.cpp
	g++ -c POS.cpp -std=gnu++11
