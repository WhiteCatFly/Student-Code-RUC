#include "htmlparser.h"
using namespace std;

string HtmlParser::title() const
{
	if(tit_tag == NULL) return "";
	int siz = tit_tag -> strs.size();
	string str("");
	for(int i = 0;i < siz; ++i) str += tit_tag -> strs[i];
	return str;
}

Tag HtmlParser::head() const
{
	if(_root == NULL) return nul_tag;
	Tag* p = _root -> _son;
	while(p != NULL && p -> name != "html") p = p -> _nxt;
	if(p == NULL) return nul_tag;
	for(p = p -> _son; p != NULL; p = p -> _nxt) if(p -> name == "head") return *p;
	return nul_tag;
}

Tag HtmlParser::body() const
{
	if(_root == NULL) return nul_tag;
	Tag* p = _root -> _son;
	while(p != NULL && p -> name != "html") p = p -> _nxt;
	if(p == NULL) return nul_tag;
	for(p = p -> _son; p != NULL; p = p -> _nxt) if(p -> name == "body") return *p;
	return nul_tag;	
}


int HtmlParser::links(string path, const string& file)
{
	if(_root == NULL) return 0;
	else return _root -> links(path, file);
}

int HtmlParser::images(const string& path)
{
	if(_root == NULL) return 0;
	else return _root -> images(path);
}

int HtmlParser::sounds(const string& path)
{
	if(_root == NULL) return 0;
	else return _root -> sounds(path);
}

int HtmlParser::words(const string& path)
{
	if(_root == NULL) return 0;
	else return _root -> words(path);	
}

