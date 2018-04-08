#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<set>
#include<queue>
using namespace std;
set<string>my_set;
queue<string>my_queue;
void open_web_page(string target_url)
{
	string prefix = "wget -O current_page.txt ";
	string order = prefix + target_url;
	const char* command = order.data();
	system(command);
	return ;
}

void find_url(string current_url)
{
	ifstream fin;
	char current_str[100000];
	string str;
	fin.open("current_page.txt");
	if(current_url.find("/")!=string::npos)
	{
		current_url.erase(current_url.rfind("/"),10000);	
	}
	while(fin.getline(current_str,100000))
	{
		str=current_str;
		if(str.find("<a ")==string::npos)continue;
		int found=str.find("<a ");
		int i;
		while(found!=string::npos)
		{
			str[found]='x';
			char temp_url[10000];
			int flag=1,t=0;
			while(str.find("href=")<found)
			str[str.find("href=")]='x';
			for(i=str.find("href=");i<=10000;i++)
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
				if(temp_url_str.find("info.ruc")==string::npos)
				{
					found=str.find("<a ");
					continue;
				}
				else
				{
					temp_url_str=temp_url_str.erase(0,temp_url_str.find("info.ruc"));
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

int main()
{	
	my_queue.push("info.ruc.edu.cn");
	my_set.insert("info.ruc.edu.cn");
	int ans;
	while(!my_queue.empty())
	{	
		if(my_queue.front().find("user")==string::npos)
		if(my_queue.front().find(".do")==string::npos)
		if(my_queue.front().find(".xl")==string::npos)
		if(my_queue.front().find(".pdf")==string::npos)
		{
			cout<<ans<<endl<<my_queue.front()<<endl;
			ans++;	
			open_web_page(my_queue.front());
			find_url(my_queue.front());
		}
		my_queue.pop();
	}
	cout<<ans;
	return 0;
}
