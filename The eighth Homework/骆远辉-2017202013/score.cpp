#include"score.h"
#include"index.h"
#include"document.h"
#include<sstream>
#include<set>
#include<cmath>
#include<map>
#include<utility>

using namespace std;

extern map<int,Doc> collection;
extern map<string,Dict> index_;
extern int cnt_collection;
extern int cnt_allword;

void answer(const string& query,int topk) {
	set<int> docs; //all the query term's posting docID
	map<int,double> score; //the score of term-docs (is a cos
	map<int,double> len_td; //the len of doc (used to cal the cos) 
	istringstream is(query); 
	multiset<string> allterm; //all the term word
	
	string tmpword;
	while(is >> tmpword) {
		allterm.insert(tmpword);
	}
	double len_tq = 0; //the len of term-query 
	for(multiset<string>::iterator beg = allterm.begin(); beg != allterm.end(); beg++) { 
		string term = *beg;
		double w_tq; //the weight of term-query; tf.idf
		if (index_.count(term) == 0) {
			//not in the dictionary, ignore it
			continue;
		}
cout << term << "begin to cal" << endl;
		
		Dict t = index_[term];
		w_tq = cal_tf(allterm.count(term)); //* tq_idf;
		len_tq = len_tq + w_tq * w_tq;
		
		Post tpost = t.extract_posting();
		for (int i = 1, maxi = tpost.get_docnum(); i <= maxi;i++){
			int ID = tpost[i];
			docs.insert(ID);
			if (w_tq == 0) {
				if (score.count(ID) == 0) { //haven't scored, initiate it
					score[ID] = 0;
					len_td[ID] = 0;
				}
			}
			else { 
				double w_td = 0;
				w_td = cal_tf(tpost.get_wordcnt(i)) * t.cal_idf();
				score[ID] = score[ID] + w_td * w_tq;
				len_td[ID] = len_td[ID] + w_td * w_td * w_tq * w_tq;
			}
		}	
	}		
	for(set<int>::iterator beg = docs.begin(); beg != docs.end(); beg++) {
		int ID = *beg;
		score[ID] = score[ID] / (len_tq * len_td[ID]);
	}
	output(score,topk);	
}

double cal_tf(int t) {
	return (1 + log10(t));
}

void output(map<int,double>& sc,int topk) {
cout << "begin to output" << endl;
	multimap<double,int> isc; //inverse score map
	for (map<int,double>::iterator beg = sc.begin(); beg != sc.end(); beg++) {
cout << "111111111111111111111111" << endl;
		isc.insert(pair<double,int>(beg->second,beg->first));
	}
	multimap<double,int>::reverse_iterator itr = isc.rbegin();
	for(int i = 1; itr != isc.rend() && i <= topk;i++, itr++) { // may be wrong
		int ID = itr->second;		
		Doc tdoc = collection[ID];
		tdoc.output(cout);
	}
		
}
