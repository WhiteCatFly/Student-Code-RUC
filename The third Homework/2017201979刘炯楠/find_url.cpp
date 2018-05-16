#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "normalization.h"
#include "find_url.h"

using namespace std;

const int Download_file::URL_SIGN_LENGTH;
FILE * Download_file::open_page(const string page_name) {
	char * file_name;
	file_name = normalize_file_name(page_name);
	cout<<file_name<<endl;
	FILE * file_pointer;
	file_pointer = fopen(file_name, "r");
	free(file_name);
	return file_pointer;
}


Download_file::Download_file(const string page_name) : m_page_name(page_name) {
	FILE * file_pointer;
	file_pointer = open_page(page_name);
	fseek(file_pointer, 0, SEEK_END);
	file_len = ftell(file_pointer);
	char * char_file_content = new char[file_len + 1];
	fseek(file_pointer, 0, SEEK_SET);
	
	fread(char_file_content, sizeof(char), file_len, file_pointer);
	char_file_content[file_len] = '\0';
	
	file_content = char_file_content;
	
	fclose(file_pointer);
	delete[] char_file_content;
}

int Download_file::count_url() const{
	int url_number = 0;
	int position = -1;
	while ((position = file_content.find(URL_SIGN, position + 1)) != std::string::npos) {
		url_number++;
	}
	return url_number;
}

void Download_file::get_url(std::string* & url_list, const std::string & limit_name) const {
	int position = -1;
	int url_count = 0;
	
	while ((position = file_content.find(URL_SIGN, position + 1)) != std::string::npos) {
		string original_url = "";
		position += Download_file::URL_SIGN_LENGTH; 
		for (int i = position;file_content[i] != '"' ; ++i) {
			original_url = original_url + file_content[i];
		}
		if (original_url.find(limit_name) != std::string::npos || original_url.find(absolute_sign) == std::string::npos) {
			normalize_url(url_list[url_count], original_url, m_page_name, limit_name);
			url_count++;
		}
	}
}
		
