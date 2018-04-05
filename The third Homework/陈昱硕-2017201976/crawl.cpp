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

Crawler :: Crawler(const vector<string> &seed,
				   const vector<string> &key_word,
				   const int &running_mode,
				   const string &input_file,
				   const string &output_file,
				   const string &error_file,
				   const string &save_directory,
				   const int &retry_count,
				   const int &timeout_time,
				   const int &time_interval) :
	seed_(seed), input_file_(input_file), output_file_(output_file),
	error_file_(error_file), retry_count_(retry_count),
	number_of_popped_web_site_(0), number_of_total_web_site_(0)
{
	queue_of_web_site_ = new queue<string>;
	set_of_web_site_ = new set<string>;
	
	if (running_mode == Load){
		FILE *fp = fopen(input_file . c_str(), "r");
		char *buffer = new char[400];
		while (fscanf(fp, "%*s%*s%s", buffer) == 1){
			if (strcmp(buffer, "popped") == 0){
				number_of_popped_web_site_ ++;
				queue_of_web_site_ -> pop();
			}
			else{
				number_of_total_web_site_ ++;
				queue_of_web_site_ -> push(string(buffer));
				set_of_web_site_ -> insert(string(buffer));
			}
		}
		delete buffer;
		fclose(fp);
	}
	else if (running_mode == Restart){
		FILE *fp = fopen(output_file . c_str(), "w");
		for (auto iter : seed_){
			fprintf(fp, "seed -> %s\n", iter . c_str());
			number_of_total_web_site_ ++;
			queue_of_web_site_ -> push(iter);
			set_of_web_site_ -> insert(iter);
		}
		fclose(fp);
	}
	
	viewer_ = new Viewer(error_file, save_directory, timeout_time, time_interval);
	Filter :: StaticSettings(key_word);
	InitKeyboard();
}

void Crawler :: Crawl(){	
	while (!queue_of_web_site_ -> empty()){
		CheckKeyboard();
		
		string *web_site = new string(queue_of_web_site_ -> front());
		queue_of_web_site_ -> pop();
		FILE *fp = fopen(output_file_ . c_str(), "a+");
		fprintf(fp, "%s is popped\n", web_site -> c_str());
		fclose(fp);
		number_of_popped_web_site_ ++;
		
		Filter *handle = new Filter(error_file_, *web_site, viewer_, retry_count_);
		
		fprintf(stderr, "%s\n", web_site -> c_str());
		fprintf(stderr, "popped = %d, total = %d, remained = %d\n",
						number_of_popped_web_site_,
						number_of_total_web_site_,
			 			number_of_total_web_site_ - number_of_popped_web_site_);
		
		string *next_url;
		while ((next_url = handle -> GetNextUrl()) != NULL){
			if (set_of_web_site_ -> count(*next_url) == 0){
				FILE *fp = fopen(output_file_ . c_str(), "a+");
				fprintf(fp, "%s -> %s\n", web_site -> c_str(), next_url -> c_str());
				fclose(fp);
				number_of_total_web_site_ ++;
				queue_of_web_site_ -> push(*next_url);
				set_of_web_site_ -> insert(*next_url);
			}
			delete next_url;
		}
		
		fprintf(stderr, "end of this file\n");
		
		delete handle;
		delete web_site;
	}
}

Crawler :: ~Crawler(){
	delete viewer_;
	CloseKeyboard();	
}
