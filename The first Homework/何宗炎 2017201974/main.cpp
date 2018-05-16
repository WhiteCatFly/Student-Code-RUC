#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <time.h>
#include <cstdlib>
#include "Hzydef.h"
#include "Url_Get.h"
using namespace std;
const string Base_Site = "info.ruc.edu.cn";
const string Ins = "wget -O ";
const string First_Url = "index";
clock_t pre;
void Cral_Web(string s) {
  //const char * p = s.c_str();
	while(clock() - pre < 100000);
	pre = clock();
	system((Ins + GetFileName(s) + " " + Base_Site + "/" + s).c_str());
}
int main() {
	queue <string> Url_Queue; // use for store url
	string temp, tmp;
	int count_er = 0;
	Url_Queue.push("");
	//FILE * p = fopen("log.txt", "w");
	pre = clock();
	while(!Url_Queue.empty()) {
		temp = Url_Queue.front(), Url_Queue.pop();
		cerr << ++count_er << " " << temp << endl;
		//fwrite(temp.c_str(), temp.size(), 1, p);
		Cral_Web(temp);
		tmp = GetFileName(temp);
		GetUrlFromWeb(tmp, Url_Queue);
	}
	return 0;
}
 
  
