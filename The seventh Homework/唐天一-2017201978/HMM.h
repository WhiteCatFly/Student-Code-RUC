#ifndef HMM_H
#define HMM_H

#include <vector>
#include <string>
#include <map>
using namespace std;

const double DOUBLE_MIN = -1e200;
const string NWORD = "###";

class HMM{
private:
	int word_total;
	vector<string> lang_source;
	map<string, int> word_freq;
	map<pair<string, string>, int> part_trans;
	map<string, int> part_total;
	map<pair<string, string>, int> word_part_trans;
	map<string, vector<string> > word_part_list;
	
	bool out_flag;
	string sentence, dived_sen;

public:
	HMM();
	void pre_treatment();
	void CWS();
	void POS();
	void find_ans(int dep, vector<string> & word, double & max_pro, vector<string> & now_trans, vector<string> & ans_trans);
};

#endif
