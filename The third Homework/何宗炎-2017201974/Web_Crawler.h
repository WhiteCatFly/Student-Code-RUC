#ifndef Web_Crawler_Hzy_H_
#define Web_Crawler_Hzy_H_
#include <bits/stdc++.h>
#include "Hzydef.h"
#include "HashValueSet.h"
using namespace std;
const string Ins = "wget -O ";
const string First_Url = "index";
const string Websignal = "href";
const string Webfront = "http";
const string HostName = "index.html";
const LL seed1 = 277;
const LL seed2 = 311;
class HzyWebCrawler {
private:
    int time_interval;
    string Base_Site ;
    vector< string > seed;

    set< HashValueSet > WebpageSet ;
	
    void Hzy_Crawl(string s) ; //in Crawl.cpp

    HashValueSet CalcHashValue(string str) ;
    bool IfLegal(string & str) ;
    void FindUrl(string code_str, queue< string > & url, string & temp, size_t & status) ;
    void GetUrlFromWeb(const string File_Name, queue < string > & url) ; //in Url_Get.cpp
    
    string GetFileName(string s) ;
    void Crawl_Web(string s) ; // in Web_Crawl.cpp
    
public:
    HzyWebCrawler() {}
    HzyWebCrawler(vector< string > dseed, int dtime_interval) ;
    ~HzyWebCrawler() {}
    
    void InitGlobalSetting() ;
    void Crawl() ;
    void CheckSetting() const ;
};

#else
#endif
