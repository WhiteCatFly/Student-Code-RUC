#ifndef EXTRACT_H
#define EXTRACT_H

#include <string>
#include <unordered_map>
#include <queue>

void extract_url(std::unordered_map<std::string, bool> & ,std::queue<std::string> & , const std::string & , int cnt);

#endif

