#include "Web_Crawler.h"
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>

void get_html(const std::string &current_url, std::string &current_html, const int total){
	char operation[1000], number_html[1000];
	sprintf(number_html, "%d.html", total);
	sprintf(operation, "wget --tries=1 \"%s\" -O %s", current_url.c_str(), number_html);
	int res = system(operation);
	
	switch (res){
		case 0:{
			break;
		}
		case 1:{
			printf("Generic error code.\n");
			exit(0);
		}
		case 2:{
			printf("Parse error—for instance, when parsing command-line options, the ‘.wgetrc’ or ‘.netrc’...\n");
			exit(0);
		}
		case 3:{
			printf("File I/O error.\n");
			exit(0);
		}
		case 4:{
			printf("Network failure.\n");
			exit(0);
		}
		case 5:{
			printf("SSL verification failure.\n");
			exit(0);
		}
		case 6:{
			printf("Username/password authentication failure.\n");
			exit(0);
		}
		case 7:{
			printf("Protocol errors.\n");
			exit(0);
		}
		case 8:{
			printf("Server issued an error response.\n");
			exit(0);
		}
		default:{
			printf("Fail to crawl website.\n");
			exit(0);
		}
	}
	
	FILE* read_html = fopen(number_html, "r");
	char temp = fgetc(read_html);
	while (temp != EOF){
		current_html.push_back(temp);
		temp = fgetc(read_html);
	}
	
	fclose(read_html);
}
