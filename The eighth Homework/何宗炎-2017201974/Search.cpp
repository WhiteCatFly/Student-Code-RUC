#ifndef Search_Hzy_CPP_
#define Search_Hzy_CPP_
#include "global_settings.cpp"
#include "Search.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <cstring>
#include <math.h>

void TF(std::string s, db * res, std::map <std::string, Words> & Mp, std::vector <WebPage> & WP, bool SearchBody) {
	using namespace std;
	Words tmp = Mp[s];
	if(tmp.name != s) return;
	set <int>::iterator it;
	if(SearchBody)
	    for(it = tmp.ALL.begin(); it != tmp.ALL.end(); it++) res[*it] = (db) WP[*it].WordCounts_all[s] / (WP[*it].ALLWords_all + 50);
	else
	    for(it = tmp.Title.begin(); it != tmp.Title.end(); it++) res[*it] = (db) WP[*it].WordCounts_tit[s] / WP[*it].ALLWords_tit;
}

db IDF(std::string s, std::map <std::string, Words> & Mp, std::vector <WebPage> & WP, bool SearchBody) {
    using namespace std;
    Words tmp = Mp[s];
    if(tmp.name != s) return 0;
    int data_size = WP.size();
    if(SearchBody) return log2((db) data_size / (tmp.ALL.size() + 1)) ;
    else return log2((db) data_size / (tmp.Title.size() + 1));
}


void Search(std::vector <std::string> & words, std::map <std::string, Words> & Mp, std::vector <WebPage> & WP, int ShowLines, bool SearchBody) {
    using namespace std;
    int data_size = WP.size();
	db res[data_size + 10], tf[data_size + 10], idf;
	fill(res, res + data_size, 0.0);
	for(size_t i = 0; i < words.size(); ++i) {
	    fill(tf, tf + data_size, 0.0);
	    TF(words[i], tf, Mp, WP, SearchBody);
	    idf = IDF(words[i], Mp, WP, SearchBody);
	    for(int j = 0; j < data_size; ++j)
		res[j] += tf[j] * idf;
	}
	pair<db, int> rk[data_size + 10];
	for(int i = 0; i < data_size; ++i) rk[i] = make_pair(-res[i], i);
	sort(rk, rk + data_size);
	for(int i = 0; i < ShowLines; ++i) {
	    cout << WP[rk[i].second].name << endl;
	    WP[rk[i].second].ShowTitle();
	}
}

#endif
	
