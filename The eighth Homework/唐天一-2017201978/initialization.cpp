#include "Info_Ret.h"

#include <fstream>
using std::ifstream;

Info_Ret::Info_Ret(){
	web_num = 0;
	
	ifstream fin;
	fin.open("file_list.txt");
	string web_path;
	while (fin >> web_path){
		web_num++;
		
		ifstream webin;
		webin.open((web_path + ".title").c_str());
		string title;
		web_title.push_back(title);
		while (webin >> title)
			web_title[web_num - 1] += title;
	}
	fin.close();
	fin.open("stop_words.txt");
	string word;
	while (fin >> word)
		stop_words[word] = 1;
	
	make_wtd();
}
