#ifndef FIND_URL_H
#define FIND_URL_H

#include <iostream>
#include <string>

class Download_file{
	private :
		const static int URL_SIGN_LENGTH = 8;
		std::string m_page_name;
		int file_len;
		std::string file_content;
		FILE * open_page(const std::string page_name);
	public :
		Download_file(const std::string page_name);	
		~Download_file() {}
		
		int count_url() const;
		void get_url(std::string* & url_list, const std::string & limit_name) const;
};

const std::string URL_SIGN = "a href=\"";
#endif
