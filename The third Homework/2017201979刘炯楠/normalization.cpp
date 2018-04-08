#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include "normalization.h"

using namespace std;

inline static int find_pos(const string & web_page) {
	int length = web_page.length();
	int position;
	for (int i = length - 1; i >= 0; --i) {
		if (web_page[i] == seperate_sign)
			{position = i; break;}
	}
	return position;
}

char * normalize_file_name(const string & web_page) {
	char * file_name = (char *) malloc ((MAXLEN + EXTRA_LEN)* sizeof(char));
	int position = find_pos(web_page);
	int len = 0;
	int length = web_page.length();
	file_name[len++] = 'w';
	file_name[len++] = 'e';
	file_name[len++] = 'b';
	file_name[len++] = 'p';
	file_name[len++] = 'a';
	file_name[len++] = 'g';
	file_name[len++] = 'e';
	file_name[len++] = '/'; 
	for (int i = 0; i < length; ++i) file_name[len++] = web_page[i];
	if (position == length - 1 || ((web_page.find(".", position + 1) + 4 != length) && (web_page.find(".", position + 1) + 5 != length))) {
		file_name[len++] = '.';
		file_name[len++] = 'h';
		file_name[len++] = 't';
		file_name[len++] = 'm';
		file_name[len++] = 'l';
	}
	file_name[len] = '\0';
	return file_name;
}

char * normalize_directory(const string & web_page) {
	char * directory = (char *) malloc ((MAXLEN + EXTRA_LEN) * sizeof(char));
	const int position = find_pos(web_page);
	int len = 0;
	directory[len++] = 'w';
	directory[len++] = 'e';
	directory[len++] = 'b';
	directory[len++] = 'p';
	directory[len++] = 'a';
	directory[len++] = 'g';
	directory[len++] = 'e';
	directory[len++] = '/';
	for (int i = 0; i < position; ++i) directory[len++] = web_page[i];
	directory[len] = '\0';
	return directory;
}

void normalize_url(string & normal_url, const string & original_url, const string & now_web_page, const string & limit_name) {
	if (original_url.find(limit_name) == std::string::npos) {
		if (original_url.find(absolute_sign) == std::string::npos) {
			int length = now_web_page.length();
			if (original_url[0] != seperate_sign) {
				int last_pos = 0;
				for (int i = 0;i < length;++i)
					if (now_web_page[i] == seperate_sign)
						last_pos =  i;
				for (int i = 0;i < last_pos;++i)
					normal_url = normal_url + now_web_page[i];
				normal_url = normal_url + seperate_sign + original_url;
			}
			else {
				for (int i = 0;i < length; ++i) {
					if (now_web_page[i] == seperate_sign) break;
					normal_url += now_web_page[i];
				}
				normal_url += original_url;
			}
		}
	}
	else {
		if (original_url.find(absolute_sign) != std::string::npos) {
			int pos_1 = original_url.find(absolute_sign1);
			int pos_2 = original_url.find(absolute_sign2);
			int pos = 0;
			if (pos_1 != (int)std::string::npos) pos = pos_1 + absolute_sign1.length();
			if (pos_2 != (int)std::string::npos) pos = pos_2 + absolute_sign2.length();
			int Len = original_url.length();
			for (int i = pos; i < Len;++i)
				normal_url += original_url[i];
			if (original_url.find(seperate_sign,pos) == std::string::npos)
				normal_url = normal_url + seperate_sign;
		}
		else
			normal_url = original_url;	
	}
}
