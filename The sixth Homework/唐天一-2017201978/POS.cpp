#include "HMM.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

void HMM::find_ans(int dep, vector<string> & word, double & max_pro, vector<string> & now_trans, vector<string> & ans_trans){
	if (dep == word.size()){
		double now_pro = 0;
		for (int i = 0; i < dep; ++i){
			now_pro += log((double)part_trans[make_pair(now_trans[i], (i ? now_trans[i - 1] : NWORD))] / part_total[(i ? now_trans[i - 1] : NWORD)]);
			now_pro += log((double)word_part_trans[make_pair(word[i], now_trans[i])] / part_total[now_trans[i]]);
		}
		if (now_pro > max_pro)
			max_pro = now_pro, ans_trans = now_trans;
	}
	else{
		for (int i = 0; i < word_part_list[word[dep]].size(); ++i){
			now_trans[dep] = word_part_list[word[dep]][i];
			find_ans(dep + 1, word, max_pro, now_trans, ans_trans);
		}
	}
}

void HMM::POS(){
	ifstream sen_in;
	sen_in.open("sentence.in");
	sen_in >> sentence;
	out_flag = 0;
	CWS();
	
	istringstream word_in(dived_sen);
	string tmp;
	vector<string> word;
	word.clear();
	while (word_in >> tmp)
		word.push_back(tmp);
	
	double max_pro = DOUBLE_MIN;
	vector<string> now_trans;
	now_trans.clear();
	now_trans.resize(word.size());
	vector<string> ans_trans;
	ans_trans.clear();
	ans_trans.resize(word.size());
	find_ans(0, word, max_pro, now_trans, ans_trans);
	for (int i = 0; i < word.size(); ++i)
		cout << word[i] << '/' << ans_trans[i] << ' ';
	cout << endl;
}
