#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "my_regex.h"
#include "html_text.h"
#include "normalization.h"

using namespace std;

static const string kind_str = "-S";
static const string kind_file = "-F";
static const string redirect = " -> ";

void wrong_put() {
	cerr << "wrong!" << endl;
	cerr << "the standord format is :" << endl;
	cerr << "./html_parser -S string or html_parser -F filename page_name" << endl;
}

void help_put() {
	cout << "input -1 to exit" << endl;
	cout << "input 0 to get url" << endl;
	cout << "input 1 to get text" << endl;
	cout << "input 2 to get title" << endl;
	cout << "input 3 to use your regex" << endl;
	cout << "input 4 to make the tree strcuture" << endl;
	cout << "input 5 to change the source html" << endl;
	cout << "[1-4] -> filename means print to the file (default stdout)" << endl;
	cout << "5 is same to the initialize" << endl;
}

void out(const string & instruction, int count, string * & list) {
	if (instruction.find(redirect) != string::npos) {
		int length = instruction.length();
		int pos = instruction.find(redirect) + redirect.length();
		string temp = "";
		for (int i = pos;i < length; ++i)
			temp = temp + instruction[i];
		ofstream ofs;
		ofs.open(temp.c_str(), ios::ate);
		if (count >= 1)
			ofs << count << endl;
		for (int i = 0;i < max(1, count); ++i)
			ofs << list[i] << endl;
		ofs.close();
	}
	else {
		if (count >= 1)
			cout << count << endl;
		for (int i = 0;i < max(1, count); ++i)
			cout << list[i] << endl;
	}
}

string make_pattern(const string & instruction) {
	int length = instruction.length();
	int pos;
	string pattern = "";
	for (int i = 1;i < length;++i)
		if (instruction[i] != ' ') {
			pos = i;
			break;
		}
	int redirect_pos = instruction.find(redirect);
	if (redirect_pos == -1)
		redirect_pos = length;
	for (int i = pos;i < redirect_pos; ++i)
		pattern = pattern + instruction[i];
	return pattern;
}

static const int argu_number = 4;
void initialize(html_text & text, int argc, const char ** argv) {
	if (argc != argu_number) {
		wrong_put();
		exit(1);
	}
	else {
		string arg[argu_number - 1];
		for (int i = 0 ; i < argu_number - 1;++i)
			arg[i] = argv[i + 1];
		if ((arg[0] != kind_str) && (arg[0] != kind_file)) {
			wrong_put();
			exit(1);
		}
		string page_name = arg[2];
		cout<<page_name<<endl;
		if (page_name[page_name.length() - 1] != seperate_sign)
			page_name = page_name + seperate_sign;
		if (arg[0] == kind_str) {
			istringstream istr(arg[1]);
			text = html_text(istr, page_name);
		}
		if (arg[0] == kind_file) {
			ifstream ifs(arg[1]);
			text = html_text(ifs, page_name);
		}
	}
}

void change_source(html_text & text, const string argu) {
	int pos_f = argu.find(kind_file);
	int pos_s = argu.find(kind_str);
	string ifs_name = "";
	string page_name;
	if (pos_f != string::npos) {
		int start = pos_f + kind_file.length() + 1;
		int plc;
		for (plc = start; argu[plc] != ' ';++plc)
			ifs_name = ifs_name + argu[plc];
		ifstream ifs(ifs_name);
		page_name = argu.substr(plc+1);
		if (page_name[page_name.length() - 1] != seperate_sign)
			page_name = page_name + seperate_sign;
		text = html_text(ifs,page_name);
	}
	if (pos_s != string::npos) {
		int start = pos_f + kind_file.length() + 1;
		int plc;
		for (plc = start; argu[plc] != ' ';++plc)
			ifs_name = ifs_name + argu[plc];
		ifstream ifs(ifs_name);
		page_name = argu.substr(plc+1);
		if (page_name[page_name.length() - 1] != seperate_sign)
			page_name = page_name + seperate_sign;
		text = html_text(ifs,page_name);
	}
}

int main(int argc,const char ** argv) {
	html_text text;
	initialize(text, argc, argv);
	string instruction;
	while (true) {
		help_put();
		getline(cin,instruction);
		if (instruction.find( "-1" ) == 0) break;
		string * list = new string[maxnumber];
		if (instruction.find( "0" ) == 0) {
			int count = text.find_url(list);
			out(instruction, count, list);
		}
		if (instruction.find("1") == 0) {
			int count = text.find_text(list);
			out(instruction, count, list);
		}
		if (instruction.find("2") == 0) {
			int count = text.find_title(list);
			out(instruction, count, list);
		}
		if (instruction.find("3") == 0) {
			string pattern = make_pattern(instruction);
			int count = text.find_by_regex(pattern, list);
			out(instruction, count, list);
		}
		if (instruction.find("4") == 0) {
			text.make_tree_structure(list);
			out(instruction, -1, list);
		}
		if (instruction.find("5") == 0) {
			change_source(text, instruction);
		}
		delete[] list;
	}
}
