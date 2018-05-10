#ifndef PARSER_HZY_CPP_
#define PARSER_HZY_CPP_
#include "Parser.h"
#include "global_setting.cpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#define CheckAss(s) (NoAss.find(SearchChanger(s), 0) == std::string::npos ? 1 : 0)
#define CheckBanner(s) (Banner.find(SearchChanger(s), 0) == std::string::npos ? 0 : 1)

std::string Tolower(std::string s) {
    std::string tmp;
    for(size_t i = 0; i < s.size(); ++i)
	tmp += (Upper(s[i]) ? s[i] + Delta : s[i]);
    return tmp;
}
Tag Build_Tag(std::string s) {
    using namespace std;
    int n = s.size() - 1, p = 1;
    string Name, typ, val;
    bool SetName = 0;
    Tag T;
    while(p < n) {
        if(s[p] == Space) {
            do {
                ++p;
	    }while(p < n && s[p] == Space);
            continue;
        }
        if(!SetName) {
            while(p < n && s[p] != Space) Name += s[p++];
	    Name = Tolower(Name);
            T.SetTagType(Name);
            SetName = 1;
        }
        else {
            typ = val = Empty;
            while(p < n && s[p] != Space && s[p] != EqualMark) typ += s[p++];
            if(s[p] == EqualMark) {
                do {
                    ++p;
		}while(p < n && s[p] == Space);
                if(s[p] != QuateMark)
                    while(p < n && s[p] != Space) val += s[p++];
                else {
		    do {
			val += s[p++];
		    }while(p < n && s[p] != QuateMark);			
                    if(p < n) val += s[p++];
                }
            }
            Attribute att(typ, val);
            T.AddAttribute(att);
        }
    }
    return T;
}
/*bool CheckAss(std::string s) {
    for(int i = 0; i < NoTailNum; ++i)
	if(StringTolower(s) == NoTail[i]) return 0;
    return 1;
    }*/

std::string Build_Node(Node & n, std::stringstream & st, std::string tagname, std::string Lef) {
    using namespace std;
    string temp = Empty, tmp = Lef;
    size_t p1, p2;
    bool b1 = 0, b2 = 0;
    do {
        temp = temp + Spacestring + tmp;
	
        if(!b1) p1 = tmp.find(LeftMark, 0);
        if(!b2) p2 = tmp.find(RightMark, 0);
        if(!b1 && (p1 != string::npos)) b1 = 1;
        if(!b2 && (p2 != string::npos)) b2 = 1;
	
        if(b1 && b2) {
            p1 = temp.find(LeftMark, 0);
            p2 = temp.find(RightMark, 0);
	    if(p1 > p2) {
		tmp = temp.substr(0, p2);
		n.AddText(tmp);
		tmp = temp.substr(p2 + 1);
		temp = Empty;
		b1 = b2 = 0;
		continue;
	    }		
	    
            tmp = temp.substr(0, p1);
            n.AddText(tmp);
	    
            tmp = temp.substr(p1, p2 - p1 + 1);
            Tag T = Build_Tag(tmp);
            tmp = temp.substr(p2 + 1);
	    temp = Empty;
	    
	    b1 = b2 = 0;
            if(AssMark + tagname == T.CheckTagName())
		return tmp;
	    if(IgnoreMark == T.CheckTagName().at(0) || AssMark == T.CheckTagName().at(0)) 
		continue;

	    
            Node sn;
	    sn.SetTag(T);

	    
	    if(CheckBanner(T.CheckTagName())) {
		do {
		    temp = temp + Spacestring + tmp;
		    if(Tolower(tmp).find(AssMark + T.CheckTagName(), 0) != string::npos) {
			
			string tp = Empty;
			tp += LeftMark, tp += AssMark, tp += T.CheckTagName() + RightMark;
			
			size_t p = Tolower(temp).find(tp, 0);
			tmp = temp.substr(0, p);
			sn.AddText(tmp);
			
			while(temp[p] != RightMark) p++;
			tmp = temp.substr(p + 1);
			temp = Empty;
			break;
		    }
		    if(!(st >> tmp)) break;
		}while(1);
	    }
	    else if(CheckAss(T.CheckTagName())) 
		tmp = Build_Node(sn, st, T.CheckTagName(), tmp) ;
	    n.AddSubNode(sn);
	    continue;
        }
	if(!(st >> tmp)) break;
    }while(1);
    return temp;
}

/*<---------------------------------------------------->*/

Parser::Parser(std::stringstream & st) {
    using namespace std;
    string temp = Empty, tmp = Empty;
    size_t p1, p2;
    bool b1 = 0, b2 = 0;
    do  {
	temp = temp + Spacestring + tmp;
	
	if(!b1) p1 = tmp.find(LeftMark, 0);
        if(!b2) p2 = tmp.find(RightMark, 0);
        if(!b1 && (p1 != string::npos)) b1 = 1;
        if(!b2 && (p2 != string::npos)) b2 = 1;
	
	if(b1 && b2) {
            p1 = temp.find(LeftMark, 0);
            p2 = temp.find(RightMark, 0);
	    
	    tmp = temp.substr(p1, p2 - p1 + 1);
	    Tag T = Build_Tag(tmp);
	    tmp = temp.substr(p2 + 1);
	    temp = Empty;

	    b1 = b2 = 0;
	    //st << temp;
	    if(T.CheckTagName() == HTMLTagName) {
		HTML = T;
		Node tp;
		tp.clear();
		Build_Node(tp, st, HTMLTagName, tmp);
		Head = tp.FindTag(HeadTagName);
		Body = tp.FindTag(BodyTagName);
		break;
	    }
	    continue;
	}
	if(!(st >> tmp)) break;
    }while(1);
}

Parser::~Parser() {
	clear();
}

void Parser::ShowHead(LL mode) {
    Head.ShowSubNode(mode);
}
void Parser::ShowBody(LL mode) {
    Body.ShowSubNode(mode);
}
void Parser::clear() {
    Head.clear(), Body.clear();
    HTML.clear();
}
#endif
