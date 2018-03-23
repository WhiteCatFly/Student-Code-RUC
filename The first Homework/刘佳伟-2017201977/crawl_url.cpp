#include "crawl.h"

//The Keyword List, Copyright CYS 2018
const char *forbidden_str[] = {"@", "#", "(", ")", "[", "]", "{", "}",
					".txt", ".doc", ".ppt", ".xls", ".pdf", ".PDF", "ftp://", "file://", "telnet://",
					".jpg", ".JPG", ".jpeg", ".JPEG", ".png", ".gif", ".bmp", ".rar", ".zip", ".7z", ".mp3", ".mp4", ".MP4",
					"javascript:void(0)", "javascript:;",
					".flv", ".wmv", ".avi", ".rmvb", ".mpeg", ".qt", ".mpg", ".mkv", ".rm",
					"twitter", "google", "facebook", "END_OF_FORBIDDEN_STRING"};

const char END_OFS[] = "END_OF_FORBIDDEN_STRING";

string UrlProcess(string FatherUrl, string url)
{
	vector < pair <string, string> > Var;
	int ProcessQuery = 0;
	string StdUrl = "", ProcessQueryUrl = "", VarName, VarValue;
	
	for(int i = 0; strcmp(forbidden_str[i], END_OFS) != 0; i++)
		if(url.find(forbidden_str[i]) != -1)
			return "";
			
	for(int i = 0; i < url.size(); i++)
		if(url[i] != ' ')
			StdUrl += url[i];
	url = StdUrl;
	StdUrl = "";
	if(url[url.size() - 1] == '/')
		url = url.substr(0, url.size() - 1);
	
	
//https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=baidu&wd=strcmp&oq=c%252B%252B%25E8%25B5%258B%25E5%2580%25BC%25E8%25BF%2594%25E5%259B%259E%25E5%2580%25BC&rsv_pq=b341a17400085990&rsv_t=327e80%2FmHVPA7qMXTctrlQGURtds7O7ZAA8GdcpGZPbkLOm3b9ftNEqgsYY&rqlang=cn&rsv_enter=1&inputT=671&rsv_sug3=126&rsv_sug1=94&rsv_sug7=100&rsv_sug2=0&rsv_sug4=1675
	while(ProcessQuery < url.size() && url.find('?', ProcessQuery) != -1)
	{		
		Var.clear();
		int i;
		VarName = ""; VarValue = "";
		ProcessQueryUrl += url.substr(ProcessQuery, url.find('?', ProcessQuery) - ProcessQuery);
		ProcessQuery = url.find('?', ProcessQuery);
	
		for(i = ProcessQuery + 1; url[i] != '='; i++)
			VarName += url[i];
		for(i++; i < url.size() && url[i] != '/' && url[i] != '&'; i++)
			VarValue += url[i];
		Var.push_back(make_pair(VarName, VarValue));
	
		while(url[i] == '&')
		{
			bool FoundVar = false;
			VarName = ""; VarValue = "";
			for(i++; url[i] != '='; i++)
				VarName += url[i];
			for(i++; i < url.size() && url[i] != '/' && url[i] != '&'; i++)
				VarValue += url[i];
			
			for(int j = 0; j < Var.size(); j++)
				if(Var[j].first == VarName)
				{
					FoundVar = true;
					Var[j].second = VarValue;
					break;
				}
			
			if(!FoundVar)
				Var.push_back(make_pair(VarName, VarValue));
		}
		 
		ProcessQueryUrl += '?';
		ProcessQueryUrl += Var[0].first;
		ProcessQueryUrl += '=';
		ProcessQueryUrl += Var[0].second;
		for(int j = 1; j < Var.size(); j++)
		{
			ProcessQueryUrl += '&';
			ProcessQueryUrl += Var[j].first;
			ProcessQueryUrl += '=';
			ProcessQueryUrl += Var[j].second;
		}
		ProcessQuery = i;
	}
	if(ProcessQuery < url.size())
		ProcessQueryUrl += url.substr(ProcessQuery, url.size() - ProcessQuery);
	
	
	if(url.find("http://") != -1)
		StdUrl = ProcessQueryUrl.substr(7, url.size() - 7);
	else if(url.find("https://") != -1)
		StdUrl = ProcessQueryUrl.substr(8, url.size() - 8);
	else if(url[0] != '/')
	{
		for(int i = 0; i < FatherUrl.size() && FatherUrl[i] != '/'; i++)
			StdUrl += FatherUrl[i];
		StdUrl += '/';
		StdUrl += ProcessQueryUrl;
	}
	else
	{
		int i;
		
		for(i = FatherUrl.size() - 1; i >= 0 && FatherUrl[i] != '/'; i--)
			;
		if(i < 0)
			i = FatherUrl.size() - 1;
		else
			i--;
			
		StdUrl += FatherUrl.substr(0, i + 1);
		StdUrl += ProcessQueryUrl;
	}
	
	return StdUrl;
}

string UrlToDirectory(string url)
{
	int i = url.size() - 1;
	
	for(; i >= 0 && url[i] != '/'; i--)
		;
	if(i < 0)
		i = 0;
		
	return url.substr(0, i);
}

string UrlToFile(string url)
{
	int i = url.size() - 1;
	
	for(; i >= 0 && url[i] != '/'; i--)
		;
	if(i < 0)
		i = 0;
	if(i > 0)
		i++;
		
	return url.substr(i, url.size() - i) + ".jrcrawl";
}
