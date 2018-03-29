main: main.o download.o extract.o
	g++ -o main main.o download.o extract.o -std=c++11

main.o: main.cc
	g++ -c main.cc -std=c++11 -g

download.o: download.cc
	g++ -c download.cc -std=c++11 -g

extract.o: extract.cc
	g++ -c extract.cc -std=c++11 -g

clean:
	rm main main.o download.o extract.o

