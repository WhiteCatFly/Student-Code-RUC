Web_Crawler :main.o Web_Crawler_BFS.o get_html.o parse_html.o
	g++ -o Web_Crawler main.o Web_Crawler_BFS.o get_html.o parse_html.o 

main.o : main.cpp Web_Crawler_BFS.cpp Web_Crawler.h
	g++ main.cpp -c -Wall

Web_Crawler_BFS.o : Web_Crawler_BFS.cpp get_html.cpp parse_html.cpp Web_Crawler.h
	g++ Web_Crawler_BFS.cpp -c -Wall
	
get_html.o : get_html.cpp Web_Crawler.h
	g++ get_html.cpp -c -Wall
	
parse_html.o : parse_html.cpp Web_Crawler.h
	g++ parse_html.cpp -c -Wall

clean :
	rm *.o
	

