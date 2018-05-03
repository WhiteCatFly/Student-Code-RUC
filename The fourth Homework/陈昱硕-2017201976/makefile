objects = main.o parser.o

run : main
	reset && ./main -s in.html -m from_file -l "<(head(?=[\\s>]).*?)>((?!(</\\1>)).)*\\3"

main : $(objects)
	g++ main.o parser.o -o main -g -Wall --std=c++11

main.o : parser.h main.cpp
	g++ -c main.cpp -DMAIN_CPP -g -Wall --std=c++11

parser.o : parser.h parser.cpp
	g++ -c parser.cpp -DPARSER_CPP -g -Wall --std=c++11


clean :
	rm main $(objects) -rf
