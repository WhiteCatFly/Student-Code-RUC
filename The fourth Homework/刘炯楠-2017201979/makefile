html_parser: html_parser.o my_regex.o html_text.o normalization.o
	g++ -o html_parser html_parser.o my_regex.o html_text.o normalization.o -std=c++11
html_parser.o: html_parser.cpp html_text.h my_regex.h normalization.h
	g++ -c html_parser.cpp -std=c++11
html_text.o: html_text.cpp html_text.h my_regex.h
	g++ -c html_text.cpp -std=c++11
my_regex.o: my_regex.cpp my_regex.h normalization.h
	g++ -c my_regex.cpp -std=c++11
normalization.o: normalization.cpp normalization.h
	g++ -c normalization.cpp -std=c++11
clean:
	rm html_parser html_parser.o html_text.o my_regex.o
