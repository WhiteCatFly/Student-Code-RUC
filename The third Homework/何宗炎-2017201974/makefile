#mkfile
obj = main.o Crawl.o Init_Crawler.o Url_Get.o Web_Crawl.o Crawl_Setting_checker.o

work: $(obj)
	g++ -o work $(obj) -g -Wall

main.o: main.cpp
	g++ -c main.cpp -g -Wall

Crawl.o: Crawl.cpp Web_Crawler.h
	g++ -c Crawl.cpp Web_Crawler.h -DCRAWL_CPP -g -Wall

Init_Crawler.o: Init_Crawler.cpp Web_Crawler.h
	g++ -c Init_Crawler.cpp Web_Crawler.h -DINIT_CRAWLER_CPP -g -Wall

Url_Get.o: Url_Get.cpp Web_Crawler.h
	g++ -c Url_Get.cpp Web_Crawler.h -DURL_GET_CPP -g -Wall

Web_Crawl.o: Web_Crawl.cpp Web_Crawler.h
	g++ -c Web_Crawl.cpp Web_Crawler.h -g -Wall

Crawl_Setting_checker.o: Crawl_Setting_checker.cpp Web_Crawler.h
	g++ -c Crawl_Setting_checker.cpp Web_Crawler.h -g -Wall

sweep:
	rm work $(obj)
