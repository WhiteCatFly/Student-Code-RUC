#include <string>
#include <cmath>
#include <set>
#include <fstream>
#include <sstream>
#include "document.h"
#include "../THULAC/include/thulac.h"

using namespace std;

vector<document> store;
set<string> stopwords;

double document::wtf(string word){
	if(word_freq.count(word))
		return 1+log10(word_freq[word]);
	else
	 	return 0;
}
void document::analyer(){
	char* model_path = "../THULAC/models";
	char* user_path = NULL;
	char separator = '_';
	int just_seg = 1;
	int ufilter = 0;
	int t2s = 0;
	THULAC test;	
	THULAC_result ans;
	test.init(model_path, user_path, just_seg, t2s, ufilter, separator);
	test.cut(content, ans);	
	for(int i=0;i<ans.size();i++){
		string temp = ans[i].first;
		if(stopwords.count(temp))
			continue;
		if(word_freq.count(temp))
			word_freq[temp]++;
		else{
			words.push_back(temp);
			word_freq[temp] = 1;
		}		
	}

}
void document::writer(){
	istringstream is(content);
	string temp;
	while(is>>temp){
		if(stopwords.count(temp))
			continue;
		if(word_freq.count(temp))
			word_freq[temp]++;
		else{
			words.push_back(temp);
			word_freq[temp] = 1;
		}	
	}	
}
document::document(const string& cont, bool seg){
	content = cont;
	if(seg){
		writer();
	}
	else
	analyer();	
	
}
	
document::document(int id, const char* dir, string Url, bool seg){
	url = Url;
	docID = id;
	string path(dir);
	path += ".body";
	ifstream file(path.c_str());
	string line;
	while(getline(file,line))
	content += line;
	string path2(dir);
	path2 += ".title";
	ifstream file2(path2.c_str());
	while(file2>>line)
		title += line;
	if(seg)
		writer();
	else
		analyer();
}
