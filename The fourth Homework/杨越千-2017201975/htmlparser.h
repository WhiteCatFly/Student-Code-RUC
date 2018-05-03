#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <map>
#include <regex>
#include <string>
#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "consts.h"

const int cmd_maxlen = 1024;

class HtmlParser;
class Tag{
	friend class HtmlParser;
private:	
	Tag* _fa, *_pre, *_nxt;
	Tag* _son; //first son
	std::string url;
	
public:
	enum{_LINK, _IMAGE, _SOUND, _WORD};
	
	std::string name;
	std::vector<std::string> strs, cmts;
	std::map<std::string, std::string> attrs;		

	const std::string& operator [](const std::string& str) const{
		if(attrs.count(str) > 0) return attrs.find(str) -> second;
		else return nul_str;
	}
	bool operator ==(const Tag& tg) const;
	bool operator !=(const Tag& tg) const;
	

	Tag() {_fa = _pre = _nxt = _son = NULL; name = ""; }
	~Tag() {}

	int links(std::string path = def_path, const std::string& file = def_file);
	int images(const std::string& path = def_path); //relative or absolute
	int sounds(const std::string& path = def_path);
	int words(const std::string& path = def_path); //docs, excels, pdfs, ...
	Tag* prev() const{return _pre; }
	Tag* next() const{return _nxt; }
	Tag* fa() const{return _fa;}
	Tag* son() const{return _son; }

	Tag find(const std::string& str) const;
	std::vector<Tag> find_all(const std::string& str) const;
	
};
const Tag nul_tag;


class HtmlParser{
private:
	Tag* _root, *cur_tag, *tit_tag;
	int r_mode;
	std::ifstream file;
	std::stringstream sfile;
	std::string init_url, text;

	//void cpdfs(Tag* &cur_tag, Tag* &tit_tag, const Tag* htm_tag, const Tag* &htm_tit);
	void ParseStrs(const std::string& str, int l, int r);
	void ParseEndtag(std::string str);
	void ParseCmt(std::string str);
	void ParseTag(std::string str);
	void Init();	
	
public:		
	HtmlParser() {_root = cur_tag = tit_tag = NULL; r_mode = 0; }
	~HtmlParser();
	HtmlParser(const HtmlParser& htm);		
	HtmlParser(std::string str, std::string url, int mode = def_mode);
	HtmlParser& operator =(const HtmlParser& htm);
	
	Tag* root() const {return _root; }
	std::string title() const;
	Tag head() const;
	Tag body() const;
	
	int links(std::string path = def_path, const std::string& file = def_file);
	int images(const std::string& path = def_path); //relative or absolute
	int sounds(const std::string& path = def_path);
	int words(const std::string& path = def_path); //docs, excels, pdfs, ...

	Tag find(const std::string& str) const;
	std::vector<Tag> find_all(const std::string& str) const;
	
};

#endif
