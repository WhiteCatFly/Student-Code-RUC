#include "crawl_gethtml.h"

using namespace std;

inline int command(string order, const string &para)
{
	order += " " + para;
	return system(order.c_str());
}

int get_html(const string &url)
{
	string filename = "'", wgetUrl = " '";
	
	usleep(50000);
	command("mkdir -p", UrlToDirectory(url));
	//cout<<url<<endl<<UrlToDirectory(url)<<endl;;
	filename += ((UrlToDirectory(url) == "") ? "" : (UrlToDirectory(url) + "/"));
	filename += UrlToFile(url);
	filename += "'";
	wgetUrl += url;
	wgetUrl += "'";
	
	//cout<<filename<<endl<<endl;
	filename += wgetUrl;
	return command("wget --tries=3 -O", filename); 
}

void set_root(const string &url)
{
	exist.insert(url);
}

int num_of_found_html()
{
	return exist.size();
}

void search_html(const string &fatherUrl, vector <string> &result)
{
	string content = "", line = "", filename = ((UrlToDirectory(fatherUrl) == "") ? "" : (UrlToDirectory(fatherUrl) + "/")), url;
	int HrefPos = 0, HrefEndPos;
	
	result.clear();
	filename += UrlToFile(fatherUrl);
	//cerr<<filename<<endl;
	
	ifstream fin(filename.c_str());
	
	while(getline(fin, line))
		content += line;
	
	
	while((HrefPos = content.find("<a href=", HrefPos)) != -1)
	{
		//cerr<<HrefPos<<endl;
		HrefPos += 8;
		HrefEndPos = content.find(content[HrefPos], HrefPos + 1);
		HrefPos++;
		//cerr<<HrefEndPos<<endl<<endl;
		url = UrlProcess(fatherUrl,content.substr(HrefPos, HrefEndPos - HrefPos));
		if(url != "" && url.find(RangeKey, 0) != -1)
		{
			if(!exist.count(url))
			{
				exist.insert(url);
				result.push_back(url);
			}
		}
		HrefPos = HrefEndPos + 1;
	}
	
}
