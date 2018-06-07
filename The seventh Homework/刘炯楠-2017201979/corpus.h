#ifndef CORPUS_H_INCLUDED
#define CORPUS_H_INCLUDED

#include <string>
#include <utility>
#include <vector>
#include <map>

const char seperate_sign = '/';
const char percent_sign = '%';
const char br_st = '[';
const char br_en = ']';
const char database[9] = "database";
const char corpus[11] = "199800.txt";
const std::string start = "st";
const std::string other = "other";
const int w_len = 3;
const int n_len = 1;
const int file_number = 6;
const int change_plc = 5;
void add_word(std::string word, std::string part);
void add_matrix(std::string part_1, std::string part_2);
void normalize();
void make_database();

#endif
