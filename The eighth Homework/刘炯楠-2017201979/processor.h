#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>

#include "document.h"

static const std::string input = "--input";
static const std::string output = "--output";
static const std::string help = "--help";
static const std::string path = "--path";
static const std::string default_root_path = "./data/file_list.txt";

void help_out();
std::string argument_processor(int argc, char ** argv);

#endif
