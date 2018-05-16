#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using std::string;
using std::stringstream;

class Parser{
	private:
		string html;
		string url_;
		
	public:
		Parser() {};
		Parser(const char* name);
		Parser(const string& url);
		~Parser(){};
		void get_html(const char* filename);
		void display(const stringstream& content, const string& name ) const;
		void get_title()const;
		void get_text() const;
		void get_url() const;
		void get_tag(const string& tag) const;
};
#endif 
