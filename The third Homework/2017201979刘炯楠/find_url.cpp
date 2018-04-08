#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "normalization.h"
#include "find_url.h"

using namespace std;

inline static FILE* open_page(const string web_page) {
	char * file_name;
	file_name = normalize_file_name(web_page);
	FILE * file_pointer;
	file_pointer = fopen(file_name, "r");
	free(file_name);
	return file_pointer;
}

int count_url(const string now_web_page) {
	FILE * file_pointer;
	
	file_pointer = open_page(now_web_page);
	fseek(file_pointer, 0, SEEK_END);
	const int len = ftell(file_pointer);
	char *page_char_array = (char *)malloc((len + 1) * sizeof(char));
	fseek(file_pointer, 0, SEEK_SET);
	
	fread(page_char_array, sizeof(char), len, file_pointer);
	page_char_array[len] = '\0';
	string page_string = page_char_array;
	
	int url_number = 0;
	int position = -1;
	while ((position = page_string.find(URL_SIGN, position + 1)) != std::string::npos) {
		url_number++;
	}
	free(page_char_array);
	fclose(file_pointer);
	return url_number;
}

void get_url(string * & url_list, const string & now_web_page, const string & limit_name) {
	FILE * file_pointer;
	file_pointer = open_page(now_web_page);
	fseek(file_pointer, 0, SEEK_END);
	const int len = ftell(file_pointer);
	char *page_char_array = (char *)malloc((len + 1) * sizeof(char));
	fseek(file_pointer, 0, SEEK_SET);
	
	fread(page_char_array, sizeof(char), len, file_pointer); 
	page_char_array[len] = '\0';
	string page_string = page_char_array;
	
	int position = -1;
	int url_count = 0;
	
	while ((position = page_string.find(URL_SIGN, position + 1)) != std::string::npos) {
		string original_url = "";
		position += URL_SIGN_LENGTH; 
		for (int i = position;page_string[i] != '"' ; ++i) {
			original_url = original_url + page_string[i];
		}
		if (original_url.find(limit_name) != std::string::npos || original_url.find(absolute_sign) == std::string::npos) {
			normalize_url(url_list[url_count], original_url, now_web_page, limit_name);
			url_count++;
		}
	}
	
	free(page_char_array);
	fclose(file_pointer);
}
