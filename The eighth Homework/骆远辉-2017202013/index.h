#ifndef _INDEX_
#define _INDEX_

#include"document.h"

#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;



class Post {
private:
	vector<int> docIDs;
	vector<int> cnt_word;
	//vector<int> pos; // neglect temporally
	int cnt; // frequency
public:
	Post() : cnt(0) {}
	void add(int ID) {
		if(cnt == 0) {
			docIDs.push_back(ID);
			cnt++;
			cnt_word.push_back(1);
			return;
		}
		else{
			for(int i = 0;i < cnt; i++)
				if(docIDs[i] == ID) {
					 cnt_word[i]++;
					 return;
				}
			cnt++;
			docIDs.push_back(ID);
			cnt_word[cnt] = 1;
		}
	}
  	int get_docnum() const { return cnt; }
	int get_wordcnt(int i) const { return cnt_word[i];} 
	int operator [](int i) const { return docIDs[i];}
};

class Dict {
private:
	string word;
	int cnt;
	double idf;
	Post posting; // int stores docID vector<int>stores [0] the frequency N [1-N] the position of the document
public:
	Dict() : cnt(0), idf(0) {}
	Dict(const string& s,int ID) : word(s) , cnt(1) {
		posting.add(ID);
	}
	void add(int ID) {
		cnt++;
		posting.add(ID);
	}
	double cal_idf() {
		const double EPS = 1e-10;
		if ( (idf - 0 ) < EPS) {
			idf = log10(cnt_collection/posting.get_docnum());
		}
		else return idf;			
	}
	Post & extract_posting() {
		return posting;
	}
};

void add_index(const string& tmpp,int);
extern int cnt_allword;

#endif
