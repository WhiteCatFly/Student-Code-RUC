#include "filter.h"

#include <cstdio>
#include <cstring>

#include <iostream>

#include <string>
#include <vector>

#include "view_source.h"

using namespace std;

const char *Filter :: forbidden_string[] = {"@", "#", "(", ")", "[", "]", "{", "}",
					".txt", ".doc", ".ppt", ".xls", ".XLS", ".pdf", ".PDF", "ftp://", "file://", "telnet://",
					".jpg", ".JPG", ".jpeg", ".png", ".gif", ".bmp", ".rar", ".zip", ".7z", ".mp3", ".MP3", ".mp4", ".MP4",
					"javascript:void(0)", "javascript:;",
					".flv", ".wmv", ".avi", ".rmvb", ".mpeg", ".qt", ".mpg", ".mkv", ".rm",
					"twitter", "google", "facebook", "END"};
const char Filter :: space_char[] = "\t" "\f" "\v" "\n" "\r" " ";

vector<string> Filter :: key_word_;

Filter :: Filter(const string &error_file,
				 const string &web_site,
				 Viewer *viewer,
				 int retry_count) :
	error_file_(error_file), site_(web_site),
	cursor_position_(0), web_site_error_(false)
{
	string :: size_type begin = web_site . find("://");
	string :: size_type end = web_site . find_last_of("/", web_site . find("?"));
	if (begin == string :: npos){
		FILE *fp = fopen(error_file . c_str(), "a+");
		fprintf(fp, "%s is illegal!\n", web_site . c_str());
		fclose(fp);
		web_site_error_ = true;
		return;
	}
	
	begin += strlen("://");
	if (begin < end && end != string :: npos){
		site_prefix_ = string(web_site, 0, end + 1);
		string :: size_type root = web_site . find("/", begin);
		site_root_ = string(web_site, 0, root);
	}
	else{
		site_prefix_ = web_site + "/";
		site_root_ = web_site;
	}
	
	while (viewer -> Download(site_, content_) != 0){
		if (retry_count == 0){
			web_site_error_ = true;
			break;
		}
		retry_count --;
	}
}

bool Filter :: ValidUrl(string *result){
	if (result -> find("http") != 0)
		return false;
	
	string :: size_type begin = result -> find("://");
	if (begin == string :: npos)
		return false;
	begin += strlen("://");
	string :: size_type end = result -> find("/", begin);
	for (auto iter : key_word_){
		string :: size_type position = result -> find(iter);
		if (!(begin <= position && position < end))
			return false;
	}
	
	for (const char **ptr = forbidden_string; strcmp(*ptr, "END"); ptr ++)
		if (result -> find(*ptr) != string :: npos)
			return false;
	
	return true;
}

void Filter :: DeleteRelativePath(string *web_site){
	if (web_site -> at(web_site -> length() - 1) != '/')
		web_site -> append("/");
	
	string :: size_type head = web_site -> find("://") + strlen("://");
	string :: size_type last = head, begin = head, end = web_site -> find('/', head);
	
	string *result = new string(*web_site, 0, head);
	string section;
	
	do{
		section = web_site -> substr(begin, end - begin + 1);
		if (section == "./" || section == "/"){
			//neglect
		}
		else if (section == "../"){
			if (last != head){
				result -> erase(last);
				last = result -> find('/', result -> length() - 2) + 1;
			}
		}
		else{
			last = result -> length();
			result -> append(section);
		}
		
		begin = end + 1;
		end = web_site -> find('/', begin);
	}while (end != string :: npos);
	
	if (result -> at(result -> length() - 1) == '/')
		result -> erase(result -> length() - 1);
		
	*web_site = *result;
	delete result;
}

inline string :: size_type Filter :: GetSpaceChar(string *web_site){
	string :: size_type ptr = string :: npos;
	for (int i = 0; space_char[i]; i ++)
		ptr = min(ptr, web_site -> find(space_char[i]));
	return ptr;
}

inline void Filter :: EraseSpaceChar(string *web_site){
	string :: size_type ptr;
	while ((ptr = GetSpaceChar(web_site)) != string :: npos)
		web_site -> erase(ptr, 1);
}

void Filter :: DeleteArgv(string *web_site){
	string :: size_type begin, end, equal;
	begin = web_site -> find("?");
	if (begin == string :: npos)
		return;
	
	string *result = new string(*web_site, 0, begin);
	do{
		begin ++;
		end = web_site -> find("&", begin);
		equal = web_site -> find("=", begin);
		if (end == string :: npos)
			end = web_site -> length();
		
		string key_name = web_site -> substr(begin, equal - begin + 1);
		string the_whole_key = web_site -> substr(begin , end - begin);
		string :: size_type result_begin = result -> find(key_name);
		
		if (result_begin != string :: npos){
			string :: size_type result_end = result -> find("&", result_begin);
			if (result_end == string :: npos)
				result_end = result -> length();
			result -> replace(result_begin, result_end - result_begin, the_whole_key);
		}
		else{
			result -> append(web_site -> substr(begin - 1, 1));
			result -> append(the_whole_key);
		}
		
		begin = end;
	}while (begin != web_site -> length());
	
	*web_site = *result;
	delete result;
}

inline void Filter :: AddPrefix(string *web_site){
	if (web_site -> length() == 0)
		*web_site = site_root_;
	else if (web_site -> find("://") == string :: npos){
		if (web_site -> at(0) == '/')
			*web_site = site_root_ + *web_site;
		else if (web_site -> at(0) == '?')
			*web_site = site_ . substr(0, site_ . find("?")) + *web_site;
		else
			*web_site = site_prefix_ + *web_site;
	}
}

inline void Filter :: NormalizeWebSite(string *web_site){
	EraseSpaceChar(web_site);
	AddPrefix(web_site);
	DeleteRelativePath(web_site);
	DeleteArgv(web_site);
}

inline bool Filter :: GetNextPosition(string :: size_type &begin, string :: size_type &end){
	if (cursor_position_ >= (int)content_ . length())
		return false;
			
	begin = content_ . find("<a", cursor_position_);
	if (begin == string :: npos)
		return false;
	begin = content_ . find("href", begin);
	if (begin == string :: npos)
		return false;
	begin = min(content_ . find("'", begin), content_ . find("\"", begin));
	if (begin == string :: npos)
		return false;
	begin ++;
	
	end = min(content_ . find("'", begin), content_ . find("\"", begin));
	if (end == string :: npos)
		return false;
	
	return true;
}

string *Filter :: GetNextUrl(){
	if (web_site_error_)
		return NULL;
	string :: size_type begin, end;
	string *result = new string;
	
	do{
		if (GetNextPosition(begin, end) == false){
			delete result;
			return NULL;
		}
		*result = content_ . substr(begin, end - begin);
		NormalizeWebSite(result);
		
		cursor_position_ = end + 1;
	}while (ValidUrl(result) == false);
	return result;
}
