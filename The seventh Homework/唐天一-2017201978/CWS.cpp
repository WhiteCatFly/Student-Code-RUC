#include "HMM.h"
#include <iostream>
#include <fstream>
#include <cmath>

void HMM::CWS(){
	ifstream sen_in;
	sen_in.open("sentence.in");
	sen_in >> sentence;
	
	int pos = sentence.length() - 1;
	double dp[pos + 10];
	int trans[pos + 10] = {0};
	for (int i = 0; i < sentence.size(); ++i){
		double tmp_max = DOUBLE_MIN;
		int id = 0;
		for (int j = 0; j <= i; ++j){
			string sub = sentence.substr(j, i - j + 1);
			if (word_freq.count(sub)){
				double freq = (double)word_freq[sub] / word_total;
				if (log(freq) + (j ? dp[j - 1] : 0) > tmp_max)
					tmp_max = log(freq) + (j ? dp[j - 1] : 0), id = j;
			}
		}
		dp[i] = tmp_max, trans[i] = id;
	}
	
	while (pos > 0){
		dived_sen = sentence.substr(trans[pos], pos - trans[pos] + 1) + " " + dived_sen;
		pos = trans[pos] - 1;
	}
	if (out_flag)
		cout << dived_sen << endl;
}
