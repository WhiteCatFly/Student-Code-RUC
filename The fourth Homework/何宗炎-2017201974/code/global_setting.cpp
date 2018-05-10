#ifndef PARSER_SETTING_HZY_CPP_
#define PARSER_SETTING_HZY_CPP_
#define LL long long
#define db double
#define Upper(c) (c >= 'A' && c <= 'Z')
#define SearchChanger(s) (Spacestring + s + Spacestring)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#include <string>
#include <vector>
#include "Parser_Node.h"
const char Space = ' ';
const char EqualMark = '=';
const char QuateMark = '"';
const char LeftMark = '<';
const char RightMark = '>';
const char AssMark = '/';
const char IgnoreMark = '!';

const std::string Empty = "";
const std::string Spacestring = " ";
const std::string HTMLTagName = "html";
const std::string HeadTagName = "head";
const std::string BodyTagName = "body";

const LL NoneType = 0;
const LL Title = (1LL << 0);
const LL Text = (1LL << 1);
const LL Url = (1LL << 2);
const LL Img = (1LL << 3);
const LL Script = (1LL << 4);
const LL Button = (1LL << 5);
const LL Table = (1LL << 6);
const LL Video = (1LL << 7);
const LL audio = (1LL << 8);
const LL ALL = (1LL << 62) + ((1LL << 62) - 1);

const LL Att_Type = (1LL << 0);
const LL Att_Value = (1LL << 1);

const std::string NoAss = " input br hr img option meta link ";       
const int TypeLim = 63;
const std::string Type[TypeLim] = {
	" h1 h2 h3 h4 h5 h6 caption title ",
	" div p article b big center code del em i ins pre tt u small sub mark strong sup ",
	" a base nav ",
	" img canvas ",
	" script ruby ",
	" button command ",
	" table ",
	" video ",
	" audio ",
};

const std::string Banner = " script code ruby ";
const Node BadNode;

const int Delta = 'a' - 'A';


#endif
