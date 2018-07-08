main: main.o document.o resource.o result.o enquiry.o term.o processor.o database.o
	g++ -o main main.o document.o resource.o result.o enquiry.o term.o processor.o database.o -Wl,-dn -L ../ltp-3.4.0/lib/ -lsegmentor -lboost_regex -Wl,-dy -O3
main.o: main.cpp resource.h result.h enquiry.h processor.h structure.h
	g++ -c main.cpp -O3 -g
term.o: term.cpp term.h document.h structure.h
	g++ -c term.cpp -O3 -g
document.o: document.cpp document.h term.h
	g++ -c document.cpp -O3 -g
resource.o: resource.cpp resource.h document.h term.h database.h structure.h
	g++ -c resource.cpp -std=c++11 -O3 -g
database.o: database.cpp database.h document.h term.h structure.h
	g++ -c database.cpp -std=c++11 -O3 -g
enquiry.o: enquiry.cpp enquiry.h result.h document.h structure.h
	g++ -c enquiry.cpp -I ../ltp-3.4.0/include/ltp/ -I ../ltp.3.4.0/thirdparty/boost/include -O3 -g
result.o: result.cpp result.h document.h
	g++ -c result.cpp -O3 -g
processor.o: processor.cpp processor.h document.h
	g++ -c processor.cpp -O3 -g
clean:
	rm main main.o document.o term.o resource.o enquiry.o result.o processor.o database.o
