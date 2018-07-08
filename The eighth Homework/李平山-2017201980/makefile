objects = main.cc query.cc inforetrieval.cc
objects_o = main.o query.o inforetrieval.o 
inforetrieval.o : inforetrieval.cc inforetrieval.h 
	g++ -c inforetrieval.cc --std=c++11
query.o : query.cc query.h
	g++ -c query.cc --std=c++11
main.o : query.h inforetrieval.h main.cc
	g++ -c main.cc --std=c++11
a : $(objects_o)
	g++ -o a $(objects_o) --std=c++11
clean :
	rm  $(objects_o)
