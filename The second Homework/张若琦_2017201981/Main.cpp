#include <string>
#include <iostream>
#include "crawl.h"
#include "clean.h"

int main(int argc,char * argv[])
{
	string root_url = argv[1];
	if (root_url == "clean")
		clean();
	else
		crawl(root_url);
	
	return 0;
}