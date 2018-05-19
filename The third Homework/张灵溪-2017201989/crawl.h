#ifndef CRAWL_H
#define CRAWL_H
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
class crawl{
	private:
	string head;
	ifstream web;
	bool find_url(string &line,size_t &start,string &url);
	bool check_url(const string &url);
	void merge_url(string &url,const string &root_url);
	bool download_web(const string &root_url);
	void sleep_polite();	
	public:
	void crawl_web();
	crawl(string a):head(a){}
	~crawl(){}
};
#endif
	
	
