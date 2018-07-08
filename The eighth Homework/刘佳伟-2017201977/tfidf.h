#ifndef TFIDF_H
#define TFIDF_H

#include "preprocess.h"
#include <cmath>

const int N = 6056;

class TfiDf
{
private:
	std::string key;
	std::string pagefile;
	double getTf();
	double getiDf();
public:
	TfiDf(const std::string &str, int pf);
	double getResultQue(const std::string &que);
	double getResult();
};

#endif
