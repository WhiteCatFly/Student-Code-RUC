#include "preprocess.h"

using namespace std;

unordered_map<string, vector<int> > Keys::keys;
vector<string> Keys::filename;
unordered_map<string, int> Keys::forbidden;

void find_all_keys()
{
	string keyword;
	ifstream fin("file_list.txt");
	while(fin >> keyword)
	{
		Keys::filename.push_back(keyword);
	}
	fin.close();
	
	for(int i = 0; i < Keys::filename.size(); i++)
	{
		//cout << path << endl;
		ifstream fin2(Keys::filename[i] + ".body");
		
		while(fin2 >> keyword)
		{
			Keys::keys[keyword].push_back(i);
			if(Keys::keys[keyword].size() > 1 && Keys::keys[keyword][Keys::keys[keyword].size() - 1] == Keys::keys[keyword][Keys::keys[keyword].size() - 2])
				Keys::keys[keyword].pop_back();
		}
		fin2.close();
	
		fin2 = ifstream(Keys::filename[i] + ".title");
		while(fin2 >> keyword)
		{
			Keys::keys[keyword].push_back(i);
			if(Keys::keys[keyword].size() > 1 && Keys::keys[keyword][Keys::keys[keyword].size() - 1] == Keys::keys[keyword][Keys::keys[keyword].size() - 2])
				Keys::keys[keyword].pop_back();
		}
		fin2.close();
	}
	fin.close();
}

void initialize()
{
	string str;
	int keyscount, locationcount, locationnum;
	vector<int> location;
	ifstream fin("file_list.txt");
	
	while(fin >> str)
	{
		Keys::filename.push_back(str);
	}
	fin.close();
	
	fin = ifstream("dictionary.dat");
	fin >> keyscount;
	while(keyscount--)
	{
		fin >> str >> locationcount;
		location.clear();
		while(locationcount--)
		{
			fin >> locationnum;
			location.push_back(locationnum);
		}
		pair<string, vector<int> > pr(str, location);
		Keys::keys.insert(pr);
	}
	fin.close();
	
	fin = ifstream("forbidden.dat");
	while(fin >> str)
		Keys::forbidden[str] = 1;
	fin.close();
}
