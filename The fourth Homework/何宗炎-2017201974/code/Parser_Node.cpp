#ifndef PARSER_NODE_HZY_CPP_
#define PARSER_NODE_HZY_CPP_
#include "Parser_Node.h"
#include "global_setting.cpp"
#include <cstring>
#include <vector>
#include <iostream>

Node::~Node() {
    clear();
}

void Node::SetTag(Tag T) {
    Mtag = T;
}
void Node::AddSubNode(Node p) {
    SubNode.push_back(p);
}
void Node::AddText(std::string s) {
    Text = Text + Spacestring + s;
}

Tag Node::CheckTag() {
    return Mtag;
}

Node Node::FindTag(std::string s) {
    for(size_t i = 0; i < SubNode.size(); ++i) {
	Tag T = SubNode[i].CheckTag();
	if(T.CheckTagName() == s) return SubNode[i];
    }
    return BadNode;
}

void Node::ShowTag(LL mode) {
    Mtag.ShowTagName();
    Mtag.ShowAttribute(mode);
}
void Node::ShowText() {
    std::cout << Text << std::endl;
}
bool Node::CheckType(LL mode) {
    return mode & Mtag.ShowType();
}
void Node::ShowSubNode(LL mode) {
    for(size_t i = 0; i < SubNode.size(); ++i) {
	if( SubNode[i].CheckType(mode) ) {
	    SubNode[i].ShowTag(ALL);
	    SubNode[i].ShowText();
	    SubNode[i].ShowSubNode(ALL);
	}
	else
	    SubNode[i].ShowSubNode(mode);
	}
}
void Node::clear() {
    Mtag.clear();
    SubNode.clear();
    Text = Empty;
}

#endif
