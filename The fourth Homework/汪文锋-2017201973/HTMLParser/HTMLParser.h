#ifndef HTMLParser
#define HTMLParser
#include<string>
#include<sstream>
#include<fstream>
#include"HTMLTree.h"
using std::string;
using std::fstream;
using std::stringstream;
class Parser
{
private:
	string page;
public:
	Parser();
	Parser(fstream &File);
	Parser(stringstream &Str);
	Parser(string Str);
	~Parser();
	string getag(string text);
	void getnature(string text,Tree *now);
	void getext(string text, Tree *now);
	void getstruct();
	void dfs_tag(string type,Tree* root);
	void dfs_suffix(string type, Tree* root);
};
#endif