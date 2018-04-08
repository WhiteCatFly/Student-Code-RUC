#ifndef SPIDER_H_
#define SPIDER_H_

#include<set>
#include<queue>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <unistd.h>

#define ULL unsigned long long

const int cmd_maxlen = 1024;
const int string_maxlen = 1024;
const int string_maxnum = 100;
const int def_sleep_time = 500000;
	
const int SEED = 257, SEED2 = 263;
	
const std::string def_url = "http://www.ruc.edu.cn/";
const std::string def_dom = "ruc.edu.cn";
const char def_index[12] = {"index.html"};

class Spider{
  private:
	void Bfs(std::string, std::string, int);

	int FindUrl(const std::string &, const std::string &, const std::string &, std::string[]);
	void FindDir(std::string, char*);
	void ModifyUrl(std::string &);
	void FindRoot(std::string, std::string &);

	std::string MergeUrl(std::string, const std::string &);
	bool IfUrl(std::string &, const std::string &);
	inline bool IfEsc(char s) {return s == '\t' || s == '\n' || s == '\r'; }

	bool IfMulti(const std::string &);

	std::set <std::pair<ULL, ULL> > hash_set;
	std::string index;
	
  public:
	Spider();
	~Spider();
	void run(std::string = def_url, std::string = def_dom, int = def_sleep_time);
	std::string ask_index() const;
	void set_index(std::string);
	void clear();
};

#undef ULL

#endif
