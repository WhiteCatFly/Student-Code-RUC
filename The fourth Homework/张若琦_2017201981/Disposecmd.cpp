#include <string>
#include <iostream>
#include "Disposecmd.h"

// invalid conversion from ‘const char*’ to ‘char*’
// I've tried strcpy but didn't work

int find_equalsign(const char * src)
{
	char * ptr = const_cast<char *> (src);
	while (*ptr != 0 && *ptr != '=')
		ptr ++;
	return *ptr ? ptr - src : DEFAULT;
}

int find_comma(const char * src) // you can't find comma in a valid url
{
	char *ptr = const_cast<char *> (src);
	while (*ptr != 0 && *ptr != ',')
		ptr ++;
	return *ptr ? ptr - src : DEFAULT;
}
/*
inline bool is_meta_character(const char * ptr)
{
	for (auto ch : MetaCharacter)
		if (*ptr == ch) return true;
	return false;
}

string Dispose_regex(const char * src)
{
	string ret;
	char *ptr = const_cast<char*> (src);
	while (*ptr != 0)
	{
		if  (is_meta_character(ptr))
			ret.push_back('\\'); // not append
		ret.push_back(*ptr ++);
	}
	return ret;
}
*/

string Dispose_regex(const char * src)
{
	string ret = "<a href=\"(";
	ret = ret + (src);
	ret = ret + ")\"(.)+?>";
	return ret;
}

void help_user()
{
	std :: cerr << "htmlparser help :\n\n"
		"usage : ./parser [--title] [--text] [--picture] [--url] [--url-save] [--help] \n\n"
		"   -t 或 --title <title_filename>      \t 将文档标题保存到当前目录title_filename文件\n"
		"   -w 或 --text <text_filename>        \t 将文档文本保存到当前目录text_filename文件\n"
		"   -p 或 --picture <picture_filename>  \t 将文档图片保存到当前目录picture_filename文件\n"
		"   -u 或 --url <url_format>            \t 将文档需保存url设置为url_format格式（正则表达式\n"
		"   -s 或 --url-save <url_filename>     \t 将文档url保存到当前目录url_filename文件\n"
		"   -h 或 --help                        \t 打印帮助(本信息)并退出\n"
		<< std :: endl;
	exit(0);
}