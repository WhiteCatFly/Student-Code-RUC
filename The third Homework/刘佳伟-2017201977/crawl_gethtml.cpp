#include "crawl_gethtml.h"

using namespace std;

int HTML::command(string order, string &para)
{
	order += " " + para;
	return system(order.c_str());
}

HTML::HTML(const URL &url)
{
	MyUrl = url;	
	cerr << MyUrl.GetUrl() << endl;
	string filename = "'", wgetUrl = " '", directorypath = MyUrl.UrlToDirectory();	
	
	Content = "";
	HrefPos = 0;
	Success = false;
	FilePath = "";
	
	usleep(50000);
	command("mkdir -p", directorypath);
	//cout<<url<<endl<<UrlToDirectory(url)<<endl;;
	FilePath += ((directorypath == "") ? "" : (directorypath + "/"));
	FilePath += MyUrl.UrlToFile();
	filename += FilePath + "'";
	
	wgetUrl += MyUrl.GetUrl();
	wgetUrl += "'";
	
	//cout<<filename<<endl<<endl;
	filename += wgetUrl;
	Success = (command("wget --tries=3 -O", filename) == 0);
}

bool HTML::DownloadSucceed()
{
	return Success;
}

bool HTML::ReadFromFile()
{
	try
	{
		string line;
		ifstream fin(FilePath.c_str());
		
		while(getline(fin, line))
			Content += line;
		
		fin.close();
		return true;
	}
	catch(...)
	{
		return false;
	}
}

URL HTML::GetNextHref()
{	
	int HrefEndPos;
	
	if((HrefPos = Content.find(HREF, HrefPos)) != string::npos)
	{
		//cerr<<HrefPos<<endl;
		HrefPos += href_Len;
		HrefEndPos = Content.find(Content[HrefPos], HrefPos + 1);
		HrefPos++;
		URL result(MyUrl.GetUrl(), Content.substr(HrefPos, HrefEndPos - HrefPos));
		//cerr<<HrefEndPos<<endl<<endl;
		HrefPos = HrefEndPos + 1;
		
		return result;
	}
	
	return URL(HTMLEND);
}
