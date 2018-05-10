#ifndef PARSER_NODE_HZY_H_
#define PARSER_NODE_HZY_H_
#include "Parser_Tag.h"
#include <cstring>
#include <vector>
class Node {
private:
	Tag Mtag ;
	std::vector< Node > SubNode ;
	std::string Text ;
public:
	Node() {}
	~Node() ;
	Node(Tag T, std::vector< Node > * SN, std::string tx) {
		Mtag = T;
		for(size_t i = 0; i < (* SN).size(); ++i)
			SubNode.push_back((* SN)[i]);
		Text = tx;
	}
	void SetTag(Tag T) ;
	void AddSubNode(Node p) ;
	void AddText(std::string s);
	Tag CheckTag() ;

	Node FindTag(std::string s);
	void ShowTag(long long mode) ;
	void ShowText() ;
	bool CheckType(long long mode) ;
	void ShowSubNode(long long mode);
	void clear();
};
#endif
