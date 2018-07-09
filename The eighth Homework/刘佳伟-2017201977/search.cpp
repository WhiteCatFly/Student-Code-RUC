#include "search.h"

using namespace std;

void Print(ifstream &fin, ostream &out, vector<string> &key)
{
	string str;
	while(getline(fin, str))
	{
		bool find_key = false;
		for(int i = 0; i < key.size(); i++)
			if(str.find(key[i]) != string::npos)
			{
				find_key = true;
				break;
			}
		
		if(find_key)
		{
			stringstream ss;
			string word;
			
			ss << str;
			out << "......";
			
			while(ss >> word)
			{
				if(find(key.begin(), key.end(), word) != key.end())
					out << "\033[34m\033[1m";
				out << word << "\033[0m ";
			}
			
			out << "......" << endl << endl;
		}
	}
}

void SearchKey(ostream &out, int pagefile, vector<string> &key)
{
	out << "\033[1m\033[4m" << Keys::filename[pagefile] << "\033[0m" << endl << endl;
	
	ifstream fin(Keys::filename[pagefile] + ".title");
	Print(fin, out, key);
	fin.close();
	
	fin = ifstream(Keys::filename[pagefile] + ".body");
	Print(fin, out, key);
	fin.close();
	
	out << "----------------------------------------------------------------" << endl << endl;
}
