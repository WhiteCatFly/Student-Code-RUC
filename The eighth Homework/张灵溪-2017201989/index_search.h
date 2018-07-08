#ifndef INDEX_SEARCH_H
#define INDEX_SEARCH_H

#include <vector>
#include <string>
#include "dictionary.h"
#include "document.h"
#include "posting_list.h"

using std::string;
using std::vector;

class index_search{
	private:
	size_t rank;
	dictionary indexer;
	
	posting_list find_candidate(vector<string>);
	double cal_score(document, document);
	
	public:
	index_search(const dictionary& dic, size_t rk = 5) :  rank(rk), indexer(dic){}
	~index_search(){}
	void search(string query);
	
};

#endif
