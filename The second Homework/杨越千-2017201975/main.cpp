#include "main.h"

using namespace std;

int main(int argc, char** argv)
{
	string url, dom;//domain name
	if(argc > 1) url = argv[1];else url = def_url;
	if(argc > 2) dom = argv[2];else dom = def_dom;
	Bfs(url, dom);
	
	return 0;
}
