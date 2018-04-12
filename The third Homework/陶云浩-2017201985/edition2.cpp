#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<set>
#include<queue>

using namespace std;
class tyh
{
private:
set<string>my_set;
queue<string>my_queue;
string source ;
int Max_url_length ;
int Max_line_length  ; 
void open_web_page(string target_url)
{
	string prefix = "wget -O current_page.txt ";
	string order = prefix + target_url;
	const char* command = order.data();
	system(command);
	return ;
}
void find_url(string current_url,string source)
{
	ifstream fin;
	char current_str[Max_line_length];
	string str;
	fin.open("current_page.txt");
	if(current_url.find("/")!=string::npos)
	{
		current_url.erase(current_url.rfind("/"),Max_line_length);	
	}
	while(fin.getline(current_str,Max_line_length))
	{
		str=current_str;
		if(str.find("<a ")==string::npos)continue;
		int found=str.find("<a ");
		int i;
		while(found!=string::npos)
		{
			str[found]='x';
			char temp_url[Max_line_length];
			int flag=1,t=0;
			while(str.find("href=")<found)
			str[str.find("href=")]='x';
			for(i=str.find("href=");i<=Max_line_length;i++)
			{
				if(str[i]=='"'&&flag==1)
				{
					flag=0;
					continue;
				}
				if(flag==1)continue;
				else 
				{
					if(str[i]=='"'){temp_url[t]='\0';break;}
					temp_url[t]=str[i];
					t++;
				}
				if(i==str.length()-1){flag=2;break;}
			}
			if(flag==2)break;
			string temp_url_str=temp_url;
			string url_str;
			if(temp_url_str.find("http")!=string::npos)
			{
				if(temp_url_str.find(source)==string::npos)
				{
					found=str.find("<a ");
					continue;
				}
				else
				{
					temp_url_str=temp_url_str.erase(0,temp_url_str.find(source));
					if(my_set.count(temp_url_str)==0)
					{
						my_queue.push(temp_url_str);
						my_set.insert(temp_url_str);
					}
					found=str.find("<a ");
					continue;
				}
			}
			if(temp_url_str[0]!='/')
			temp_url_str="/"+temp_url_str;
			url_str=current_url+temp_url_str;
			if(my_set.count(url_str)==0)
			{
				my_queue.push(url_str);
				my_set.insert(url_str);
			}
			found=str.find("<a ");
		}
	}
	return ;
}
public:
tyh ()
{ 
	cin >> source ;
	Max_url_length = 1000 ;
	Max_line_length = 100000 ;
}
tyh(string inputsource)
{
	source = inputsource ;
	Max_url_length = 1000 ;
	Max_line_length = 100000 ;
}
int crawl()
{	
	if(source.find("http")!=string::npos)
	source=source.erase(0,source.find("/")+2);
	my_queue.push(source);
	my_set.insert(source);
	int ans;
	while(!my_queue.empty())
	{	
		if(my_queue.front().find(".dox")==string::npos)
		if(my_queue.front().find(".xls")==string::npos)
		if(my_queue.front().find(".pdf")==string::npos)
		{
			cout<<ans<<endl<<my_queue.front()<<endl;
			ans++;	
			open_web_page(my_queue.front());
			find_url(my_queue.front(),source);
		}
		my_queue.pop();
	}
	return ans;
}
;};
int main()
{
	tyh crawler("info.ruc.edu.cn");
	cout<<crawler.crawl();
	return 0;
}
