
search_main.o : search_engine.h search_main.cpp
	g++ -c search_main.cpp -I /home/myq/文档/分词与标注/ltp/include/ltp/ -I /home/myq/文档/分词与标注/ltp/thirdparty/boost/include/ -Wl,-dn -L /home/myq/文档/分词与标注/ltp/lib/ -lsegmentor -lboost_regex -Wl,-dy
search_engine.o : search_engine.h search_engine.cpp
	g++ -c search_engine.cpp -I /home/myq/文档/分词与标注/ltp/include/ltp/ -I /home/myq/文档/分词与标注/ltp/thirdparty/boost/include/ -Wl,-dn -L /home/myq/文档/分词与标注/ltp/lib/ -lsegmentor -lboost_regex -Wl,-dy
search :	search_engine.o search_main.o
	g++  search_engine.o search_main.o -I /home/myq/文档/分词与标注/ltp/include/ltp/ -I /home/myq/文档/分词与标注/ltp/thirdparty/boost/include/ -Wl,-dn -L /home/myq/文档/分词与标注/ltp/lib/ -lsegmentor -lboost_regex -Wl,-dy          -o search
	
