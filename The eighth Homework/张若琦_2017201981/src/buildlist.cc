#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "buildlist.h"

using std::ifstream;
using std::string;

std::map<string, int> dictionary; // id of vec of words
std::vector<short> vec[MAXW]; // DocID list
std::vector<double> tf[MAXW];

void DisposeDocumentPart(string filename, int DocID, int & totalwords, int & words,
                         std::map<string, int> * pdict, int ratio)
{
	string word;

	ifstream infile(filename);

	while (infile >> word)
	{
		words ++;

		if (!dictionary[word] && !(*pdict)[word]) // new
		{
			(*pdict)[word] = ratio;
			dictionary[word] = ++ totalwords;
			vec[totalwords].push_back(DocID);
		}
		else if (!(*pdict)[word]) // new to the passage
		{
			(*pdict)[word] = ratio;
			vec[dictionary[word]].push_back(DocID);
		}
		else
		{
			(*pdict)[word] += ratio;
		}
	}

	infile.close();
}

void DisposeDocument(string filename, int DocID, int & totalwords)
{
	std::map<string, int> dict; // number of each word
	
	int words = 0; // number of word

	DisposeDocumentPart(filename + ".title", DocID, totalwords, words, &dict, 10);
	DisposeDocumentPart(filename + ".body", DocID, totalwords, words, &dict, 1);

	std::map<string, int>::iterator iter;
	for (iter = dict.begin(); iter != dict.end(); iter ++)
	{
		tf[dictionary[iter -> first]].push_back(/*1. + log10(*/(double)iter -> second / words/*)*/);
	}

	dict.clear();
}

void buildlist()
{
	int cnt = 0, totalwords = 0;

	ifstream listfile("./data/file_list.txt");
	string path;

	while (getline(listfile, path))
	{
		path.erase(0, 1);
		path = "./data" + path;

		DisposeDocument(path, cnt ++, totalwords);
	}

	MakeListFile(cnt);
	/*std::ofstream outfile("./list/dictionary");

	char str[30] = {0};
	std::map<string, int>::iterator iter;
	
	for (iter = dictionary.begin(); iter != dictionary.end(); iter ++)
	{
		int id = iter -> second;
		int n = vec[id].size(), sz = (iter -> first).size();
		memcpy(str, (iter -> first).c_str(), sz);

		outfile.write(str, sz + 1); // str + '\0'
		outfile.write((char*)&n, sizeof(int));

		double idf = log10((double)cnt / n);
		
		for (int i = 0;i < n;i ++)
		{
			short tmp1 = vec[id][i];
			double tmp2 = tf[id][i] * idf;
			outfile.write((char*)&tmp1, sizeof(short));
			outfile.write((char*)&tmp2, sizeof(double));
		}

		vec[id].clear();
		tf[id].clear();
	}*/

	listfile.close();
//	outfile.close();
}

char num[MAXL];

void MakeListFile(int N)
{
	std::ofstream list("./list/list");
	std::ofstream dict("./list/dictionary");
//	std::ofstream out("./list/dict");

	int tot = 0;
	std::map<string, int>::iterator iter;
	
	for (iter = dictionary.begin(); iter != dictionary.end(); iter ++)
	{
		int id = iter -> second;
		short n = vec[id].size();
		//memcpy(num + tot, (iter -> first).c_str(), sz);
		//tot += sz + 1; // str + '\0'
		dict << iter -> first << std::endl;

		memcpy(num + tot, (char*)&n, sizeof(short));
		tot += sizeof(short);
//		out << iter -> first << ' ' << n << ' ';

		double idf = log10((double)N / n);
		
		for (int i = 0; i < n; i ++)
		{
			short tmp1 = vec[id][i];
			memcpy(num + tot, (char*)&tmp1, sizeof(short));
			tot += sizeof(short);
//			out << tmp1 << ' ' << tmp2 << ' ';
		}
		for (int i = 0; i < n; i ++)
		{
			double tmp2 = tf[id][i] * idf;
			memcpy(num + tot, (char*)&tmp2, sizeof(double));
			tot += sizeof(double);
		}

		// out << '\n';

		vec[id].clear();
		tf[id].clear();
	}

	list.write(num, tot);
//	out.close();
	list.close();
	dict.close();
}