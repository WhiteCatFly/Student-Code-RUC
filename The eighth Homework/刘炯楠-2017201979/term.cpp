#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include "term.h"
#include "document.h"
#include "structure.h"

int term::term_num = 0;

using namespace std;

term::term() {
	word = " ";
	idf = 0;
	tot_docu = 0;
}

term::term(const std::string & new_word) {
	term::term_num++;
	word = new_word;
	idf = 0;
	tot_docu = 0;
}

term::term(const term & term_ref) {
	word = term_ref.word;
	idf = term_ref.idf;
	tot_docu = term_ref.tot_docu;
	freq_list = term_ref.freq_list;
}

term & term::operator = (const term & term_ref) {
	if (this == &term_ref) {
		return *this;
	}
	word = term_ref.word;
	idf = term_ref.idf;
	tot_docu = term_ref.tot_docu;
	freq_list = term_ref.freq_list;
	return *this;
}

term::~term() {
}

string term::ret_word() const {
	return word;
}
	
void term::add_docu(int docu_pos, double freq) {
	tot_docu++;
	freq_list.push_back(make_pair(docu_pos, freq));
}

void term::calc_idf() {
	idf = (document::docu_num * 1.0) / (1.0 * tot_docu);
}

void term::make_docu(int vec_pos, data_res & resource) const {
	int size = freq_list.size();
	for (int i = 0; i < size;++i) {
		resource.docu[freq_list[i].first].add_term(resource.word_list[word], vec_pos, freq_list[i].second);
	}
}

double term::ret_idf() const {
	return idf;
}

ostream & operator << (ostream & os , const term & word_ref) {
	os << word_ref.word;
	int size = word_ref.freq_list.size();
	for (int i = 0;i < size; ++i) {
		os << ' ' << word_ref.freq_list[i].first << ' ' << word_ref.freq_list[i].second;
	}
}
