#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::map;

class document{
	private:
	int docID;
	string url, content;
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
	vector<string> Words(){return words;}
	
	void writer();
	double wtf(string);
		
	string operator [] (int i){return words[i];}
	
};

extern vector<document> store;

#endif
