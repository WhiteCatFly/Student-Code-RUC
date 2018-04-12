#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include "normalization.h"
 
using namespace std;

inline static int find_pos(const string & page_name) {
	int length = page_name.length();
	int seperate_position;
	for (int i = length - 1; i >= 0; --i) {
		if (page_name[i] == seperate_sign)
			{seperate_position = i; break;}
	}
	return seperate_position;
}

char * normalize_file_name(const string & page_name) {
	char * file_name = (char *) malloc ((MAXLEN + EXTRA_LEN)* sizeof(char));
	int seperate_position = find_pos(page_name);
	int file_name_length = 0;
	int page_name_length = page_name.length();
	
	strcpy(file_name, name_head.c_str());
	file_name_length = name_head.length();
	file_name[file_name_length] = end_sign;
	
	for (int i = 0; i < page_name_length; ++i) file_name[file_name_length++] = page_name[i];
	file_name[file_name_length] = end_sign;
	
	if (seperate_position == page_name_length - 1 || ((page_name.find(".", seperate_position + 1) + 4 != page_name_length) && (page_name.find(".", seperate_position + 1) + 5 != page_name_length))) {
		strcat(file_name,name_tail.c_str());
		file_name_length = file_name_length + name_tail.length();
	}
	file_name[file_name_length] = end_sign;
	
	return file_name;
}

char * normalize_directory(const string & page_name) {
	char * directory = (char *) malloc ((MAXLEN + EXTRA_LEN) * sizeof(char));
	const int seperate_position = find_pos(page_name);
	int directory_length = 0;
	
	strcpy(directory, name_head.c_str());
	directory_length = name_head.length();
	directory[directory_length] = end_sign;
	
	for (int i = 0; i < seperate_position; ++i) directory[directory_length++] = page_name[i];
	directory[directory_length] = end_sign;
	
	return directory;
}

void normalize_url(string & normal_url, const string & original_url, const string & now_page_name, const string & limit_name) {
	if (original_url.find(limit_name) == std::string::npos) {
		if (original_url.find(absolute_sign) == std::string::npos) {
			int length = now_page_name.length();
			if (original_url[0] != seperate_sign) {
				int last_seperate_pos = 0;
				for (int i = 0;i < length;++i)
					if (now_page_name[i] == seperate_sign)
						last_seperate_pos =  i;
				for (int i = 0;i < last_seperate_pos;++i)
					normal_url = normal_url + now_page_name[i];
				normal_url = normal_url + seperate_sign + original_url;
			}
			else {
				for (int i = 0;i < length; ++i) {
					if (now_page_name[i] == seperate_sign) break;
					normal_url += now_page_name[i];
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
			int length = original_url.length();
			for (int i = pos; i < length;++i)
				normal_url += original_url[i];
			if (original_url.find(seperate_sign,pos) == std::string::npos)
				normal_url = normal_url + seperate_sign;
		}
		else
			normal_url = original_url;	
	}
}
