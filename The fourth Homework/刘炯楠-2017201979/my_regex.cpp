#include <cstdio>
#include <string>
#include <regex>
#include "my_regex.h"
#include "normalization.h"

using namespace std;

int get_h(const string & content, string * & list) {
	int count = 0;
	regex r_pattern(h_pattern);
	for (sregex_iterator it(content.begin(), content.end(), r_pattern), end_it; it != end_it; it++) {
		list[count] = "";
        string temp = it->str();
        smatch result;
        
        regex r_st(h_st_pattern);
        regex_search(temp,result,r_st);
        int start_pos = temp.find(result.str()) + result.str().length();
        
        regex r_en(h_en_pattern);
        regex_search(temp,result,r_en);
        int end_pos = temp.find(result.str());
        
        for (int i = 0; i < start_pos - 1; ++i)
        	if (temp[i] == head_sign && (temp[i + 1] >= head_range_low && temp[i + 1] <= head_range_high)) {
        		list[count] = list[count] + temp[i] + temp[i + 1] + " ";
        		break;
        	}
        for (int i = start_pos; i < end_pos; ++i)
        	list[count] = list[count] + temp[i];
        count++;
    }
    return count;
}

int get_p(const string & content, string * & list) {
	int count = 0;
	regex r_pattern(p_pattern);
	for (sregex_iterator it(content.begin(), content.end(), r_pattern), end_it; it != end_it; it++) {
		list[count] = "";
        string temp = it->str();
        smatch result;
        
        regex r_st(p_st_pattern);
        regex_search(temp,result,r_st);
        int start_pos = temp.find(result.str()) + result.str().length();
        
        regex r_en(p_en_pattern);
        regex_search(temp,result,r_en);
        int end_pos = temp.find(result.str());
        
        for (int i = start_pos; i < end_pos; ++i)
        	list[count] = list[count] + temp[i];
        count++;
    }
    return count;
}

int get_url(const string & content, string * & list, const string & now_web_page) {
	int count = 0;
	regex r_pattern(url_pattern);
	for (sregex_iterator it(content.begin(), content.end(), r_pattern), end_it; it != end_it; it++) {
		list[count] = "";
        string temp = it->str();
        
        regex r_st(url_st_pattern);
        smatch result;
        regex_search(temp,result,r_st);
        int start_pos = temp.find(result.str()) + result.str().length();
        char sign = temp[start_pos - 1];
        string origin = "";
        
        for (int i = start_pos; temp[i] != sign; ++i)
        	origin = origin + temp[i];
        normalize_url(list[count], origin, now_web_page);
        count++;
    }
    return count;
}

int get_by_regex(const string & content, const string & pattern, string * & list) {
	int count = 0;
	regex r_pattern(pattern);
	for (sregex_iterator it(content.begin(), content.end(), r_pattern), end_it; it != end_it; it++) {
		list[count++] = it -> str();
    }
    return count;
}

std::string get_title(const string & content) {
	regex r_pattern(title_pattern);
	smatch result;
	regex_search(content, result, r_pattern);
	if (result.str() == "")
		return "" ;
	else {
		string temp = result.str();
		int start_pos = temp.find(title_start) + title_start.length();
		int end_pos = temp.find(title_end);
		string ret = "";
		for (int i = start_pos; i < end_pos; ++i)
			ret = ret + temp[i];
		return ret;
	}
}

bool has_html(const string & content) {
	return (content.find(html_end) != string::npos);
}

bool has_head(const string & content) {
	return (content.find(head_end) != string::npos);
}

bool has_body(const string & content) {
	return (content.find(body_end) != string::npos);
}
