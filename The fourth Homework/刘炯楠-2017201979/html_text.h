#ifndef HTML_TEXT_INCLUDED
#define HTML_TEXT_INCLUDED

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "my_regex.h"
#include "normalization.h"

const int maxnumber = 50000;
static int head_pos = 3;
static const std::string comment_start("<!--");
static const std::string comment_end("-->");
static const std::string tab("\t");
static const std::string enter("\n");
static const char slash = '/';
static const char st_sign = '<';
static const char en_sign = '>';
class html_text{
private:
	std::string content;
	std::string page_name;
	int length;
	void normalize_content();
public:
	html_text();
	html_text(std::istringstream & iStr, std::string & name);
	html_text(std::ifstream & iFile, std::string & name);
	~html_text();
	
	html_text & operator = (const html_text & rval);
	
	int find_url(std::string * & list) const;
	int find_text(std::string * & list) const;
	int find_title(std::string * & list) const;
	int find_by_regex(const std::string & pattern, std::string * & list) const;
	
	void make_tree_structure(std::string * & list) const;
};

#endif
