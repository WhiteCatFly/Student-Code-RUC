#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>
#include <set>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::map;
using std::set;

class document{
	private:
	int docID;
	string url, content, title;
	vector<string> words;
	map<string, int> word_freq;
	
	void analyer();
	
	public:
	document(int, const char*, string, bool);
	document(const string&, bool);	
	~document(){}
		
	size_t size(){return words.size();}
	int id(){return docID;}
	int freq(string temp){return word_freq[temp];}
	string Url(){return url;}
	string Title(){return title;}
	vector<string> Words(){return words;}
	
	void writer();
	double wtf(string);
		
	string operator [] (int i){return words[i];}
	
};

extern vector<document> store;
extern set<string> stopwords;

#endif
