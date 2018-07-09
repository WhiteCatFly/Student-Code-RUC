#include <iostream>
#include <fstream>
#include <sstream>
#include "data_processor.h"
#include "corpus.h"

extern std::map< std::string, std::vector<std::string> > words;
extern std::map< std::pair<std::string, std::string>, double > freq;
extern std::map< std::pair<std::string, std::string>, double > p_matrix;
extern std::map< std::string, double > word_freq;
extern int word_count;
using namespace std;

string get_part(string text) {
	int pos = text.find(seperate_sign);
	text = text.substr(pos + 1);
	if ((pos = text.find(seperate_sign)) != string::npos) 
		return text.substr(0, pos);
	return text; 
}

string get_word(string text) {
	int pos = text.find(seperate_sign);
	return text.substr(0, pos);
}

void read_from_corpus(const char * name) {
	ifstream fin;
	fin.open(name);
	string line;
	while (getline(fin, line)) {
		istringstream ifs(line);
		string text;
		int count = 0;
		string last_part = start;
		bool flag = false;
		while (ifs>>text) {
			count++;
			if (count == 1) 
				continue;
			if (text.find(br_st) != string::npos) {
				flag = true;
				continue;
			} 
			if (flag)
				continue;
			if (text.find(br_en) != string::npos) {
				flag = false;
				continue;
			} 
			string word = get_word(text);
			string part = get_part(text);
			if (word == "") continue;
			add_word(word,part);
			add_matrix(last_part, part);
			last_part = part;
		}
	}
}


void read_from_database(const char * name) {
	ifstream fin;
	fin.open(name);
	string line;
	int status = -1;
	while (getline(fin, line)) {
		if (line == "0") {
			status = 0;
			fin>>word_count;
			continue;
		}
		if (line == "1") {
			status = 1;
			continue;
		}
		if (line == "2") {
			status = 2;
			continue;
		}
		if (line == "3") {
			status = 3;
			continue;
		}
		if (status == 0) {
			istringstream ifs(line);
			string word;
			double per;
			ifs>>word>>per;
			word_freq[word] = per;
		}
		if (status == 1) {
			istringstream ifs(line);
			string word;
			ifs>>word;
			string part;
			while (ifs>>part)
				words[word].push_back(part);
		}
		if (status == 2) {
			istringstream ifs(line);
			string part;
			ifs>>part;
			string word;
			while (ifs>>word) {
				double per;
				ifs>>per;
				pair<string, string> pr = make_pair(part, word);
				freq[pr] = per;
			}
		}
		if (status == 3) {
			istringstream ifs(line);
			string part;
			ifs>>part;
			string to_part;
			while (ifs>>to_part) {
				double per;
				ifs>>per;
				pair<string, string> pr = make_pair(part, to_part);
				p_matrix[pr] = per;
			}
		}
	}
}
