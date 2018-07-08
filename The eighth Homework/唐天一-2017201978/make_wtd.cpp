#include "Info_Ret.h"

#include <fstream>
#include <sstream>
#include <cmath>
using std::ifstream;
using std::istringstream;

void Info_Ret::make_wtd(){
	web_num = 0;
	
	ifstream fin;
	fin.open("file_list.txt");
	string web_path;
	while (fin >> web_path){
		web_num++;
		ifstream webin;
		webin.open((web_path + ".body").c_str());
		string body;
		web_body.push_back(body);
		
		int word_tot = 0;
		map<string, int> word_count;
		vector<string> word_list;
		
		while (getline(webin, body)){
			istringstream wordin(body);
			string word;
			while (wordin >> word){
				web_body[web_num - 1] += word;
				word_tot++;
				if (!word_count.count(word))
					word_list.push_back(word);
				word_count[word]++;
			}
			web_body[web_num - 1] += '\n';
		}
		
		map<string,double> tmp_wtd;
		for (auto i = word_list.begin(); i != word_list.end(); ++i)
			tmp_wtd[*i] = (1 + log(word_count[*i])) * log((double)word_tot / word_count[*i]);
		wtd.push_back(tmp_wtd);
	}
}
