#include "craw.h"
#include "find_url.h"
#include <iostream>

int main(int argc, char * argv[])
{
	std::string root = "http://info.ruc.edu.cn";
	url_bfs(root);
	return 0;
}
