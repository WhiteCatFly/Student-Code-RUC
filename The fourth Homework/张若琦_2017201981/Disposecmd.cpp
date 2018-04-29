#include <string>
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