#include"WebCrawlerGlobal.h"
#include<string>
using namespace std;
WebCrawlerGlobal::WebCrawlerGlobal()
{
	findhref = "<a href=";
	hreflen = findhref.length();
	findhttp = "http://";
	httplen = findhttp.length();
	findtitle = "<title>";
	titlelen = findtitle.length();
	finduntitle = "</title>";
	untitlelen = finduntitle.length();
}