#ifndef HTMLParser
#define HTMLParser
#include "HTMLParser.h"
#endif

HTML::HTML(string &file_or_code){
	if (file_or_code.find("<head>") != file_or_code.npos)
		htmlcode = file_or_code;
	else {
		if (file_or_code.find(http) == 0 || file_or_code.find(https) == 0){
			origin_html = file_or_code;
			if (origin_html.back() != '/')
				origin_html += '/';
			http_feature = (origin_html.find(http) != origin_html.npos) ? http : https;
			system(("wget \"" + file_or_code + "\" 2> wget-log -O origin.html").c_str());
			file_or_code = "origin.html";
		}
		ifstream codein;
		codein.open(file_or_code.c_str());
		string tempcode;
		while (getline(codein, tempcode))
			htmlcode += tempcode + '\n';
	}
	initialize_string();
}

void HTML::initialize_string(){
	for (int i = 0; i < 100; ++i)
		if (trans_words[i][0] != end_word){
			int start = htmlcode.find(trans_words[i][0]);
			
			while (start != -1){
				htmlcode.replace(start, trans_words[i][0].length(), trans_words[i][1]);
				start = htmlcode.find(trans_words[i][0], start + 1);
			}
		}
		else break;
}

string HTML::combine_origin_new(const string &new_url) const{
	const string dot_dot = "..";
	if (new_url[0] == '/' || new_url[0] == '.'){
		if (new_url[0] == '/'){
			return origin_html.substr(0, origin_html.find('/', origin_html.find(http_feature) + http_feature.length())) + new_url;
		}
		else {
			if (new_url[1] == '/')
				return origin_html.substr(0, origin_html.find_last_of('/') + 1) + new_url.substr(2);
			else {
				int dot_dot_begin = 0, slash_end = origin_html.rfind('/');
				while (new_url.find(dot_dot, dot_dot_begin) != new_url.npos){
					dot_dot_begin = new_url.find(dot_dot, dot_dot_begin) + dot_dot.length() + 1;
					slash_end = origin_html.rfind('/', slash_end) - 1;
				}
				return origin_html.substr(0, origin_html.rfind('/', slash_end) + 1) + new_url.substr(dot_dot_begin);
			}
		}
	}
	else {
	 	return origin_html.substr(0, origin_html.find_last_of('/') + 1) + new_url;
	}
}

