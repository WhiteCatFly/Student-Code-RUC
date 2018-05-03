#include "htmlparser.h"
#include "consts.h"
using namespace std;

int main()
{
	ifstream ifile("htmlparser.in");
	string html, url;
	string s, temp;
	int mode = 0;
	ifile >> html >> url >> mode;
	//string html = "academic_faculty.php", url = "http://info.ruc.edu.cn";
	//string html = "codeforces.html", url = "http://codeforces.com";
	if(mode)
	{
		ifstream sfile(html);
		while(!sfile.eof())
		{
			getline(sfile, temp);
			s += temp + "\n";
		}
		sfile.close();
		HtmlParser test(s, url, 1);
		cout << "title: " << test.title() << endl;
		cout << "links: " << test.links("link") << endl;
		cout << "images: " << test.images("image") << endl;
		cout << "sounds: " << test.sounds("sound") << endl;
		cout << "words: " << test.words("word") << endl;				
	}
	else
	{
		HtmlParser test(html, url, 0);
		cout << "title: " << test.title() << endl;
		cout << "links: " << test.links("link") << endl;
		cout << "images: " << test.images("image") << endl;
		cout << "sounds: " << test.sounds("sound") << endl;
		cout << "words: " << test.words("word") << endl;		
	}	
	
	ifile.close();
	/*
	Tag tg = test.find("script");
	cout << "find(): ";
	if(tg != nul_tag)
	{
		for(auto i = tg.attrs.begin(); i != tg.attrs.end(); ++i) cout << i -> first << "=" << i -> second << " ";
	}
	cout << endl;
	vector<Tag> vtg = test.find_all("div");
	cout << "find_all(): " << endl;
	if(vtg.size())
	{
		for(int j = 0; j < min(3, (int)vtg.size()); ++j)
		{
			for(auto i = vtg[j].attrs.begin(); i != vtg[j].attrs.end(); ++i) cout << i -> first << "=" << i -> second << " ";
			cout << endl;
		}
	}
	*/

	return 0;
}
