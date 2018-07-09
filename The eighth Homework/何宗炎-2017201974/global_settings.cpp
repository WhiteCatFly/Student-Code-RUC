#ifndef Global_Settings_Hzy_CPP_
#define Global_Settings_Hzy_CPP_
#define db double
#define LL long long
#define fir first
#define sec second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

const int Para_Num = 4;
const std::string Para[4] = {"-show_lines", "title_only", "-words", "-rebuild"};

const char * const THUlac = "./thulac -seg_only -input Input.txt -output result.txt";
const std::string InputFile = "Input.txt";
const std::string OutputFile = "result.txt";
const int Len = 110;

const char * const NameList = "file_list.txt";
const std::string BodyFile = ".body";
const std::string TitleFile = ".title";

const char * const SaveFile = "Savedata.sav";
const int Ends = -9819;
const std::string NameEnds = "hzy9819___";

const std::string Yes = "True";
const std::string No = "False";

//static bool SearchBody = true;
//static int ShowLines = 20;

struct Words {
    std::string name;
    std::set <int> Title, ALL;
    void add(int num, bool tit) {
	ALL.insert(num);
	if(tit)
	    Title.insert(num);
    }
};
struct WebPage {
    std::string name;
    std::map <std::string, int> WordCounts_tit, WordCounts_all;
    int ALLWords_tit, ALLWords_all;
    WebPage() {
	ALLWords_tit = ALLWords_all = 0;
    }
    void add(std::string s, int num, bool tit) {
	WordCounts_all[s] += num;
	ALLWords_all += num;
	if(tit) {
			WordCounts_tit[s] += num;
			ALLWords_tit += num;
	}
    }
    void ShowTitle() {
	std::string temp = name + TitleFile;
	std::fstream f(temp.c_str(), std::ios::in);
	std::string s;
	while(f >> s) std::cout << s;
	std::cout << std::endl;
    }
    
};

#endif
