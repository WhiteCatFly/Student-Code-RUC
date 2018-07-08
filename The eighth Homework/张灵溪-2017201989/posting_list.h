#ifndef POSTING_LIST_H
#define POSTING_LIST_H

#include <vector>
#include <map>

using std::map;
using std::vector;

class posting_list{
	
	private:
	vector<int> post;
	map<int, int> word_freq;
	
	public:
	posting_list(int, int);
	posting_list(){};
	void add_post(int id, int freq);
	size_t size()const{return post.size();};
	
	posting_list operator += (posting_list);
	size_t operator [] (size_t i)const{return post[i];}
	
};

#endif
