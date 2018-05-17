#ifndef PARSER_HZY_H_
#define PARSER_HZY_H_
#include "Parser_Node.h"
#include "Parser_Tag.h"
#include "global_setting.cpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
class Parser {
private:
    Node Head, Body;
    Tag HTML;
public:
    Parser() {}
    ~Parser() ;
    Parser(Node hd, Node bd, Tag T) : Head(hd), Body(bd), HTML(T) {}
    Parser(std::stringstream & ss) ;
    Parser(const char * f) {
	using namespace std;
	fstream in(f);
	stringstream ss;
	ss << in.rdbuf();
	//string tmp, temp;
	//while(in >> tmp) temp += Spacestring + tmp;
	//ss << temp;
	*this = Parser{ss};
    }
    Parser(std::string s) {
	std::stringstream ss;
	ss.str(s);
	*this = Parser{ss};
    }
    void ShowHead(long long mode);
    void ShowBody(long long mode);
    void clear();
};
#endif
