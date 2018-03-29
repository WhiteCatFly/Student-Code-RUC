#include "craw.h"
#include "find_url.h"
#include <iostream>
#include <string.h>
#include <set>
#include <queue>

using std::string;

std::queue<string> Q;
std::set<string> visited;
const string url_root = "http://info.ruc.edu.cn";
const string pre_order = "wget -O tmp_url.html ";

void download_html(const string& current_url)
{
	string current_order = pre_order+current_url;
	system(current_order.c_str());	

}
void url_bfs(const string& root = url_root)
{
	static int cnt = 0;
	Q.push(root);
	while(!Q.empty())
	{
		
		string current_url = Q.front();
		Q.pop();
		download_html(current_url);
		//char char_cur[100];
		//strcpy(char_cur,cur.c_str());
		//system(cur.c_str());
		cnt++;
		std::cout<<cnt<<std::endl;
		read(current_url);
	}
}


