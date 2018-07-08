#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <fstream>

class Keys
{
public:
	static std::vector<std::string> filename;
	static std::unordered_map<std::string, std::vector<int> > keys;
	static std::unordered_map<std::string, int> forbidden;
};

void initialize();
void find_all_keys();

#endif
