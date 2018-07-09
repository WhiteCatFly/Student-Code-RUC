#include "Info_Ret.h"
#include "segment_dll.h"
#include <algorithm>
using std::pair;
using std::make_pair;

bool cmp(pair<double, int> a, pair<double, int> b){
	return a.first > b.first;
}

void Info_Ret::search(string str){
	vector< pair<double, int> > score_sort;
	
	vector<string> word;
	void * engine = 0;
	engine = segmentor_create_segmentor("cws.model");
	const char * suite = str.c_str();
	int word_num = segmentor_segment(engine, suite, word);
	//segmentor_release_segmentor(engine);
	
	for (int i = 0; i < web_num; ++i){
		double score = 0;
		for (int j = 0; j < word_num; ++j)
			if (wtd[i].count(word[j]) && !stop_words.count(word[j]))
				score += wtd[i][word[j]];
		score_sort.push_back(make_pair(score, i));
	}
	sort(score_sort.begin(), score_sort.end(), cmp);
	for (int i = 0; i <= 9; ++i){
		int id = score_sort[i].second;
		cout << "\033[1m" << web_title[id] << "\033[0m" << endl;
		for (int j = 0; j < max_out_len; ++j)
			cout << web_body[id][j];
		cout << "..." << endl << endl;
	}
}
