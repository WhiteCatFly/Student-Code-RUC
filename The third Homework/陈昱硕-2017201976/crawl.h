#ifndef CRAWL_H
#define CRAWL_H

#include <vector>
#include <queue>
#include <set>

#include "global_settings.h"
#include "view_source.h"

using std :: vector;
using std :: queue;
using std :: set;

class Crawler{
	private : 
		vector<string> seed_;
		
		string input_file_;
		string output_file_;
		string error_file_;
		
		queue<string> *queue_of_web_site_;
		set<string> *set_of_web_site_;
		int retry_count_;
		int number_of_popped_web_site_;
		int number_of_total_web_site_;
		
		Viewer *viewer_;
		
	public : 
		void Crawl();
		
		Crawler(const vector<string> &seed,
				const vector<string> &key_word,
				const int &running_mode_ = Restart,
				const string &input_file = "origin.log",
				const string &output_file = "origin.log",
				const string &error_file = "error.log",
				const string &save_directory = "./download/",
				const int &retry_count = 5,
				const int &timeout_time = 10,
				const int &time_interval = 50000);
		
		~Crawler();
};

#endif
