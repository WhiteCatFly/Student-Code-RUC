#mkfile
obj = main.o Parser.o Parser_Node.o Parser_Tag.o 

work: $(obj)
	g++ -o work $(obj) -g -Wall --std=c++11

main.o: main.cpp
	g++ -c main.cpp -g -Wall --std=c++11

Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp Parser.h -g -Wall --std=c++11

Parser_Node.o: Parser_Node.cpp Parser_Node.h
	g++ -c Parser_Node.cpp Parser_Node.h -g -Wall --std=c++11

Parser_Tag.o: Parser_Tag.cpp Parser_Tag.h
	g++ -c Parser_Tag.cpp Parser_Tag.h -g -Wall --std=c++11

sweep:
	rm work $(obj)
