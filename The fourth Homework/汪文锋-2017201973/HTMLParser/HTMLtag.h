#ifndef HTMLtag
#define HTMLtag
#include<string>
#include<vector>
using std::string;
using std::vector;
class nature
{
public:
	friend class Parser;
	friend class Tree;
	friend class Htag;
	string tag;
	string text;
	nature();
	nature(string tag_, string text_);
	~nature();
};
class Htag
{
private:
	string tag;
	string text;
	vector<nature> Hclass;
public:
	friend class Parser;
	friend class Tree;
	Htag();
	Htag(string tag);
	~Htag();
};
#endif