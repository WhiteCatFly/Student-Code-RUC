#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<queue>
#include<set>
using namespace std;
bool find_url(ifstream &web,string &line,size_t &start,string &url){
	string first="<a",last="</a>";
	string href="href";
	size_t b=line.find(first,start),e=line.find(last,start);
	static bool flag=false;	
	if(e!=string::npos){
		flag=false;
	}
	
	if(b!=string::npos){
		start=b;
		flag=true;
	}
	if(!flag){
		if(getline(web,line)){
			start=0;
			return find_url(web,line,start,url);
		}
	}
	size_t found=line.find(href,start);
	if(found==string::npos){
		if(getline(web,line)){
			start=0;
			return find_url(web,line,start,url);
		}
	}
	else{
		size_t front_quo;
		bool flag=true;
		while(flag){
		    for(size_t i=found;i<line.size();i++){
			    if(line[i]=='"'||line[i]=='\'')	{
			        front_quo=i+1;
			        flag=false;
			        break;
			    }
			}
			if(!flag)
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
bool if_url(string &url,string &root_url,string &head){
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
	return true;
}

void crawl(string &head){
	char command[300],filename[200];
	queue<string> to_crawl;
	set<string> crawled;
	to_crawl.push(head);
	crawled.insert(head);
	int err=0,cnt=0;
	while(!to_crawl.empty()){
		string line,url,root_url;
		root_url=to_crawl.front();
		to_crawl.pop();	
		sprintf(filename,"%d",cnt);
		sprintf(command,"wget '%s' -O %s",root_url.c_str(),filename);
		system(command);
		ifstream web(filename);
		if(!getline(web,line)){	
			err++;
			continue;
		}
		cnt++;
		size_t start=0;	
		while(find_url(web,line,start,url)){
			if(if_url(url,root_url,head)&&!crawled.count(url)){
				to_crawl.push(url);
				crawled.insert(url);
			}		
			url.clear();
		}
		int p=0;
		for(int i=0;i<10000;i++)
		p=(p+1)%7;
	}
	cout<<"total : "<<cnt<<endl<<endl;
    cout<<"the cannot open file "<<err<<endl;
}
int main(void){
	string root_url="http://info.ruc.edu.cn";
	crawl(root_url);
	return 0;
}

