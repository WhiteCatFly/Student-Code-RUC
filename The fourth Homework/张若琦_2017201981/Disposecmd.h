#ifndef Disposecmd_H_
#define Disposecmd_H_

#include <string>

using std :: string;

static const char MetaCharacter[] = {
	'$', '(', ')', '*', '+', '[', '?', '\\', '^', '{', '|'
};

const int DEFAULT = -1;

int find_equalsign(const char * src);
int find_comma(const char * src);

//inline bool is_meta_character(const char * ptr);
string Dispose_regex(const char * src);

void help_user();

#endif // Disposecmd_H_