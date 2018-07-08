#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "structure.h"

class term{
private :
	std::string word;
	std::vector < std::pair<int,double> > freq_list;
	double idf;
	int tot_docu;
public :
	static int term_num;
	term();
	explicit term(const std::string & new_word); 
	term(const term & term_ref); 
	~term();
	
	std::string ret_word() const;	
	void add_docu(int docu_pos, double freq);
	void calc_idf();
	double ret_idf() const;
	void make_docu(int vec_pos, data_res & resource) const;	
		
	term & operator = (const term & term_ref);
	
	friend std::ostream & operator << (std::ostream & os , const term & word_ref);
};

#endif
