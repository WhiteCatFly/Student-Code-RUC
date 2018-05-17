obj = main.o htmlparser.o tag.o parser_extract.o parser_find.o tag_extract.o tag_find.o

htmlparser: $(obj)
	g++ -o htmlparser $(obj) -g -Wall -std=c++11

main.o: main.cpp htmlparser.h consts.h
	g++ -c main.cpp -g -Wall -std=c++11

htmlparser.o: htmlparser.cpp htmlparser.h consts.h
	g++ -c htmlparser.cpp -g -Wall -std=c++11

parser_extract.o: parser_extract.cpp htmlparser.h 
	g++ -c parser_extract.cpp -g -Wall -std=c++11

parser_find.o: parser_find.cpp htmlparser.h
	g++ -c parser_find.cpp -g -Wall -std=c++11

tag.o: tag.cpp htmlparser.h
	g++ -c tag.cpp -g -Wall -std=c++11

tag_extract.o: tag_extract.cpp htmlparser.h consts.h
	g++ -c tag_extract.cpp -g -Wall -std=c++11

tag_find.o: tag_find.cpp htmlparser.h
	g++ -c tag_find.cpp -g -Wall -std=c++11

clean:
	rm *.o
