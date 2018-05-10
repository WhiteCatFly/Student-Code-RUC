#ifndef Parser_H_
#define Parser_H_

#include <regex>
#include <iostream>
#include <string>
#include <sstream>

using std :: string;
using std :: cout;
using std :: endl;
using std :: regex;
using std :: sregex_iterator;
using std :: stringstream;

class Parser
{
private :
	string htmlfile_;
	string url_;

	void write_file();
public :
	Parser() {};
	Parser(const char * filename);
	Parser(const string & url);
	~Parser() {};

	string get_file(const char * filename) const;

	string itos(const int n) const;
	void parse_picture(const string & file_name) const;
	bool is_white_character(const char ch) const;
	void del_white_character(string & file)  const;
	void parse_text(const string & file_name) const;
	void parse_title(const string & file_name) const;
	void parse_url(const string & file_name,const string & pattern_str) const;

	void write_file(const stringstream & istr,const string & file_name) const;
	void output_picture(const string & url,const string & file_name) const;
	void write_file(const string & output,const string & file_name) const;
};

#endif // Parser_H_