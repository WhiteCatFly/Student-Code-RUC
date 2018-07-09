#include <iostream>
#include <fstream>
#include "corpus.h"

std::map< std::string, std::vector<std::string> > words;
std::map< std::pair<std::string, std::string>, double > freq;
std::map< std::pair<std::string, std::string>, double > p_matrix;
std::map< std::string, double > word_freq;
int word_count;
static std::map< std::string, int > parts_number;
static std::vector<std::string> part_list;

using namespace std;

void make_database() {
	ofstream fout;
	fout.open(database);
	fout<<0<<endl;
	fout<<word_count<<endl;
	for (map <string, double>::iterator it = word_freq.begin(); it != word_freq.end(); ++it) {
		fout<<it -> first<<' '<<it -> second<<endl;
	}
	fout<<1<<endl;
	for (map< string, vector<string> >::iterator it = words.begin(); it != words.end(); ++it) {
		int size = (it -> second).size();
		fout << it -> first <<' ';
		for (int i = 0; i < size; ++i)
			fout << (it -> second)[i] << ' ';
		fout<<endl;
	}
	fout<<2;
	string last = "";
	for (map<pair<string, string>, double>::iterator it = freq.begin(); it != freq.end(); ++it) {
		pair<string, string> pr = it -> first;
		double val = it -> second;
		if (last != pr.first) {
			fout<<endl;
			fout<<pr.first<<' ';
		}
		fout<<pr.second<<' '<<val<<' ';
		last = pr.first;
	}
	fout<<endl<<3;
	last = "";
	int cnt = 0;
	for (map<pair<string, string>, double>::iterator it = p_matrix.begin(); it != p_matrix.end(); ++it) {
		pair<string, string> pr = it -> first;
		double val = it -> second;
		if (last != pr.first) {
			cnt = 0;
			fout<<endl;
			fout<<pr.first<<' ';
		}
		cnt++;
		fout<<pr.second<<' '<<val<<' ';
		last = pr.first;
	}
}

void add_word(string word, string part) {
	int size = words[word].size();
	bool flag = true;
	for (int i = 0; i < size; ++i)
		if (words[word][i] == part) {
			flag = false;
			break;
		}
	if (flag)
		words[word].push_back(part);
		
	pair<string, string> pr = make_pair(part, word);
	freq[pr]++;
	
	size = part_list.size();
	flag = true;
	for (int i = 0; i < size; ++i) 
		if (part_list[i] == part) {
			flag = false;
			break;
		}
	if (flag) {
		part_list.push_back(part);
	}
	word_count++;
	word_freq[word]++;
}

void add_matrix(string part_1, string part_2) {
	pair<string, string> pr = make_pair(part_1, part_2);
	p_matrix[pr]++;
	parts_number[part_1]++;
}

void normalize() {
	part_list.push_back(start);
	int part_count = part_list.size();
	for (int i = 0;i < part_count; ++i)
		for (int j = 0;j < part_count; ++j)
			add_matrix(part_list[i], part_list[j]);
	
	for (map<pair<string, string>, double>::iterator it = freq.begin(); it != freq.end(); ++it) {
		pair<string, string> pr = it -> first;
		double val = it -> second;
		it -> second = val / (1.0 * parts_number[pr.first]);
	}
	
	for (map<pair<string, string>, double>::iterator it = p_matrix.begin(); it != p_matrix.end(); ++it) {
		pair<string, string> pr = it -> first;
		double val = it -> second;
		it -> second = val / (1.0 * parts_number[pr.first]);
	}
	
	for (map<string, double>::iterator it = word_freq.begin(); it != word_freq.end(); ++it) {
		it -> second = it -> second / word_count;
	}
	
}
