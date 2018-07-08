#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "processor.h"
#include "document.h"

using namespace std;

void help_out() {
	cout << "help instruction:" << endl; 
	cout << "./main\n\t--input input_file(default stdin)\n\t--output output_file(default stdout)\n\t--path root_path(default ./data/file_list.txt)\n" << endl;
}

static ifstream fin;
static ofstream fout;

string argument_processor(int argc, char ** argv) {
	string * list = new string [argc];
	for (int i = 0; i < argc; ++i) {
		list[i] = argv[i];
		//cout<<list[i]<<endl;
		if (list[i] == help) {
			help_out();
			exit(1);
		}
	}
	string root_path = default_root_path;
	for (int i = 1; i < argc; ++i) {
		if (list[i] == input) {
			string pattern = list[i + 1];
			fin.open(pattern.c_str());
			cin.rdbuf(fin.rdbuf());
		}
		if (list[i] == output) {
			string pattern = list[i + 1];
			fout.open(pattern.c_str());
			cout.rdbuf(fout.rdbuf());
		}
		if (list[i] == path) {
			root_path = list[i + 1];
		}
	}
	delete[] list;
	return root_path;
}
