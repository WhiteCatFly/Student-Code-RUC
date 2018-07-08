#include <map>
#include <vector>
#include "posting_list.h"

using namespace std;

posting_list::posting_list(int id, int freq){
	post.push_back(id);
	word_freq[id] = freq;
}

void posting_list::add_post(int id, int freq){
	post.push_back(id);
	word_freq[id] = freq;
}

posting_list posting_list::operator += (posting_list pl){
	for(size_t i = 0; i < pl.size(); i++)
		if(!word_freq.count(pl.post[i]))
			add_post(pl.post[i], pl.word_freq[pl.post[i]]);
	return *this;
}
