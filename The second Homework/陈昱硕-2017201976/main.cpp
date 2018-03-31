#include <cstdio>

#include "global_settings.h"
#include "crawl.h"

int main(int argc, char *argv[]){
	InitGlobalSettings(argc, argv);
	Crawl();
	return 0;
}
