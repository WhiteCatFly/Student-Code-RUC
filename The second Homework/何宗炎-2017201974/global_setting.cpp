#ifndef Global_Setting_Hzy_CPP_
#define Global_Setting_Hzy_CPP_

#include "global_setting.h"

/*const string Ins = "wget -O ";
const string First_Url = "index";
const string Websignal = "href";
const string Webfront = "http";
const string HostName = "index.html";
const int time_interval = 100000;
*/    
    
string Base_Site;
vector<string> seed;

void InitGlobalSetting(const int &argc, char *argv[])
{
    for(char ** pt = argv + 1; *pt != NULL; ++pt)
	seed.push_back(string(*pt));
}

#else
#endif
