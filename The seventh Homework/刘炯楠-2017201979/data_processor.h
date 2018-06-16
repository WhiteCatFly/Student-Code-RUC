#ifndef DATA_PROCESSOR_H_INCLUDED
#define DATA_PROCESSOR_H_INCLUDED

#include <string>

std::string get_part(std::string text);
std::string get_word(std::string text);
void read_from_corpus(const char * name);
void read_from_database(const char * name);

#endif
