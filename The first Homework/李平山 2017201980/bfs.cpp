#include "craw.h"
#include <iostream>
#include <string.h>
#include <set>
#include <queue>
using namespace std;



queue<string> Q;
set<string> visited;

void bfs(string root = "http://info.ruc.edu.cn")
{
	static int cnt = 0;
	Q.push(root);
	while(!Q.empty())
	{
		
		string curr = Q.front();
		Q.pop();
		string pre = "wget -O tmp_url.html ";
		string cur = pre+curr;		
		//char char_cur[100];
		//strcpy(char_cur,cur.c_str());
		system(cur.c_str());
		cnt++;
		cout<<cnt<<endl;
		read(curr);
	}
}


