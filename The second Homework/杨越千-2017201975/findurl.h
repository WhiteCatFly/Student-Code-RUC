#ifndef FINDURL_H_
#define FINDURL_H_

#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#ifndef cmd_maxlen
#define cmd_maxlen 1024
#endif

int FindUrl(const std::string &, const std::string &, const std::string &, std::string[]);
void FindDir(std::string, char*);
void ModifyUrl(std::string &);
void FindRoot(std::string, std::string &);


#endif
