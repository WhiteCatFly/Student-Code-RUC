#ifndef InputDealHzy_CPP_
#define InputDealHzy_CPP_
#include "global_settings.cpp"
#include "InputDeal.h"
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

int CheckInput(std::string s) {
	for(int i = 0; i < Para_Num; ++i)
		if(s == Para[i]) return i;
	return -1;
}

void InputWords(std::string s, std::vector<std::string> & result) {
	using namespace std;
	fstream p(InputFile, ios::out);
	p << s;
	p.close();
	system(THUlac);
	p.open(OutputFile, ios::in);
	string tmp;
	while(p >> tmp) result.push_back(tmp);
	p.close();
	
	
	/*FILE * p = fopen(InputFile, "w");
	fputs(s.c_str(), p);
	fclose(p);
	system(THUlac);
	p = fopen(OutputFile, "r");
	int num = 0;
	while(!feof(p)) {
		char tmp[Len];
		fscanf(p, "%s", tmp);
		result[num++] = tmp;
	}
	fclose(p);
	return num;*/
}

#endif
	
