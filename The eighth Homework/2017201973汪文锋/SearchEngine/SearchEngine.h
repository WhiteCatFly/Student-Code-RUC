#ifndef SearchEngine_2018
#define SearchEngine_2018
#include"PostingList.h"
#include"WordDictionary.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
using namespace std;
class SearchEngine
{
public:
	void ReadByDoc(const char *ReadIn);
	void ReadByFiles(const char * catalog);
	void CalcIDF();
	void FindOneWord(string Words);
	void FindMultiWord(vector<string> Words);
	void ReadAndSearch();
	void Check();
};
#endif
