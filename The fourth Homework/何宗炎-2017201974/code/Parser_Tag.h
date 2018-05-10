#ifndef PARSER_TAG_HZY_H_
#define PARSER_TAG_HZY_H_
#include <vector>
#include <string>
#include <cstdio>
struct Attribute {
    std::string Type, Value;
    Attribute() {}  
    Attribute(std::string tp, std::string val) : Type(tp), Value(val) {}
    void Show(long long mode) ;
    void clear() ;
};
class Tag {
private:
	std::string TagName;
	long long TagType;
	std::vector< Attribute > ATT;
public:
	Tag() {}
	~Tag() ;
	void SetTagType(std::string s);
	Tag(std::string Typ, std::vector< Attribute > * att) {
		SetTagType(Typ);
		for(size_t i = 0; i < (* att).size(); ++i)
			ATT.push_back((* att)[i]);
	}
	std::string CheckTagName() ;
	long long ShowType();
	void ShowTagName();
	void ShowAttribute(long long mode);
	
	void AddAttribute(Attribute att);
	//void SetTagType(string s);
	void clear();
};
#endif
