#pragma GCC diagnostic error "-std=c++11"
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<regex>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<streambuf>

using namespace std;

class Html { // store the html's original content
public:
	friend void extract (const Html& html,const string& pattern,vector<string>& packet);
	friend void extract_url (const Html& html,vector<string>& urls);
	friend void extract_head (const Html& html,vector<string>& heads);
	friend void extract_body (const Html& html,vector<string>& bodies);
	
	Html(string& t) : content_(t) {} // from string
	Html(ifstream& in) : content_("") // from file
	{
		string buf;
		while (getline(in,buf)) {
			content_ += buf;
		}
	} 

private:
	string content_;
};

int main()
{
	ifstream infile("info.ruc.edu.cn");
	Html html_(infile);
	vector<string> urls;
	extract_url(html_,urls);
	if (urls.empty()) cout << "nothing" << endl;	

	for (auto ele : urls)
		cout << ele << endl;
	return 0;
}

void extract (const Html& html,const string& pattern,vector<string>& packet)
{
	regex r(pattern);
	smatch result;
	for (sregex_iterator it(html.content_.begin(),html.content_.end(),r) , end_it;
		it != end_it; ++it)
		packet.push_back(it->str());
}

void extract_url (const Html& html,vector<string>& urls)
{
	string pattern("<a.*?href[^=]*=[^\"]*\"([^\"]*)\"[^>]*>");
	regex r(pattern);
	for (sregex_iterator it(html.content_.begin(),html.content_.end(),r) , end_it;
		it != end_it; ++it) {
		urls.push_back(it->str(1));
	}
}

void extract_head (const Html& html,vector<string>& heads)
{
	string pattern("<h[0-9][^>]*>([^</]*)</h[0-9]>");
	regex r(pattern);
	for (sregex_iterator it(html.content_.begin(),html.content_.end(),r) , end_it;
		it != end_it; ++it) {
		heads.push_back(it->str(1));
	}
}	

void extract_body (const Html& html,vector<string>& bodies)
{
	string pattern("<body[^>]*>([^</]*)</body>");
	regex r(pattern);
	for (sregex_iterator it(html.content_.begin(),html.content_.end(),r) , end_it;
		it != end_it; ++it) {
		bodies.push_back(it->str(1));
	}
}

