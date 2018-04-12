#ifndef Cral_Hzy_CPP_
#define Cral_Hzy_CPP_

#include "Hzydef.h"
#include "Url_Get.h"
#include "Web_Cral.h"
#include "Cral.h"
#include "global_setting.h"

/*const string Base_Site = "info.ruc.edu.cn";
const string Ins = "wget -O ";
const string First_Url = "index";
clock_t pre;
void Cral_Web(string s)
{
  //const char * p = s.c_str();
	while(clock() - pre < 100000);
	pre = clock();
	system((Ins + GetFileName(s) + " " + Base_Site + "/" + s).c_str());
	}*/
void Hzy_Cral(string s) 
{
	Base_Site = s;
	queue <string> Url_Queue; // use for store url
	string temp, tmp;
	//int count_er = 0;
	Url_Queue.push("");
	//FILE * p = fopen("log.txt", "w");
	//pre = clock();
	while(!Url_Queue.empty())
		{
			temp = Url_Queue.front(), Url_Queue.pop();
			//cerr << ++count_er << " " << temp << endl;
			//fwrite(temp.c_str(), temp.size(), 1, p);
			Cral_Web(temp);
			tmp = GetFileName(temp);
			GetUrlFromWeb(tmp, Url_Queue);
		}
	//return 0;
}

void Cral() {
    for(int i = 0; i < seed.size(); ++i)
	Hzy_Cral(seed[i]);
}
 
#else
#endif
