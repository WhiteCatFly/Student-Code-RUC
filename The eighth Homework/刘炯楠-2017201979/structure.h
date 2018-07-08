#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include <map>
#include <vector>

class term;

class document;

struct data_res{
	std::vector<document> docu;
	std::map<std::string, int> docu_list;
	std::vector<term> word;
	std::map<std::string, int> word_list;
};

#endif
