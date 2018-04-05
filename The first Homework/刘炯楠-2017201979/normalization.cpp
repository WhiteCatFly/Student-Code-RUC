#include <cstring>
#include <cstdlib>
#include <string>
#include "normalization.h"

using namespace std;

inline static int find_pos(const string & web_page) {
	int length = web_page.length();
	int position;
	for (int i = length - 1; i >= 0; --i) {
		if (web_page[i] == '/')
			{position = i; break;}
	}
	return position;
}

char * normalize_file_name(const string & web_page) {
	char * file_name = (char *) malloc (4 * MAXLEN * sizeof(char));
	int position = find_pos(web_page);
	int len = 0;
	int length = web_page.length();
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
	char * directory = (char *) 	malloc (4 * MAXLEN * sizeof(char));
	const int position = find_pos(web_page);
	int len = 0;
	for (int i = 0; i < position; ++i) directory[len++] = web_page[i];
	directory[len] = '\0';
	return directory;
}

void normalize_url(string & normal_url, const string & original_url, const string & now_web_page) {
	if (original_url.find(now_web_page) == -1) {
		if (original_url.find("http") == -1) {
			int length = now_web_page.length();
			int last_pos = 0;
			for (int i = 0;i < length;++i)
				if (now_web_page[i] == '/')
					last_pos =  i;
			for (int i = 0;i < last_pos;++i)
				normal_url = normal_url + now_web_page[i];
			normal_url = normal_url + '/' + original_url;
		}
	}
	else {
		if (original_url.find("http") != -1) {
			int pos = original_url.find(TOP_NAME);
			int Len = original_url.length();
			for (int i = pos; i < Len;++i)
				normal_url += original_url[i];
		}
		else
			normal_url = original_url;	
	}
}
