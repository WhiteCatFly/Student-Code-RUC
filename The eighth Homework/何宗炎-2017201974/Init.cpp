#ifndef Init_Hzy_CPP_
#define Init_Hzy_CPP_
#include "global_settings.cpp"
#include "Init.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <fstream>

void ReBuild(std::map <std::string, Words> & Mp, std::vector <WebPage> & WP) {
	using namespace std;
	int num = 0;
	fstream Name(NameList, ios::in);
	string s;
	while(Name >> s) {
		WebPage wp;
		wp.name = s;
		string temp = s + TitleFile; 
		fstream tmp(temp.c_str(), ios::in);
		string ss;
		while(tmp >> ss) {
		    // if(ss == "IOI") cerr << s << endl;
			Mp[ss].name = ss;
			Mp[ss].add(num, 1);
			wp.add(ss, 1, 1);
		}
		temp = s + BodyFile;
		tmp.close();
		tmp.open(temp.c_str(), ios::in);
		while(tmp >> ss) {
		    // if(ss == "IOI") cerr << s << endl;
			Mp[ss].name = ss;
			Mp[ss].add(num, 0);
			wp.add(ss, 1, 0);
		}
		WP.push_back(wp);
		num++;
	}
	SaveData(Mp, WP);
}

void InitFromSave(std::map <std::string, Words> & Mp, std::vector <WebPage> & WP) {
    using namespace std;
    fstream saves(SaveFile, ios::in) ;
    string s, ss; int tmp;
    while(saves >> s) {
	if(s == NameEnds) break;
	Mp[s].name = s;
	while(saves >> tmp) {
	    if(tmp == Ends) break;
	    Mp[s].Title.insert(tmp);
	}
	while(saves >> tmp) {
	    if(tmp == Ends) break;
	    Mp[s].ALL.insert(tmp);
	}
    }
    while(saves >> s)
	{
	    if(s == NameEnds) break;
	    WebPage wp;
	    wp.name = s;
	    while(saves >> ss >> tmp) {
		if(ss == NameEnds) break;
		wp.WordCounts_tit[ss] = tmp;
	    }
	    while(saves >> ss >> tmp) {
		if(ss == NameEnds) break;
		wp.WordCounts_all[ss] = tmp;
	    }
	    saves >> wp.ALLWords_tit >> wp.ALLWords_all ;
	    WP.push_back(wp);
	}
    saves.close();
}

void SaveData(std::map <std::string, Words> & Mp, std::vector <WebPage> & WP) {
    using namespace std;
    fstream saves(SaveFile, ios::out);
    map <string, Words>::iterator mit;
    set <int>::iterator sit;
    for(mit = Mp.begin(); mit != Mp.end(); mit++) {
	saves << mit->fir << endl;
	for(sit = (mit->sec).Title.begin(); sit != (mit->sec).Title.end(); sit++)
	    saves << *sit << " ";
	saves << Ends << endl;
	for(sit = (mit->sec).ALL.begin(); sit != (mit->sec).ALL.end(); sit++)
	    saves << *sit << " ";
	saves << Ends << endl;
    }
    saves << NameEnds << endl;
    map <string, int>::iterator it;
    for(size_t i = 0; i < WP.size(); ++i) {
	saves << WP[i].name << endl;
	for(it = WP[i].WordCounts_tit.begin(); it != WP[i].WordCounts_tit.end(); it++)
	    saves << it->fir << " " << it->sec << endl;
	saves << NameEnds << " " << 0 << endl;
	for(it = WP[i].WordCounts_all.begin(); it != WP[i].WordCounts_all.end(); it++)
	    saves << it->fir << " " << it->sec << endl;
	saves << NameEnds << " " << 0 << endl;
	saves << WP[i].ALLWords_tit << " " << WP[i].ALLWords_all << endl;
    }
    saves << NameEnds << endl;
    saves.close();
}

#endif
		
