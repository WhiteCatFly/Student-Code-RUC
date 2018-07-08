#include "tfidf.h"

using namespace std;

double TfiDf::getTf()
{
	int timesA = 0, timesB = 0, total = 0;
	string str;
	ifstream fin(pagefile + ".title");
	
	while(fin >> str)
	{
		total++;
		if(str == key)
			timesA++;
	}
	fin.close();
	
	fin = ifstream(pagefile + ".body");
	
	while(fin >> str)
	{
		total++;
		if(str == key)
			timesB++;
	}
	fin.close();
	
	return 10 * log((timesA * 1.4 + timesB * 1.1  == 0) ? 1 : timesA * 1.4 + timesB * 1.1) / log(total);
}

double TfiDf::getResultQue(const string &que)
{
	int last = 0, times = 0;
	while((last = que.find(que, last)) != string::npos)
	{
		times++;
		last += key.size();
	}
		
	return log((times == 0) ? 1 : times * 1.4) * getiDf();
}

double TfiDf::getiDf()
{
	return (log(N) - log(Keys::keys[key].size())) * 10;
}

TfiDf::TfiDf(const string &str, int pf)
{
	key = str;
	pagefile = Keys::filename[pf];
}

double TfiDf::getResult()
{
//	cerr << getTf() << ' ' << getiDf() << endl;
	return getTf() * getiDf();
}
