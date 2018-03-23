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

using namespace std;

extern vector<string> seed;

extern int running_mode;
extern string input_file;
extern string output_file;

static queue<string> *queue_of_web_site;
static set<string> *set_of_web_site;

static void InitQueue(){
	queue_of_web_site = new queue<string>;
	set_of_web_site = new set<string>;
	while (!queue_of_web_site -> empty())
		queue_of_web_site -> pop();
	set_of_web_site -> clear();
	
	for (auto iter : seed){
		queue_of_web_site -> push(iter);
		set_of_web_site -> insert(iter);
	}
}

void Crawl(){
	InitQueue();
	InitViewer();
	InitKeyboard();
	
	int number_of_web_site = 0;
	
	while (!queue_of_web_site -> empty()){
		CheckKeyboard();
		
		string *web_site = new string(queue_of_web_site -> front());
		queue_of_web_site -> pop();
		
		char *buffer = Download(web_site -> c_str());
		if (buffer == NULL){
			delete web_site;
			continue;
		}
		string *page_content = new string(buffer);
		SetPage(web_site, page_content);
		
		number_of_web_site ++;
		cerr << *web_site << endl;
		cerr << "Catched = " << number_of_web_site << endl;
		
		string *next_url;
		while ((next_url = GetNextUrl()) != NULL){
			if (set_of_web_site -> count(*next_url) == 0){
				FILE *fp = fopen(output_file . c_str(), "a+");
				fprintf(fp, "%s -> %s\n", web_site -> c_str(), next_url -> c_str());
				fclose(fp);
				queue_of_web_site -> push(*next_url);
				set_of_web_site -> insert(*next_url);
			}
			delete next_url;
		}
		
		cerr << "end of this file" << endl;
		FILE *fp = fopen(output_file . c_str(), "a+");
		fprintf(fp, "pop: %s", web_site -> c_str());
		fclose(fp);
		
		delete web_site;
		delete page_content;
	}
	
	CloseViewer();
	CloseKeyboard();
}
