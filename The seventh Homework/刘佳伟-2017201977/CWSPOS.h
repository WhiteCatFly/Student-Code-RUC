#ifndef CWSPOS_H
#define CWSPOS_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>

struct Info
{
	int times;
	int type_times[60];
};

class CWSPOS
{
private:
	std::unordered_map<std::string, Info> dictionary;
	std::vector<std::string> CWS, POS;
	std::string type[60], sentence;
	int type_mat[60][60], type_alltimes[60], type_n, words_n;
	double f[2010], f2[2010][60];
	int choice[2010], choice2[2010][60];
	bool vis[2010], vis2[2010][60];
	int alltimes;
	
	int GetTypeTimes(std::string &word, int i);
	void InputType(const char *s0);
	void InputDictionary(const char *s0);
	void InputTypeMatrix(const char *s0);
	void dp_CWS(int i);
	void dp_POS(int i, int j);
public:
	CWSPOS() = default;
	CWSPOS(std::string &s0);
	std::vector<std::string> GetCWS();
	std::vector<std::string> GetPOS();
};

#endif
