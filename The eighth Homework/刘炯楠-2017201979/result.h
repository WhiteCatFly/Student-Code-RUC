#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <string>
#include <vector>

#include "document.h"

class result{
private :
	int num;
	std::string page_url;
	double score;
public :
	result();
	result(int docu_pos, const document & question, const std::vector<document> & docu);
	~result();
	int ret_num() const;
	std::string ret_url() const;
	double ret_score() const {return score;}
	
	friend bool operator < (const result &a, const result &b);
};

static const int pred_name_len = 16;
static std::string make_url(const std::string & path);

#endif
