#ifndef INFO_RET
#define INFO_RET

#include <vector>
#include <string>
#include <map>
#include <iostream>
using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;

class Info_Ret{
private:
	int web_num;
	vector<string> web_title;
	vector<string> web_body;
	vector< map<string, double> > wtd;
	map<string, bool> stop_words;
	const static int max_out_len = 300;
public:
	Info_Ret();
	void make_wtd();
	void search(string str = "");
};

#endif
