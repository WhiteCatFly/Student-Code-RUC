#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <algorithm>

#include "spider.h"

using namespace std;

void Spider::Bfs(string root, string dom, int sleep_time)
{
	string s;
	queue<string> bfs_Q;
	while(!bfs_Q.empty()) bfs_Q.pop();
	bfs_Q.push(root);
	char cmd[cmd_maxlen], dir[cmd_maxlen];
	char str[string_maxlen];
	memset(cmd, 0, sizeof(cmd)), memset(dir, 0, sizeof(dir)), memset(str, 0, sizeof(str));
	string url, s0, res[string_maxnum];
	int res_sum = 0, url_tot = 0, dir_len = 0;
	FILE* f;
	while(!bfs_Q.empty())
	{
		url = bfs_Q.front(), bfs_Q.pop(), url_tot++;
		cout<< url_tot << " " << url << endl;
		memset(dir, 0, sizeof(dir));
		memset(cmd, 0, sizeof(cmd));
		ModifyUrl(url);
		FindRoot(url, root);
		
		FindDir(url, dir);
		dir_len = strlen(dir);
		if(dir[dir_len - 1] == '/') sprintf(dir + dir_len, "%s", this->index.c_str());
		sprintf(cmd, "wget -q -O '%s' '%s' -T 10 -t 2", dir, url.c_str());
		system(cmd);
		if(url_tot % 10 == 0) usleep(sleep_time);
		
		if((f = fopen(dir, "r")) == NULL) continue;
		#ifdef DEBUG
		int deb = 0;
		#endif
		while(fgets(str, string_maxlen, f) != NULL)
		{
			#ifdef DEBUG
			deb++;
			#endif
			s0 = str;
			res_sum = FindUrl(s0, dom, root, res);
			for(int i = 0;i < res_sum;++i)
				if(!IfMulti(res[i]))
				{
					bfs_Q.push(res[i]);
					//cout << ++num << " " << res[i] << endl; //log
				}
		}
		fclose(f);
	}
	
}
