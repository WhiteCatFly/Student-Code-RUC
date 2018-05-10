#ifndef HTMLParser
#define HTMLParser
#include "HTMLParser.h"
#endif

void HTML::get_url() const{
	const string href = "href=";
	int url_begin = htmlcode.find(href), total = 0;
	
	ofstream url;
	url.open("url");
	
	while (url_begin != -1){
		int url_end = htmlcode.find(htmlcode[url_begin + href.length()] == '\"' ? '\"' : '\'', url_begin + href.length() + 1);
		const string new_url = htmlcode.substr(url_begin + href.length() + 1, url_end - url_begin - href.length() -1);
		url_begin = htmlcode.find(href, url_end);
		
		int flag = 0;
		for (int i = 0; sensitive_words[i] != end_word; ++i){
			if (new_url.find(sensitive_words[i]) != new_url.npos){
				flag = 1;
				break;
			}
		}
		if (flag)
			continue;
		++total;
		if (new_url.find(http) != new_url.npos || new_url.find(https) != new_url.npos)
			url << new_url << endl;
		else {
			url << combine_origin_new(new_url) << endl;
		}
	}
	if (total)
		cout << "There are " << total << " urls in the website, which are all got in the file \"url\"." << endl;
	else cout << "There are no url in the website." << endl;
}

void HTML::get_title() const{
	const string title_begin = "<title>", title_end = "</title>";
	int begin = htmlcode.find(title_begin), end = htmlcode.find(title_end);
	cout << "The title of the website is:" << endl;
	cout << htmlcode.substr(begin + title_begin.length(), end - begin - title_begin.length()) << endl;
}

void HTML::get_img() const{
	const string src = "src=", img = "img";
	int src_begin = htmlcode.find(src), total = 0;
	system("mkdir Picture 2> wget-log ");
	
	cout << "Please wait for a little time." << endl << endl;
	while (src_begin != -1){
		int src_end = htmlcode.find(htmlcode[src_begin + src.length()] == '\"' ? '\"' : '\'', src_begin + src.length() + 1);
		const string new_url = htmlcode.substr(src_begin + src.length() + 1, src_end - src_begin - src.length() -1);
		
		if (htmlcode.find(img, htmlcode.rfind('<', src_begin)) < src_begin){
			++total;
			const string whole_string = combine_origin_new(new_url);
			system(("wget \"" + whole_string + "\" 2> wget-log -O Picture/" + whole_string.substr(whole_string.rfind('/') + 1)).c_str());
		}
		src_begin = htmlcode.find(src, src_end);
	}
	
	if (total)
		cout << "There are " << total << " pictures in the website, which are all downloaded in the file \"Picture\"." << endl;
	else cout << "There are no picture in the website." << endl;
}

void HTML::get_main_text() const{
	string p1 = "<p", p2 = "</p>";
	int text_begin = htmlcode.find(p1);
	
	cout << "The main text of this page is: " << endl;
	while (text_begin != -1){
		int text_end = htmlcode.find(p2, text_begin);
		
		int total_label = 0, total_slash = 0;
		string text = "";
		for (int i = text_begin; i < text_end; ++i){
			if (htmlcode[i] == '<'){
				++total_label;
				if (htmlcode[i + 1] == '/')
					--total_slash;
				else ++total_slash;
			}
			if (htmlcode[i] == '>')
				--total_label;
			if (total_label == 0 && total_slash == 1 && htmlcode[i] != '>')
				text += htmlcode[i];
		}
		
		int flag = 0;
		for (int i = 0; i < text.length(); ++i)
			if (!isspace(text[i])){
				flag = 1;
				break;
			}
		if (flag == 1){
			while (isspace(text[text.length() - 1]))
				text.erase(text.length() - 1);
			cout << text <<endl;
		}
		text_begin = htmlcode.find(p1, text_end);
	}
}

void HTML::get_certain_pattern(const string &type) const{
	system(("mkdir " + type + " 2> wget-log").c_str());
	const string ftype = '.' + type;
	int type_begin = htmlcode.find(ftype), total = 0;
	
	cout << "Please wait for a little time." << endl << endl;
	while (type_begin != -1){
		char quotation = htmlcode.find('\'', type_begin) < htmlcode.find('\"', type_begin) ? '\'' : '\"';
		int new_begin = htmlcode.rfind(quotation, type_begin), new_end = htmlcode.find(quotation, type_begin);
		
		const string whole_string = combine_origin_new(htmlcode.substr(new_begin + 1, new_end - new_begin -1));
		system(("wget \"" + whole_string + "\" 2> wget-log -O " + type + "/" + whole_string.substr(whole_string.rfind('/') + 1)).c_str());
		
		++total;
		type_begin = htmlcode.find(ftype, type_begin + 1);
	}
	if (total)
		cout << "There are " << total << " " + type + "s in the website, which are all downloaded in the file \"" + type + "\"." << endl;
	else cout << "There are no " << type << " in the website." << endl;
}

void HTML::get_tree_structure() const{
	string code;
	for (int i = 0, flag = 0; i < htmlcode.length(); ++i){
		if (htmlcode[i] == '<')
			flag = 1;
		if (flag)
			code += htmlcode[i];
		if (htmlcode[i] == '>')
			flag = 0;
	}
	
	ofstream tree;
	tree.open("tree_structure");
	int bracket_begin = code.find('<'), indent_total = 0, flag = 0;
	while (bracket_begin != -1){
		int next_begin = code.find('<', bracket_begin + 1);
		if (next_begin == -1)
			break;
		if (code[bracket_begin + 1] == '!'){
			if (flag)
				tree << endl;
			for (int i = 1; i <= indent_total; ++i)
				tree << "\t";
			tree << code.substr(bracket_begin, next_begin - bracket_begin) << endl;
			flag = 0;
		}
		else{
			if (code[bracket_begin + 1] == '/'){
				--indent_total;
				for (int i = 1; i <= indent_total; ++i)
					tree << "\t";
				tree << code.substr(bracket_begin, next_begin - bracket_begin) << endl;
				flag = 1;
			}
			else {
				if (flag)
					tree << endl;
				for (int i = 1; i <= indent_total; ++i)
					tree << "\t";
				++indent_total;
				tree << code.substr(bracket_begin, next_begin - bracket_begin) << endl;
				flag = 0;
				if (code[next_begin - 2] == '/')
					--indent_total;
			}
		}
		bracket_begin = next_begin;
	}
	cout << "Tree structure has been rearranged in \"tree_structure\"." << endl;
}

