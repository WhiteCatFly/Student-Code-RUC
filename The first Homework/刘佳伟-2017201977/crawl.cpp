//<a href=

#include "crawl.h"

queue <string> Q;

void bfs(string root, int PagesLimit)
{
	int tj = 0;
	vector <string> href;
	string F;

	set_root(root);
	Q.push(root);
	
	while(!Q.empty() && PagesLimit > 0)
	{
		F = Q.front();
		Q.pop();
		
		if(get_html(F) == 0)
		{
			PagesLimit--;
			tj ++;
		
			href = search_html(F);
			for(int i = 0; i < href.size(); i++)
				Q.push(href[i]);
		}
			
		cerr << "*********Up to Now " << tj << " / " << num_of_found_html() <<endl;
	}
}

int main()
{
	string root = "info.ruc.edu.cn", para;
	int limit = 0;
	
	cin >> limit;
	
	bfs(root, (limit == 0 ? 2100000000 : limit));
	
	return 0;
}
