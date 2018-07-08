#include <cctype>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "corpus.h"
#include "sent_processor.h"
#include "data_processor.h"

using namespace std;
/*
extern std::map< std::pair<std::string, std::string>, double > p_matrix;
extern std::map< std::string, std::vector<std::string> > words;
extern std::map< std::pair<std::string, std::string>, double > freq;
*/
void make_data() {
	ifstream fin;
	fin.open(database);
	if (fin.is_open() == false) {
		string file = corpus;
		for (int i = 1; i <= file_number; ++i) {
			file[change_plc] = '0' + i;
			read_from_corpus(file.c_str());
			cout<<i<<endl;
		}
		normalize();
		make_database();
	}
	else {
		read_from_database(database);
	}
}

void make_word(vector<string> & vs, string sentence) {
	int length = sentence.length();
	int pos = 0;
	while (pos < length) {
		int len = 0;
		if (sentence[pos] > 0) {
			len = n_len;
		}
		else len = w_len;
		string character = sentence.substr(pos, len);
		pos+=len;
		if (len == n_len && isspace(character[0]))
			continue;
		vs.push_back(character);
	}
}

static string pattern;
static ifstream ifs;
static ofstream ofs;
void arg(int argc, char ** argv) {
	if (argc == 1) {
		cout<<"the format is : "<<endl;
		cout<<"--stage arg(pos or ws)"<<endl;
		cout<<"--input arg(default stdin)"<<endl;
		cout<<"--output arg(default stdout)"<<endl;
		exit(0);
	}
	string * list = new string [argc];
	for (int i = 0;i < argc; ++i) {
		list[i] = argv[i];
	}
	for (int i = 1;i < argc; ++i) {
		if (list[i] == "--stage")
			pattern = list[i + 1];
		if (list[i] == "--input") {
			ifs.open("main.in");
			cin.rdbuf(ifs.rdbuf());
		}
		if (list[i] == "--output") {
			ofs.open(list[i + 1].c_str());
			cout.rdbuf(ofs.rdbuf());
		}
	}
	delete[] list;
}

int main(int argc, char **argv) {
	make_data();
	arg(argc,argv);
	
	string sentence;
	
	while (getline(cin, sentence)) {
		vector<string> character;
		string sent;
		make_word(character, sentence);
		sent = word_split(character);
		if (pattern == "ws") {
			cout<<sent<<endl;
		}
		if (pattern == "pos") {
			tag(sent, cout);
		}
	}
}
