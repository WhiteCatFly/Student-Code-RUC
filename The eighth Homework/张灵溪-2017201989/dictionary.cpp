#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include "posting_list.h"
#include "document.h"
#include "dictionary.h"

using namespace std;

dictionary::dictionary(){
	ifstream file("file_list.txt");
	string File_path;
	totaldoc = 0;
	while(file>>File_path){
		string url = File_path.substr(11);
		document init(totaldoc, File_path.c_str(), url, true);
		store.push_back(init);
		add_doc(init);
	}
	ifstream file1("stopwords.txt");
	string stop;
	while(file>>stop)
		stopwords.insert(stop);
}

void dictionary::add_doc(document doc){
	for(size_t i = 0; i<doc.size(); i++){
		if(indexer.count(doc[i]))
			indexer[doc[i]].add_post(doc.id(), doc.freq(doc[i]));
		else{
			Term.push_back(doc[i]);
			posting_list t(doc.id(),doc.freq(doc[i]));
			indexer[doc[i]] = t;
		}
	}
	totaldoc++;
}

double dictionary::idf(string term){
	if(indexer[term].size() == 0)
		return 0;
	return log10((double)totaldoc/indexer[term].size());
}
posting_list dictionary::find_term(string term){
	return indexer[term];
}
