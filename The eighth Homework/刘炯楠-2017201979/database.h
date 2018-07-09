#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <string>

#include "structure.h"

bool database_exist();
data_res initialize_from_database();
void output_to_database(const data_res & resource);

static const std::string pred_data = "./data";
static const std::string database = "database";
static const std::string document_sign = "DOCUMENT";
static const std::string term_sign = "TERM";

#endif
