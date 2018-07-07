#ifndef RESOUCE_H_INCLUDED
#define RESOUCE_H_INCLUDED

#include <string>
#include "term.h"
#include "document.h"
#include "structure.h"

data_res resource_initialize(const std::string & root_directory);
static void docu_preprocessor(const std::string & file_name, data_res & resource);
static const double t_weight = 0.6;
static const double b_weight = 0.4;

#endif
