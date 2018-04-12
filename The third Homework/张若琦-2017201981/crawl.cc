#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <set>
#include "crawl.h"
#include "ExtractURL.h"
#include "DisposeStr.h"

std :: queue <string> url_que;
std :: set <string> url_set;

void crawl(const string & root_url)
{
	int cnt = 0;
	char order[MAXN] = {0},now_file[MAXN] = {0};

	url_que.push(root_url);
	url_set.insert(root_url);

	FILE* list_fp = fopen("list.txt","a+");

	while (!url_que.empty())
	{
		string now_url = url_que.front();
		url_que.pop();
		strcpy(now_file,now_url.c_str());

		cnt ++;
		//cout << now_url << endl;
		printf("%s\n",now_url.c_str());

		sprintf(order,"wget -q \"%s\" -O tmp",now_file);
		if (system(order)) // error
		{
			continue;
		}

		string str_file;
		Getfile_and_ExtractURL(root_url,now_url,str_file); // fetch each URL in the current page
 
		fprintf(list_fp,"%4d %s\n",cnt,now_url.c_str());

		if (now_url.find(".php") != string :: npos)
			sprintf(now_file,"%d.php",cnt);
		else
			sprintf(now_file,"%d.html",cnt);

		FILE* fp = fopen(now_file,"w");
		fprintf(fp,"%s",str_file.c_str());
		fclose(fp);

		Delay();
	}
	printf("total : %d\n",cnt);
	fclose(list_fp);
}