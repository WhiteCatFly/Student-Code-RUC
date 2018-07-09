#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include "Hits.h"
#include "document.h"
#include "posting_list.h"
#include "index_search.h"

using namespace std;

posting_list index_search::find_candidate(vector<string> query){
	posting_list cand;
	for(size_t i = 0; i < query.size(); i++){		
		cand += indexer.find_term(query[i]);
	}	
	return cand;
}

double index_search::cal_score(document q, document d){
	double score = 0;
	vector<double> cosq, cosd;
	for(size_t i = 0; i < q.size(); i++){
		string temp = q[i];
		double Cosq, Cosd;	
		Cosq = q.wtf(temp) * indexer.idf(temp);
		cosq.push_back(Cosq);
		Cosd = d.wtf(temp);
		cosd.push_back(Cosd);
	}
	double sumq = 0, sumd = 0;
	for(size_t i = 0; i < cosq.size(); i++){
		sumq += cosq[i] * cosq[i];
		sumd += cosd[i] * cosd[i];
	}
	sumq=sqrt(sumq);
	sumd=sqrt(sumd);
	for(size_t i = 0; i < cosq.size(); i++)
		score += cosq[i] * cosd[i];
	score = (score/sumq)/sumd;
	return score;
}

void index_search::search(string query){
	document Query(query,false);
	posting_list doc;
	doc = find_candidate(Query.Words());
	Hits result(rank);
	for(size_t i = 0; i < doc.size(); i++){
		double score = cal_score(Query, store[doc[i]]);
		result.insert(make_pair(doc[i], score));
	}
	if(doc.size() == 0){
		cout<<"sorry we can't find this word"<<endl;
		return;
	}
	result.print();
}


