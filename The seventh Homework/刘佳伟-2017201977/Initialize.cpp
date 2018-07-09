#include "CWSPOS.h"

using namespace std;

void CWSPOS::InputType(const char *s0)
{
	cout << "读取type。。。" << endl;
	ifstream fin0(s0);
	fin0 >> type_n;
	for(int i = 1; i <= type_n; i++)
		fin0 >> type[i];
	fin0.close();
	cout << "完成。" << endl;
}

void CWSPOS::InputDictionary(const char *s0)
{
	string str1, str2;
	int num;
	
	cout << "读取dictionary。。。" << endl;
	ifstream fin(s0);
	fin >> alltimes;
	fin >> words_n;
	for(int i = 1; i <= words_n; i++)
	{
		fin >> str1 >> num;
		dictionary[str1].times = num;
		for(int i = 1; i <= type_n; i++)
			fin >> str2 >> dictionary[str1].type_times[i];
	}
	fin.close();
	cout << "完成。" << endl;
}

void CWSPOS::InputTypeMatrix(const char *s0)
{
	cout << "读取TypeMatrix。。。" << endl;
	ifstream fin2(s0);
	for(int i = 1; i <= type_n; i++)
	{
		fin2 >> type_alltimes[i];
		type_alltimes[0] += type_alltimes[i];
	}
		
	for(int i = 1; i <= type_n; i++)
		for(int j = 1; j <= type_n; j++)
			fin2 >> type_mat[i][j];
	fin2.close();
	cout << "完成。" << endl;
}

CWSPOS::CWSPOS(string &s0)
{
	memset(vis, false, sizeof(vis));
	memset(vis2, false, sizeof(vis2));	
	memset(type_alltimes, 0, sizeof(type_alltimes));
	sentence = s0;
	
	InputType("type");
	InputDictionary("dictionary");
	InputTypeMatrix("TypeMatrix");
	
	
}

