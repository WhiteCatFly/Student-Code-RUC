#include"PostingList.h"
#include"WordDictionary.h"
#include"SearchEngine.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstring>
#include<dirent.h>
using namespace std;
int main()
{
	SearchEngine A;
	A.ReadByFiles("/home/dia/download");
	A.CalcIDF();
	A.ReadAndSearch();
	return 0;
}

