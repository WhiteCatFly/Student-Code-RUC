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

void normalize_url(string & normal_url, const string & original_url, const string & now_web_page) {
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
	else {
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
}
