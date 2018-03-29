#include "crawl.h"

#include <cstdio>
#include <cstring>

#include <iostream>

#include <string>
#include <vector>
#include <queue>
#include <set>

#include "filter.h"
#include "view_source.h"
#include "kbhit.h"
#include "global_settings.h"

using namespace std;

extern vector<string> seed;

extern int running_mode;
extern string input_file;
extern string output_file;

static queue<string> *queue_of_web_site;
static set<string> *set_of_web_site;
static int number_of_popped_web_site = 0;
static int number_of_total_web_site = 0;

inline static void InitQueue(){
	queue_of_web_site = new queue<string>;
	set_of_web_site = new set<string>;
	
	if (running_mode == Load){
		FILE *fp = fopen(input_file . c_str(), "r");
		char *buffer = (char *) malloc(400 * sizeof(char));
		cerr << "test!" << endl;
		while (fscanf(fp, "%*s%*s%s", buffer) == 1){
			cerr << buffer << endl;
			if (strcmp(buffer, "popped") == 0){
				number_of_popped_web_site ++;
				queue_of_web_site -> pop();
			}
			else{
				number_of_total_web_site ++;
				queue_of_web_site -> push(string(buffer));
				set_of_web_site -> insert(string(buffer));
			}
		}
		free(buffer);
		fclose(fp);
	}
	else if (running_mode == Restart){
		FILE *fp = fopen(output_file . c_str(), "w");
		for (auto iter : seed){
			fprintf(fp, "seed -> %s\n", iter . c_str());
			number_of_total_web_site ++;
			queue_of_web_site -> push(iter);
			set_of_web_site -> insert(iter);
		}
		fclose(fp);
	}
}

void Crawl(){
	InitQueue();
	InitViewer();
	InitKeyboard();
	
	while (!queue_of_web_site -> empty()){
		CheckKeyboard();
		
		string *web_site = new string(queue_of_web_site -> front());
		queue_of_web_site -> pop();
		FILE *fp = fopen(output_file . c_str(), "a+");
		fprintf(fp, "%s is popped\n", web_site -> c_str());
		fclose(fp);
		number_of_popped_web_site ++;
		
		char *buffer = Download(web_site -> c_str());
		if (buffer == NULL){
			delete web_site;
			continue;
		}
		string *page_content = new string(buffer);
		SetPage(web_site, page_content);
		
		cerr << *web_site << endl;
		cerr << "popped = " << number_of_popped_web_site
			 << ", total = " << number_of_total_web_site
			 << ", remained = " << number_of_total_web_site - number_of_popped_web_site << endl;
		
		string *next_url;
		while ((next_url = GetNextUrl()) != NULL){
			if (set_of_web_site -> count(*next_url) == 0){
				FILE *fp = fopen(output_file . c_str(), "a+");
				fprintf(fp, "%s -> %s\n", web_site -> c_str(), next_url -> c_str());
				fclose(fp);
				number_of_total_web_site ++;
				queue_of_web_site -> push(*next_url);
				set_of_web_site -> insert(*next_url);
			}
			delete next_url;
		}
		
		cerr << "end of this file" << endl;
		
		delete web_site;
		delete page_content;
	}
	
	CloseViewer();
	CloseKeyboard();
}
