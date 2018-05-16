#ifndef HTMLTree
#define HTMLTree
#include<string>
#include<vector>
#include"HTMLtag.h"
using std::string;
using std::vector;
class Tree
{
private:
	Htag value;
	Tree* father;
	vector<Tree*> child;
public:
	friend class Parser;
	Tree();
	Tree(Htag tag);
	//Tree(T tag, Tree<T>* father_);
	~Tree();
};
#endif