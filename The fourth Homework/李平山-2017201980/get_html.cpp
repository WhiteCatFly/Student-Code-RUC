#include <iostream>
#include "parser.h"
#include "standardize.h"

bool in_use(char x)
{
	if(x != ' ' && x != '\t' && x != '\n') return 1;
	return 0;
}
string add(string temp,string home)
{
	int flag = 0;
	int now = 0;
	now = home.find("//",now);
	now++;
	while(home.find("/",now+1) != string::npos && home.find("/",now+1) != home.length()-1)
	{
		flag = 1;
		now = home.find("/",now+1);
	}
	if(flag && home.find(".",now) != string::npos)  home.erase(now,home.length()-now);
	
	if(temp[0] == '/'||home[home.length()-1] == '/')    return home + temp;
	else 	return home+'/'+temp;
	
}
void Parser::get_html(const char* filename) 
{
	string tmp;
	std::ifstream fin;
	fin.open(filename);


	fin.seekg(0,std::ios::end);
	//int size = fin.tellg();
	tmp.resize(fin.tellg());
	fin.seekg(0,std::ios::beg);
	fin.read(&tmp[0],tmp.size());
	int len = tmp.size();
	for(int i = 0; i <len; i++)
	{
		if(in_use(tmp[i]))
		this->html += tmp[i];
	}

	//this->html = tmp;
	
	fin.close();
	//std::ofstream fout("a.txt");
	//fout<<html;
	//fout.close();
}

void Parser::display(const stringstream& content, const string& name) const
{
	std::ofstream fout;
	const char* filename = name.c_str();
	fout.open(filename);
	fout << content.rdbuf();
	fout.close();
}
