web_crawler: web_crawler.o bfs.o download.o find_url.o normalization.o
	g++ -o web_crawler web_crawler.o bfs.o download.o find_url.o normalization.o
web_crawler.o: web_crawler.cpp bfs.h
	g++ -c web_crawler.cpp
bfs.o: bfs.cpp bfs.h download.h find_url.h
	g++ -c bfs.cpp
download.o: download.cpp download.h normalization.h
	g++ -c download.cpp
find_url.o: find_url.cpp find_url.h normalization.h
	g++ -c find_url.cpp
normalization.o: normalization.cpp normalization.h
	g++ -c normalization.cpp
	
clean:
	rm web_crawler web_crawler.o bfs.o download.o find_url.o normalization.o
