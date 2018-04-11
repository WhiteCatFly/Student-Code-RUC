#ifndef url_2017201973
#define url_2017201973
#include<string>
#include<fstream>
#include<vector>
#include"WebCrawlerGlobal.h"
using std::string;
using std::ifstream;
using std::vector;
class url
{
	private:
		string host;
		string urlname;
		string allhtml;
		int number;
		string deltitle = string("-");
		string deltitle2 = string(" ");
		string findright = string("\"");
	public:
		WebCrawlerGlobal setting;
		url(string host_,string url_,int id);//构造函数
		string gethost();//获得网页的主机
		string geturl();//获得网页的网址
		void changehtml(string strhtml);//将网页内容传入allhtml
		ifstream downloadurl();//下载网址
		void getitle();//修改标题
		void getotherurl(vector<string> &vec);//获得当前地址下所有的链接,使用vector<string>存储所有的字符串
};
#endif