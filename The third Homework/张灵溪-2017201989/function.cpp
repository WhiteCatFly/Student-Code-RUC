#include <string>
#include <set>
#include <fstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "crawl.h"
using std::string;
using std::set;
using std::queue;
using std::cout;
using std::endl;

bool crawl::find_url(string &line,size_t &start,string &url){
	string first="<a",last="</a>",href="href";
	size_t b=line.find(first,start),e=line.find(last,start);
	static bool flag=false;	
	if(e!=string::npos)
		flag=false;	
	if(b!=string::npos){
		start=b;
		flag=true;
	}
	if(!flag){
		if(getline(web,line)){
			start=0;
			return find_url(line,start,url);
		}
	}
	size_t found=line.find(href,start);
	if(found==string::npos){
		if(getline(web,line)){
			start=0;
			return find_url(line,start,url);
		}
	}
	else{
		size_t front_quo;
		bool flag1=true;
		while(flag1){
		    for(size_t i=found;i<line.size();i++){
			    if(line[i]=='"'||line[i]=='\'')	{
			        front_quo=i+1;
			        flag1=false;
			        break;
			    }
			}
			if(!flag1)
			break;
			getline(web,line);
			found=0;
		}
		for(;;){
		    for(size_t i=front_quo;i<line.size();i++){
			    if(line[i]!='"'&&line[i]!='\'')	
			        url+=line[i];
			    else{
			    	start=i+1;
					return true;
				}
			}
			getline(web,line);
			front_quo=0;
		}			
	}
	return false;
}

bool crawl::check_url(const string &url){
	string http="http",mail="mailto",java="javascript";
	if(url.find(http,0)!=string::npos){
		if(url.find(head,0)==string::npos)
		return false;
		return true;
	}
	if(url.find(mail,0)!=string::npos)
	return false;
	if(url.size()>=2&&url[0]=='/'&&url[1]=='/')
	return false;
	if(url.find(java,0)!=string::npos)
	return false;
	return true;
}

void crawl::merge_url(string &url,const string &root_url){
	if(url.find("http",0)!=string::npos)
	return;
	size_t cur;
	if(root_url.find('/',7)==string::npos)
		cur=root_url.size();		
	else{
		for(cur=root_url.size()-1;cur>=0;cur--){
			if(root_url[cur]=='/')
			break;
		}
	}		
	string temp(root_url,0,cur);
	if(url[0]=='/')
		url=temp+url;
	else
		url=temp+'/'+url;
}

bool crawl::download_web(const string &root_url){
	static int cnt=0;
	char command[300],filename[300];
	sprintf(filename,"%d",cnt);
	sprintf(command,"wget '%s' -O %s",root_url.c_str(),filename);
	system(command);
	web.open(filename);
	if(!web.is_open())
		return false;
	cnt++;	
	return true;
}

void crawl::sleep_polite(){
	int p=0;
	for(int i=0;i<10000;i++)
	p=(p+1)%7;
}

void crawl::crawl_web(){
	queue<string> to_crawl;
	set<string> crawled;
	to_crawl.push(head);
	crawled.insert(head);
	while(!to_crawl.empty()){
		string line,url,root_url;
		root_url=to_crawl.front();
	cout<<root_url<<endl;
		
		to_crawl.pop();	
		if(!download_web(root_url))
		continue;
		size_t start=0;	
		while(find_url(line,start,url)){
			if(check_url(url)){
				merge_url(url,root_url);
				if(!crawled.count(url)){
					to_crawl.push(url);
					crawled.insert(url);
				}
			}		
			url.clear();
		}
		sleep_polite();
	}
}
