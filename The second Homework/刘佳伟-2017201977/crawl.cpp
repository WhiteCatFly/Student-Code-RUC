//<a href=

#include "crawl.h"

using namespace std;

void bfs(const string &root, const int &PagesLimit)
{
	int total = 0;
	vector <string> href;
	string F;

	set_root(root);
	Q.push(root);
	
	while(!Q.empty() && total < PagesLimit)
	{
		F = Q.front();
		Q.pop();
		
		if(get_html(F) == 0)
		{
			total ++;
		
			search_html(F, href);
			for(int i = 0; i < href.size(); i++)
				Q.push(href[i]);
		}
			
		cerr << "********************Process********************" << endl << "    Downloaded: " << total << endl << "    Detected: " << num_of_found_html() << endl << "    Target: " << PagesLimit << endl;
		cerr << "***********************************************" << endl << endl;
	}
}

int main()
{
	string StartUrl;
	int limit;

	cout << "Input the StartUrl: ";
	cin >> StartUrl;
	cout << "Input the RangeKey: ";
	cin >> RangeKey;
	cout << "Input the PagesLimit: ";
	cin >> limit;
	
	bfs(StartUrl, (limit == 0 ? 2100000000 : limit));
	
	return 0;
}
