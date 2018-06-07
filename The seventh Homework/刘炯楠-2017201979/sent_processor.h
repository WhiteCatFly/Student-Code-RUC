#ifndef SENT_PROCESSOR_H_INCLUDED
#define SENT_PROCESSOR_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

const int maxl = 500;
const double inf = 1e10;

void tag(std::string sentence, std::ostream & os);
std::string word_split(const std::vector<std::string> & ws);

#endif
