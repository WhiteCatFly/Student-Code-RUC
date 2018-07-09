#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include <map>
#include "document.h"
#include "posting_list.h"

using std::vector;
using std::string;
using std::map;

class dictionary{
	private:
	int totaldoc;
	vector<string> Term;
	map<string, posting_list> indexer;
	
	public:
	dictionary();
	~dictionary(){}
	
	void add_doc(document);
	posting_list find_term(string);
	double idf(string);
};

#endif
