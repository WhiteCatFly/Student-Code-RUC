#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <string>
#include <vector>

class term;

class document{
private :
	std::string content;
	std::string title;
	std::string path;
	int len;
	double * coordination;
	int * term_pos;
public :
	static int docu_num;
	document();
	document(const std::string & str, bool kind, int len);
	document(const document & art);
	~document();
	
	document & operator = (const document & art);
	
	void mult_idf(const std::vector<term> & word);
	void regularize_crd();
	void add_term(int word_pos, int vec_pos, double freq);
	double length() const;
	std::string ret_title() const;
	std::string ret_content() const;
	std::string ret_path() const;
	
	friend double operator ^ (const document & a, const document & b);
};


static const std::string suff_body = ".body";
static const std::string suff_title = ".title";

#endif
