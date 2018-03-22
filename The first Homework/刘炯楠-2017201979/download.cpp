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

void download_sleep() {
	usleep(CLOCKS_PER_SEC * 0.05);
}

void page_download(string web_page) {
	static int cnt = 0;
	char * web_page_name = (char *) malloc (4* MAXLEN * sizeof(char));
	int position = web_page.find("info");
	int len = web_page.length();
	
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

	free(web_page_name);
	free(file_name);
	free(directory);
	free(instruction_1);
	free(instruction_2);
}
