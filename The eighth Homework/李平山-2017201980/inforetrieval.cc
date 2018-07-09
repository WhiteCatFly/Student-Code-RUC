#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <math.h>
#include <cstring>
#include "inforetrieval.h"

map< string, map< string, double > > chart;
void countnum(string name,string file,int val)
{
	ifstream fread(name.c_str());
	string word;
	while(fread >> word)
	{
		chart[word][file] += val;
	}
	fread.close();	
}
void read()
{
	ifstream fin("file_list.txt");
	char url[505];
	while(fin.getline(url,500))
	{
		N++;		
		int len = strlen(url);
		string name("");
		string file = url;
		name = url;
		name += ".body";
		int val = 1;
		countnum(name,file,val);
		name = url;
		name += ".title";
		val = 10;
		countnum(name,file,val);
	}
	fin.close();
}
void build()
{
	for( map<string,map<string,double> > :: iterator it_w = chart.begin(); it_w != chart.end(); it_w++)
	{
		for(map<string,double> :: iterator it_f = it_w->second.begin(); it_f != it_w->second.end(); it_f++)
		{
			it_f->second = ( 1+log10(it_f->second))*( 1 + log10(double(N)) - log10( double( it_w->second.size() ) ) ); 
		}
	}
}



