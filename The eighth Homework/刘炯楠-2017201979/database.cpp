#include <cstdlib>
#include <utility>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

#include "database.h"
#include "term.h"
#include "document.h"
#include "structure.h"

using namespace std;

bool database_exist() {
	ifstream fin;
	fin.open(database.c_str());
	bool status = fin.is_open();
	fin.close();
	return status;
}

data_res initialize_from_database() {
	data_res resource;
	ifstream fin;
	fin.open(database);
	string line;
	string file_name;
	int status = 0;
	int cnt = 0;
	while (getline(fin, line)) {
		if (line == document_sign) {
			status = 1;
			getline(fin, line);
			istringstream istr(line);
			istr >> document::docu_num;
			cnt = 0;
			continue;
		}
		if (line == term_sign) {
			status = 2;
			cnt = 0;
			continue;
		}
		if (status == 1) {
			file_name = line;
			resource.docu.emplace_back(file_name, 0, 1);
			resource.docu_list[file_name] = cnt;
			cnt++;
		}
		if (status == 2) {
			istringstream istr(line);
			string word_str;
			istr >> word_str;
			resource.word_list[word_str] = cnt;
			resource.word.emplace_back(word_str);
			int docu_pos;
			double freq;
			while (istr >> docu_pos >> freq) {
				resource.word[cnt].add_docu(docu_pos, freq);
			}
			resource.word[cnt].calc_idf();
			cnt++;
		}
	}
	fin.close();
	return resource;
}

void output_to_database(const data_res & resource) {
	ofstream fout;
	fout.open(database);
	
	fout << document_sign << endl;
	fout << document::docu_num << endl;
	for (int i = 0; i < document::docu_num; ++i) {
		fout << resource.docu[i].ret_path() << endl;
	}
	
	fout << term_sign << endl;
	for (int i = 0; i < term::term_num; ++i) {
		fout << resource.word[i] << endl;
	}
	
	fout.close();
}
