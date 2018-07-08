#ifndef ENQUIRY_H_INCLUDED
#define ENQUIRY_H_INCLUDED

#include <map>
#include <string>

#include "result.h"
#include "structure.h"

result * enquiry_processor(std::string enquiry, data_res & resource);
static void print(const std::string & str, std::map<std::string, bool> & enquiry_exist);
void print_res(result * res,const std::string & enquiry, const data_res & resoure, const std::streambuf * default_buf, int branch_num = 5);
static void segmentor(const std::string & enquiry, std::vector<std::string> & vs);
static void make_vector(const std::string & enquiry, document & question, const std::vector<std::string> & vs, data_res & resource);
 
const std::string segmentor_path = "../ltp-3.4.0/bin/ltp_data/cws.model";
const std::string red_letter = "\033[1;31m";
const std::string blue_letter = "\033[1;34m";
const std::string regular_letter = "\033[0m";
const std::string green_letter = "\033[1;36m";

#endif
