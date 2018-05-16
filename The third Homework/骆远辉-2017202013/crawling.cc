#pragma GCC diagnostic error "-std=c++11"
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<set>
#include<queue>
#include<vector>
#include<unistd.h>
#include<algorithm>
#include<fstream>

using namespace std;

class crawl {
	public:
		crawl(const string &s) : seed(s) {};
		crawl() = default;
		void set_seed(const string &s)
		{
			seed = s;
		}
	private:
		int url_cnt = 0;
		string seed;
		set<string> all_urls;
		queue<string> url_frontier;
		
		void crawling();
		void fetch(const string &url);
		void parse(string &url);
		bool nomalize(string &s,const string &root);
		void findurl(const string &url,vector<string> &newurls);
		string trans(const string &s);
};
int main(void)
{
	string seed = "info.ruc.edu.cn";
	//cin >> seed; // by default = info.ruc.edu.cn
	
	crawl inforuc(seed);
		
	return 0;
}

void crawl::crawling()
{
	if (seed.empty()){
		cerr << "no seed" << endl;
		return;
	}
	do{
		url_cnt++;
		string cur_url = url_frontier.front();
		url_frontier.pop();
		
		fetch(cur_url);
		parse(cur_url); //1.find 3.judge_rep 2.nomalize 4.push	
		//sleep(1);
	}while (!url_frontier.empty());
}

void crawl::fetch(const string &url)
{
	string realurl = trans(url);
	realurl = '"' + realurl + '"'; 
	string t = "wget " + realurl + " -O " + url;
	const char *cstr = t.c_str();
	system(cstr);
	return;
}

void crawl::parse(string &url)
{
	vector<string> newurls;
	
	findurl(url,newurls);
	auto end = newurls.end();
	for (auto beg = newurls.begin() ; beg != end ; ++beg) {
		if (!all_urls.count(*beg)) {
			url_frontier.push(*beg);
			all_urls.insert(*beg);
		}
	}
}


// nomalize the relative path to be the absolute one if not our target return false
bool crawl::nomalize(string &s,const string &root)
{
	const string home = "info.ruc.edu.cn";// restrict the url not go outside
	const string abslt = "http" ;// if absolute path; ????????????? if dont have this?
	size_t ifhome = string::npos , ifabs = string::npos;
	const int http_len = 7; //"http://";
	
	ifabs = s.find(abslt);
	if ( ifabs == string::npos ) {
		if(s[0] == '#') {
			 return false; // isnt a url but a anchor
		}
		size_t ifjavas = s.find("javascript");
		if (ifjavas != string::npos) return false;
		string realroot = root;
		size_t index = realroot.find_last_of(',');
		
		if(index != string::npos)
			realroot.erase(index,string::npos);	
		if (s[0] == '/') {
			s = realroot + s;
		}
		else s = realroot + '/' + s;
	}
	else {
		ifhome = s.find(home);
		if (ifhome == string::npos)
			return false;
		else{
			s.erase(0,http_len); //delete the "http://"
		}		
	}
	
	for (auto & c : s)
		if (c == '/') 
			c = ',';
	return true;
}

void crawl::findurl(const string &url,vector<string> &newurls)
{
	const char *curl = url.c_str();
	auto fileopen = freopen(curl,"r",stdin); // using fstream is better
	
	if (!fileopen) {	
//test << "the url cannot open" << url << endl;
		return;
	}

	do {
		string curtxt; //temporary txt to store a small part of the content of html
		getline(cin,curtxt,'<');
		char tempc; // to judge "<  a"
		cin >> tempc;		
		if (tempc == 'a') {		
			curtxt.clear();
			getline(cin,curtxt,'>');
			size_t index_href = curtxt.find("href");
			size_t index1_l = curtxt.find_first_of('"',index_href+1); // for '"'
			size_t index1_r = curtxt.find_first_of('"',index1_l+1); // l = left r = right
			size_t index2_l = curtxt.find_first_of('\'',index_href+1); 
			size_t index2_r = curtxt.find_first_of('\'',index2_l+1);
			size_t dis1 = index1_r-index1_l-1 , dis2 = index2_r-index2_l-1;
			string tempurl;// = curtxt.substr(index_1+1,index_2-index_1-1);
			if(index1_l != string::npos) {
				tempurl = curtxt.substr(index1_l+1,dis1);
			}
			else if (index2_l != string::npos) {
				tempurl = curtxt.substr(index2_l+1,dis2);
			}
			auto beg = tempurl.begin() , end = tempurl.end();
			tempurl.erase(remove(beg,end,' '),end);  // erase the blank interuption of url 	
			beg = tempurl.begin(); end = tempurl.end();
			tempurl.erase(remove(beg,end,'\n'),end);
			beg = tempurl.begin(); end = tempurl.end();
			tempurl.erase(remove(beg,end,'\t'),end);
			
			bool flag = false;
			flag = nomalize(tempurl,url);
			if (flag)
				newurls.push_back(tempurl);
		
		}
	} while(cin);	
	cin.clear(); // clear the EOF remianed in the buffer 
	fclose(stdin);
}

// transfer the '*' (the filename) to a realurl  
inline string crawl::trans(const string &s)
{
	string str = s;
	for ( auto &c : str)
		if ( c == ',' )
			c = '/';
	return str;
}

/* bugs:
 * 1. cannot use '/' to name a file ; solution 1: erase the http:// on nomalize 
 * 2. the same as 1 but the '/' in the url cannot be use as a file name ; solution 2: '/' -> '<' when needed, transfer'<' -> '/' cannotbe '*' or '?' or '<' or '!' or '`'
 * 3. only 123 websites were successfully download ; solution 3: the buffer must be flush  because "EOF" doesnt be "cin" and remain in the buffer ; u can use fstream to avoid this
 * 4. <a id="A" href="B"> will regard "A" as a url 
 * 5. the relative path is related to the url which delete its tail until '/'
 */
