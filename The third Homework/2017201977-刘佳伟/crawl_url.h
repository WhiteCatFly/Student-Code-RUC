#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <unistd.h>

//The Keyword List, Copyright CYS 2018

extern const char *forbidden_str[];
extern const char END_OFS[];
extern const char ILLEGALURL[];
extern const char HTMLEND[];
extern const char HREF[];
extern const int http_Len;
extern const int https_Len;
extern const int href_Len;

class URL
{
	private:
		std::string path;
	public:
		URL() {}
		URL(const std::string &url);
		URL(const std::string &FatherUrl, std::string url);
		std::string UrlToDirectory();
		std::string UrlToFile();
		std::string GetUrl();
};

