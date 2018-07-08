#ifndef QUERYPROCESS_H
#define QUERYPROCESS_H

#include "preprocess.h"
#include "segment_dll.h"

class QueryProcess
{
private:
	std::string query;
	std::vector<std::string> key;
	std::vector<int> pagefile;
public:
	QueryProcess(const std::string &str);
	std::vector<std::string> & getKey();
	std::vector<int> & getPagefile();
};

#endif
