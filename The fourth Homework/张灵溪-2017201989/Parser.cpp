#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;
using std::fstream;
string begin_tag[20]={"<h1>","<h2>","<h3>","<h4>","<h5>","<h6>","<H1>","<H2>","<H3>","<H4>","<H5>","<H6>","<p","<P","<a","<A"};
string end_tag[20]={"</h1>","</h2>","</h3>","</h4>","</h5>","</h6>","</H1>","</H2>","</H3>","</H4>","</H5>","</H6>","</p>","</P>","</a>","</A>"};
class parser{
	private:
	stringstream ss;
	string line;
	size_t cur;
	vector<string> title;
	vector<string> text;
	vector<string> url;
	void extract(string &org,const string &tag);
	void delete_tag(string &temp);
	void get_url(string &org);
	void delete_half_tag(string &org);
	void get_txt();
	public:
	parser(){line="";cur=0;get_txt();};
	parser(const char *fp);
	parser(string html);
	~parser(){};
	void show_text();
	void show_url();
	void show_title();
};
parser::parser(const char *fp){
	fstream file(fp);
	ss<<file.rdbuf();
	getline(ss,line);cur=0;
	get_txt();
}
parser::parser(string html){
	ss.str(html);
	getline(ss,line);cur=0;
	get_txt();
}
void parser::show_text(){
	for(size_t i=0;i<text.size();i++)
		cout<<text[i];
	cout<<endl;
}
void parser::show_url(){
	for(size_t i=0;i<url.size();i++){
		if(url[i].size()==0)
		continue;
		cout<<url[i]<<endl;
	}
}
void parser::show_title(){
	for(size_t i=0;i<title.size();i++)
		cout<<title[i]<<endl;
}
void parser::extract(string &org,const string &tag){
	while(line.find(tag,cur)==string::npos){
		for(size_t i=cur;i<line.size();i++)
			org+=line[i];
		if(getline(ss,line))
		cur=0;
		else
		break;
	}
	size_t cur1=line.find(tag,cur);
	for(size_t i=cur;i<cur1;i++){
		org+=line[i];
	}
	cur=cur1+tag.size();
}
void parser::delete_tag(string &temp){
	string org;
	for(size_t i=0;i<temp.size();i++){
		if(temp[i]=='<'){
			while(temp[i]!='>')
				i++;
			continue;
		}
		org+=temp[i];
	}
	temp=org;
}			
void parser::delete_half_tag(string &org){
	size_t cur1=org.find('>');
	string temp(org,cur1+1);
	org=temp;
}
void parser::get_txt(){
	while(1){
		bool flag=false;
		for(size_t i=0;i<16;i++){
			string org;
			if(line.find(begin_tag[i],cur)!=string::npos){
				cur=line.find(begin_tag[i],cur)+begin_tag[i].size();
				extract(org,end_tag[i]);
				delete_tag(org);
				if(i<12)
					title.push_back(org);
				else if(i<14){
					delete_half_tag(org);
					text.push_back(org);
				}
				else{
					get_url(org);
					url.push_back(org);
				}
				flag=true;
			}
		}
		if(flag)
			continue;
		if(getline(ss,line))
			cur=0;
		else
		break;
	}
}
void parser::get_url(string &org){
	size_t cur1=org.find("href");
	string temp;
	for(size_t i=cur1;i<org.size();i++){
		if(org[i]=='\''||org[i]=='"'){
			i++;
			while(i<org.size()&&org[i]!='\''&&org[i]!='"'){
				temp+=org[i];
				i++;
			}
			break;
		}
	}
	org=temp;
}
int main(void){
	parser web("/home/zhanglingxi/test.html");
	web.show_url();
	web.show_text();
	web.show_title();
	return 0;
}
