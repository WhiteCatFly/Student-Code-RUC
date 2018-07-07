#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "resource.h"
#include "document.h"
#include "term.h"
#include "database.h"
#include "structure.h"

using namespace std;

data_res resource_initialize(const string & root_directory) {
	data_res resource;
	if (database_exist() == true) {
		return initialize_from_database();
	} 
	else {
		ifstream fin;
		fin.open(root_directory.c_str());
		string file_name;
	
		int cnt = 0;
		while (fin >> file_name) {
			file_name = pred_data + file_name.substr(1);
			resource.docu_list[file_name] = cnt;
			resource.docu.emplace_back(file_name, 0, 1);
			cnt++;
		}
		document::docu_num = cnt;
		
		fin.clear();
		fin.seekg(0, ios::beg);
		
		while (fin >> file_name) {
			file_name = pred_data + file_name.substr(1);
			docu_preprocessor(file_name, resource);
		}
	
		fin.close();
	
		int size = resource.word.size();
		for (int i = 0; i < size; ++i) {
			resource.word[i].calc_idf();
		}
		output_to_database(resource);
	}
	return resource;
}

static void docu_preprocessor(const string & file_name, data_res & resource) {
	static int count = 0;
	int title_word = 0;
	int body_word = 0;
	string line;
	map<string, double> freq_title;
	map<string, double> freq_body;
	map<string, double> freq;
	ifstream fin;
	
	fin.open((file_name + suff_title).c_str());
	while (fin >> line) {
		istringstream istr(line);
		string word_str;
		while (istr >> word_str) {
			title_word++;
			if (resource.word_list.find(word_str) == resource.word_list.end()) {
				resource.word_list[word_str] = count;
				resource.word.emplace_back(word_str); 
				count++;
			}
			freq_title[word_str]++;
		}
	}
	for (map<string,double>::iterator it = freq_title.begin(); it != freq_title.end(); ++it) {
		it -> second = it -> second / title_word;
		freq[it -> first] += it -> second * t_weight;
	}
	fin.close();
	
	fin.open((file_name + suff_body).c_str());
	while (fin >> line) {
		istringstream istr(line);
		string word_str;
		while (istr >> word_str) {
			body_word++;
			if (resource.word_list.find(word_str) == resource.word_list.end()) {
				resource.word_list[word_str] = count;
				resource.word.emplace_back(word_str); 
				count++;
			}
			freq_body[word_str]++;
		}
	}
	for (map<string,double>::iterator it = freq_body.begin(); it != freq_body.end(); ++it) {
		it -> second = it -> second / body_word;
		freq[it -> first] += it -> second * b_weight;
	}
	fin.close();
	
	for (map<string,double>::iterator it = freq.begin(); it != freq.end(); ++it) {
		string word_str = it -> first;
		resource.word[resource.word_list[word_str]].add_docu(resource.docu_list[file_name], it -> second);
	}
	
	fin.close();
}
