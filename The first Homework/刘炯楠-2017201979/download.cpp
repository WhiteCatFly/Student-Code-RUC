#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include "normalization.h"
#include "download.h"

using namespace std;

inline void download_sleep(const double utime) {
	usleep(CLOCKS_PER_SEC * utime);
}

void page_download(const string & web_page) {
	char * web_page_name = (char *) malloc (4* MAXLEN * sizeof(char));
	const int position = web_page.find("info");
	const int len = web_page.length();
	
	for (int i = position; i < len; ++i) {
		web_page_name[i - position] = web_page[i];
	}
	web_page_name[len - position] = '\0';

	char * instruction_1 = (char *) malloc (4 * MAXLEN * sizeof (char));
	char * directory = normalize_directory(web_page);
	sprintf(instruction_1,"mkdir -p '%s'",directory); 
	
	system(instruction_1);

	char * file_name = normalize_file_name(web_page);
	char * instruction_2 = (char *) malloc (4 * MAXLEN * sizeof (char));
	sprintf(instruction_2, "wget -O '%s' '%s' --tries=3 -T5",file_name, web_page_name);

	system(instruction_2);

	download_sleep();

	free(web_page_name);
	free(file_name);
	free(directory);
	free(instruction_1);
	free(instruction_2);
}
