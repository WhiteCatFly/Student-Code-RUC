#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "document.h"
#include "term.h"

int document::docu_num = 0;

using namespace std;

document::document() {
	content = title = path = "";
	coordination = NULL;
	term_pos = NULL;
	len = 0;
}

document::document(const string & str, bool kind,int size) {
	if (kind == 0) {
		ifstream fin;
		path = str;
		
		fin.open((path + suff_title).c_str());
		string line;
		title = "";
		while (getline(fin, line)) {
			title = title + line;
		}
		fin.close();
		
		fin.open((path + suff_body).c_str());
		content = "";
		while (getline(fin, line)) {
			content = content + line + "\n";
		}
		fin.close();
	}
	else {
		path = title = "";
		content = str;
	}
	
	len = size;
	coordination = new double [size];
	term_pos = new int [size];
	
	for (int i = 0; i < len; ++i) {
		coordination[i] = 0.0;
		term_pos[i] = -1;
	}
}

document::document(const document & art) {
	content = art.content;
	path = art.path;
	title = art.title;
	len = art.len;
	
	coordination = new double [len];
	for (int i = 0;i < len;++i) {
		coordination[i] = art.coordination[i];
	}
	
	term_pos = new int [len];
	for (int i = 0;i < len;++i)
		term_pos[i] = art.term_pos[i];
}

document::~document() {
	delete[] coordination;
	delete[] term_pos;
}

double document::length() const{
	double ret = 0;
	for (int i = 0; i < len; ++i)
		ret = ret + (coordination[i] * coordination[i]);
	ret = sqrt(ret);
	return ret;
}

string document::ret_title() const {
	return title;
}

string document::ret_content() const {
	return content;
}

string document::ret_path() const {
	return path;
}

document & document::operator = (const document & art) {
	if (this == &art) {
		return *this;
	}
	path = art.path;
	content = art.content;
	title = art.title;
	len = art.len;

	delete[] coordination;
	coordination = new double [len];
	for (int i = 0;i < len;++i) {
		coordination[i] = art.coordination[i];
	}
	
	delete[] term_pos;
	term_pos = new int [len];
	for (int i = 0;i < len;++i) {
		term_pos[i] = art.term_pos[i];
	}
		
	return *this;
}

void document::add_term(int word_pos, int vec_pos, double freq) {
	coordination[vec_pos] += freq;
	term_pos[vec_pos] = word_pos;
}

void document::mult_idf(const vector<term> & word) {
	for (int i = 0;i < len; ++i) {
		if (term_pos[i] != -1) {
			coordination[i] = coordination[i] * log(word[term_pos[i]].ret_idf());
		}
	}
}

void document::regularize_crd() {
	for (int i = 0;i < len; ++i) {
		if (term_pos[i] != -1 && coordination[i] != 0) {
			coordination[i] = log(1 + coordination[i]);
		}
	}
}

double operator ^ (const document & a, const document & b) {
	double cosarg = 0;
	for (int i = 0;i < a.len; ++i) {
		cosarg = cosarg + a.coordination[i] * b.coordination[i];
	}
	return cosarg;
}
