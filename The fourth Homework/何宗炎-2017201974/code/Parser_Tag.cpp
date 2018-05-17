#ifndef PARSER_TAG_HZY_CPP_
#define PARSER_TAG_HZY_CPP_
#include "Parser_Tag.h"
#include "global_setting.cpp"
#include <string>
#include <vector>
#include <iostream>

/*<--------------------------------------*/

void Attribute::Show(LL mode) {
    using namespace std;
    if(mode & Att_Type) cout << Type << EqualMark;
    if(mode & Att_Value) cout << Value << endl;
}
void Attribute::clear() {
    Type = Value = Empty;
}

/*<---------------------------------------*/

Tag::~Tag() {
    clear();
}

std::string Tag::CheckTagName() {
    return TagName;
}
LL Tag::ShowType() {
    return TagType;
}
void Tag::ShowTagName() {
    std::cout << TagName << std::endl;
}
void Tag::ShowAttribute(LL mode) {
    for(size_t i = 0; i < ATT.size(); ++i)
	ATT[i].Show(mode);
}

void Tag::AddAttribute(Attribute att) {
	ATT.push_back(att);
}
void Tag::SetTagType(std::string s) {
    TagType = NoneType;
    for(int i = 0; i < TypeLim; ++i)
	if(Type[i].find(SearchChanger(s), 0) != std::string::npos) TagType |= (1 << i);
    TagName = s;
}
void Tag::clear() {
    TagName = Empty;
    TagType = NoneType;
    ATT.clear();
}

/*<-------------------------------------*/


#endif
