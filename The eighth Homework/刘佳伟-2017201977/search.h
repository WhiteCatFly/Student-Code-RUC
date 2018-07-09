#ifndef SEARCH_H
#define SEARCH_H

#include "preprocess.h"
#include <sstream>

void Print(std::ifstream &fin, std::ostream &out, std::vector<std::string> &key);
void SearchKey(std::ostream &out, int pagefile, std::vector<std::string> &key);

#endif
