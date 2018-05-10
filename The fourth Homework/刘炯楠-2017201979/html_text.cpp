#include <cstdio>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "my_regex.h"
#include "html_text.h"
#include "normalization.h"

using namespace std;

html_text::html_text() {
	content = "";
	length = 0;
}

html_text::html_text(istringstream & iStr) {
	content = "";
	string temp;
	while (getline(iStr, temp)) {
		content = content + temp;
	}
	length = content.length();
	normalize_content();
}

html_text::html_text(ifstream & iFile) {
	content =  "";
	string temp;
	while (getline(iFile, temp)) {
		content = content + temp;
	}
	length = content.length();
	normalize_content();
}

html_text::~html_text() {}

html_text & html_text::operator = (const html_text & rval) {
	if (this == &rval)
		return *this;
	content = rval.content;
	length = rval.length;
	return *this;
}

int html_text::find_url(string * & list, const string & now_web_page) const {
	return get_url(content, list, now_web_page);
}

int html_text::find_text(string * & list) const{
	return get_p(content, list);
}

int html_text::find_title(string * & list) const{
	return get_h(content, list);
}

int html_text::find_by_regex(const string & pattern, string * & list) const{
	return get_by_regex(content, pattern, list);
}

void html_text::normalize_content() {
	int start_pos = -1, end_pos = 0;
	bool commet[length];
	memset(commet, 0, sizeof(commet));
	while ((start_pos = content.find(comment_start, end_pos)) != string::npos) {
		end_pos = content.find(comment_end, start_pos) + comment_end.length();
		for (int i = start_pos;i < end_pos; ++i)
			commet[i] = true;
	}
	string temp = "";
	for (int i = 0;i < length;++i) 
		if (commet[i] == false) {
			temp = temp + content[i];
		}
	content = temp;
	length = content.length();
}

/*
void html_text::make_tree_structure(string * & list) const {
	list[0] = "";
	bool html_flag = has_html(content);
	bool head_flag = has_head(content);
	bool body_flag = has_body(content);
	string title = get_title(content);
	string * p_list = new string[maxnumber];
	string * h_list = new string[maxnumber];
	int p_count = find_text(p_list);
	int h_count = find_title(h_list);
	
	if (title != "") {
		list[0] = list[0] + "\t\t" + title_start + " " + title + " " + title_end + "\n"; 
	}
	
	if (head_flag)
		list[0] = "\t" + head_start + "\n" + list[0] + "\t" + head_end + "\n";
	
	if (body_flag)
		list[0] = list[0] + "\t" + body_start + "\n";
	
	int st1 = 0,st2 = 0;
	while (st1 < p_count && st2 < h_count) {
		int h_place = content.find(h_list[st2].substr(head_pos));
		int p_place = content.find(p_list[st1]);
		if (p_place < h_place) {
			add_text(p_list[st1], list[0]);
			st1++;
		}
		if (h_place < p_place) {
			add_title(h_list[st2], list[0]);
			st2++;
		}
	}
	if (st2 >= h_count) {
		while (st1 < p_count) {
			add_text(p_list[st1], list[0]);
			st1++;
		}
	}
	if (st1 >= p_count) {
		while (st2 < h_count) {
			add_title(h_list[st2], list[0]);
			st2++;
		}
	}

	if (body_flag)
		list[0] = list[0] + "\t" + body_end + "\n";
		
	if (html_flag)
		list[0] = html_start + "\n" + list[0] + html_end + "\n";
	delete[] p_list;
	delete[] h_list;
}
*/

void html_text::make_tree_structure(string * & list) const {
	list[0] = "";
	int tab_count = 0;
	for (int i = 0; i < length; ++i) {
		while (isspace(content[i]) == true && i < length)  {
			i++;
		}
		if (content[i] == st_sign) {
			int start = i;
			int end =  i;
			while (content[i] != en_sign) {
				i++;
			}
			end = i;
			if (content[start + 1] == slash)
				tab_count--;
			for (int k = 1; k <= tab_count; ++k)
				list[0] = list[0] + tab;
			for (int k = start; k <= end; ++k) {
				while (isspace(content[k]) == true && k <= end) 
						k++;
				if (k <= end)
				list[0] = list[0] + content[k];
			}
			list[0] = list[0] + enter;
			tab_count++;
			if (content[start + 1] == slash || content[end - 1] == slash)
				tab_count--;
			if (i < length - 1 && content[i + 1] != st_sign && isspace(content[i + 1]) == false) {
				for (int k = 1; k <= tab_count; ++k)
					list[0] = list[0] + tab;
				i = i + 1;
				while (content[i] != st_sign) {
					while (isspace(content[i]) == true &&  i < length) 
						i++;
					list[0] = list[0] + content[i];
					i++;
				}
				list[0] = list[0] + enter;
				i--;
			}
		}
	}
}
