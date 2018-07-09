#include "search_engine.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef pair<string, double> psd;

Doc::Doc() {
	n = 0;
}

Doc::Doc(const string & file_path) {
	ifstream fin(file_path.c_str());
	if(!fin.is_open()) {
		cerr << "failed to open " << file_path << endl;
		exit(-1);
	}
	
	path = file_path;
	n = 0;
	string s;
	while(fin >> s) {
		if(mp.find(s) == mp.end()) {
			mp[s] = n++;
			/*term.push_back(s);
			tf.push_back(1);*/
			term.push_back(psd(s, 1));
		}
		else /*tf[mp[s]]++;*/term[mp[s]].second++;
	}
	for(int i = 0; i < n; i++) {
		term[i].second = 1 + log10(term[i].second);
	}
}

Doc::Doc(const vector<string> & vec) {
	n = 0;
	for(auto i = vec.begin(); i != vec.end(); i++) {
		if(mp.find(*i) == mp.end()) {
			mp[*i] = n++;
			/*term.push_back(*i);
			tf.push_back(1);*/
			term.push_back(psd(*i, 1));
		}
		else /*tf[mp[s]]++;*/term[mp[*i]].second++;
	}
	for(int i = 0; i < n; i++) {
		term[i].second = 1 + log10(term[i].second);
	}
}

SE::SE() {
	ifstream fin("file_list.txt");
	if(!fin.is_open()) {
		cerr << "failed to open data/file_list.txt" << endl;
		exit(-1);
	}

	dn = tn = 0;
	string file_path;
	while(fin >> file_path) {
		Doc t(file_path + ".body");
		d[dn] = t;
		for(int i = 0; i < d[dn].N(); i++) {
			if(mp.find(d[dn][i].first) == mp.end()) {
				mp[d[dn][i].first] = tn++;
				idf.push_back(1);
			}
			else idf[mp[d[dn][i].first]]++;
		}
		dn++;
	}
	for(int i = 0; i < dn; i++) {
		idf[i] = log10(dn / idf[i]);
	}
}

inline double sq(double x) {
	return x * x;
}

void SE::search(const Doc & q, int k) const {
	if(dn < k) k = dn;
	pair<double, int> score[N];
	memset(score, 0, sizeof score);
	for(int i = 0; i < dn; i++) {
		double sq1 = 0, sq2 = 0;
		bool flag = 0;
		for(int j = 0; j < q.N(); j++) {
			string s = q[j].first;
			if(mp.find(s) == mp.end()) continue;
			if(d[i].has(s)) {
				flag = 1;
				score[i].first += d[i][s] * q[j].second * idf[mp.at(s)];
				sq1 += sq(d[i][s]);
			}
			sq2 += sq(q[j].second * idf[mp.at(s)]);
		}
		if(flag) score[i].first /= sqrt(sq1) * sqrt(sq2);
		score[i].second = i;
	}
	sort(score, score + dn);
	for(int i = dn - 1; i >= dn - k; i--) {
		cout << d[score[i].second].Path() << endl;
	}
}

