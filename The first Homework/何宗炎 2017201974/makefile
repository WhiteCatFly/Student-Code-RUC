#mkfile
main: main.cpp Url_Get.o Hzydef.h
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	g++ -o main main.cpp Url_Get.o Hzydef.h -g -Wall

Url_Get.o: Url_Get.cpp Url_Get.h Hzydef.h
	g++ -c Url_Get.cpp -g -Wall
