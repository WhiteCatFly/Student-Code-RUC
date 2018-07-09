#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

struct Info
{
	int type[60];
	int times;
};
unordered_map<string, Info> words;
int f[2010][2010];
string type[60];
int type_mat[60][60];
int type_n;
int alltimes;

int get_type(string s)
{
	for(int i = 1; i <= type_n; i++)
		if(s == type[i])
			return i;
	return -1;
}

int main()
{
	ifstream fin0("type");
	fin0 >> type_n;
	for(int i = 1; i <= type_n; i++)
		fin0 >> type[i];
	fin0.close();
	
	string path_root = "language_data/", path, word;
	int last_type = -1;
	for(int i = 199801; i <= 199806; i++)
	{
		cout << i << "..." << endl;
		path = path_root + to_string(i) + ".txt";
		ifstream fin(path.c_str());
		while(fin >> word)
		{
			if(word.find('-') != string::npos)
			{
				last_type = -1;
				continue;
			}
			int start = (word.find('[') == string::npos ? 0 : word.find('[') + 1);
			int end1 = word.find('/');
			int end2 = (word.find(']') == string::npos ? word.size() : word.find(']'));
			words[word.substr(start, end1 - start)].times++;
			int word_type = get_type(word.substr(end1, end2 - end1));
			
			words[word.substr(start, end1 - start)].type[word_type]++;
			
			if(last_type != -1)
				type_mat[last_type][word_type]++;
			last_type = word_type;
			
			alltimes++;
		}
		fin.close();
		cout << '/' << endl;
	}
	
	unordered_map<string, Info>::iterator it;
	cout << "Writing to FILE..." << endl;
	ofstream fout("dictionary");
	fout << alltimes << endl;
	fout << words.size() << endl;
	for(it = words.begin(); it != words.end(); it++)
	{
		fout << it->first << ' ' << (it->second).times << endl;
		for(int i = 1; i <= type_n; i++)
			fout << type[i] << ' ' << (it->second).type[i] << endl;
	}
	fout.close();
	
	for(int i = 1; i <= type_n; i++)
		for(int j = 1; j <= type_n; j++)
			type_mat[i][0] += type_mat[i][j];
	ofstream fout2("TypeMatrix");
	for(int i = 1; i <= type_n; i++)
		fout2 << type_mat[i][0] << endl;
	for(int i = 1; i <= type_n; i++)
	{
		for(int j = 1; j <= type_n; j++)
			fout2 << type_mat[i][j] << ' ';
		fout2 << endl;
	
	}
	fout2.close();
	return 0;
}
