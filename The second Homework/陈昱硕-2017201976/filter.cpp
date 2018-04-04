#include "filter.h"

#include <cstdio>
#include <cstring>

#include <iostream>

#include <string>
#include <vector>

using namespace std;

extern vector<string> key_word;

extern string error_file;

static string content;
static string site;
static string site_prefix;
static string site_root;
static int cursor_position;
static bool web_site_error = false;

void SetPage(string *web_site, string *page_content){
	site = *web_site;
	string :: size_type begin = web_site -> find("://");
	string :: size_type end = web_site -> find_last_of("/", web_site -> find("?"));
	if (begin == string :: npos){
		FILE *fp = fopen(error_file . c_str(), "a+");
		fprintf(fp, "%s is illegal!\n", web_site -> c_str());
		fclose(fp);
		web_site_error = true;
		return;
	}
	else
		web_site_error = false;
	
	begin += strlen("://");
	if (begin < end && end != string :: npos){
		site_prefix = string(*web_site, 0, end + 1);
		string :: size_type root = web_site -> find("/", begin);
		site_root = string(*web_site, 0, root);
	}
	else{
		site_prefix = *web_site + "/";
		site_root = *web_site;
	}
	
	content = *page_content;
	cursor_position = 0;
}

inline static bool ValidUrl(string *result){
	if (result -> find("http") != 0)
		return false;
	
	string :: size_type begin = result -> find("://");
	if (begin == string :: npos)
		return false;
	begin += strlen("://");
	string :: size_type end = result -> find("/", begin);
	for (auto iter : key_word){
		string :: size_type position = result -> find(iter);
		if (!(begin <= position && position < end))
			return false;
	}
	
	for (const char **ptr = forbidden_string; strcmp(*ptr, "END"); ptr ++)
		if (result -> find(*ptr) != string :: npos)
			return false;
	
	return true;
}

inline static void DeleteRelativePath(string *web_site){
	if (web_site -> at(web_site -> length() - 1) != '/')
		web_site -> append("/");
	
	string :: size_type head = web_site -> find("://") + strlen("://");
	string :: size_type last = head, begin = head, end = web_site -> find('/', head);
	
	string *result = new string(*web_site, 0, head);
	string section;
	
	do{
		section = web_site -> substr(begin, end - begin + 1);
		if (section == "./" || section == "/"){
			
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

inline static string :: size_type GetSpaceChar(string *web_site){
	string :: size_type ptr = string :: npos;
	for (int i = 0; space_char[i]; i ++)
		ptr = min(ptr, web_site -> find(space_char[i]));
	return ptr;
}

inline static void EraseSpaceChar(string *web_site){
	string :: size_type ptr;
	while ((ptr = GetSpaceChar(web_site)) != string :: npos)
		web_site -> erase(ptr, 1);
}

inline static void DeleteArgv(string *web_site){
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

inline static void AddPrefix(string *web_site){
	if (web_site -> length() == 0)
		*web_site = site_root;
	else if (web_site -> find("http") == string :: npos){
		if (web_site -> at(0) == '/')
			*web_site = site_root + *web_site;
		else if (web_site -> at(0) == '?')
			*web_site = site . substr(0, site . find("?")) + *web_site;
		else
			*web_site = site_prefix + *web_site;
	}
}

inline static void NormalizeWebSite(string *web_site){
	EraseSpaceChar(web_site);
	AddPrefix(web_site);
	DeleteRelativePath(web_site);
	DeleteArgv(web_site);
}

inline static bool GetNextPosition(string :: size_type &begin, string :: size_type &end){
	if (cursor_position >= (int)content . length())
		return false;
			
	begin = content . find("<a", cursor_position);
	if (begin == string :: npos)
		return false;
	begin = content . find("href", begin);
	if (begin == string :: npos)
		return false;
	begin = min(content . find("'", begin), content . find("\"", begin));
	if (begin == string :: npos)
		return false;
	begin ++;
	
	end = min(content . find("'", begin), content . find("\"", begin));
	if (end == string :: npos)
		return false;
	
	return true;
}

string *GetNextUrl(){
	if (web_site_error)
		return NULL;
	string :: size_type begin, end;
	string *result = new string;
	
	do{
		if (GetNextPosition(begin, end) == false){
			delete result;
			return NULL;
		}
		//cerr << begin << " " << end << " " << cursor_position << " " << content . length() << endl;
		*result = content . substr(begin, end - begin);		
		NormalizeWebSite(result);
		
		cursor_position = end + 1;
	}while (ValidUrl(result) == false);
	return result;
}
