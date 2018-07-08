#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "LoadDict.h"

using std::string;

void GetDictionary(string * pdictionary, std::vector<pii> * plist, int & totalwords)
{
	std::ifstream dict("./list/dictionary");

	while (getline(dict, *(pdictionary + totalwords)))
		totalwords ++;
	
//	std::cout<<totalwords<<std::endl;

	dict.close();

	/* ********************** */

	std::ifstream list("./list/list", std::ios::in | std::ios::binary);

	short n;
	short id[MAXD];
	double tf_idf[MAXD];

	for (int i = 0;i < totalwords; i ++)
	{
	
		list.read((char*)&n, sizeof(short));
		list.read((char*)&id, sizeof(short) * n);
		list.read((char*)&tf_idf, sizeof(double) * n);

		for (int j = 0; j < n; j ++)
		{
			(plist + i) -> push_back(pii(id[j], tf_idf[j]));
		}
	}

	list.close();
}

void GetUrlList(string * purl, int & totalfiles)
{
	std::ifstream listfile("./data/file_list.txt");
	while (getline(listfile, *(purl + totalfiles)))
	{
		(purl + totalfiles) -> erase(0, 1);

		totalfiles ++;
	}

	listfile.close();
}