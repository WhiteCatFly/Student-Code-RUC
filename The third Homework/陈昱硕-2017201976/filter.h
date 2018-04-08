#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>

#include "view_source.h"

using std :: string;
using std :: vector;

class Filter{
	private : 
		static const char *forbidden_string[];
		static const char space_char[];
		
		static vector<string> key_word_;
		string error_file_;
		
		string content_;
		string site_;
		string site_prefix_;
		string site_root_;
		
		int cursor_position_;
		bool web_site_error_;
		
		bool ValidUrl(string *result);
		void DeleteRelativePath(string *web_site);
		string :: size_type GetSpaceChar(string *web_site);
		void EraseSpaceChar(string *web_site);
		void DeleteArgv(string *web_site);
		void AddPrefix(string *web_site);
		void NormalizeWebSite(string *web_site);
		bool GetNextPosition(string :: size_type &begin, string :: size_type &end);
		
	public :
		static void StaticSettings(const vector<string> &key_word){key_word_ = key_word;}
		string *GetNextUrl();
		
		Filter(const string &error_file,
			   const string &web_site,
			   Viewer *viewer,
			   int retry_count);
		
		~Filter(){}
};

#endif
