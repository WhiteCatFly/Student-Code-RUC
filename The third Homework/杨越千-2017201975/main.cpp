#include "spider.h"

using namespace std;

int main(int argc, char** argv)
{
	Spider spi;
	string url, dom;//domain name
	int num = 0;
	if(argc > 1) url = argv[1];
	if(argc > 2) dom = argv[2];
	if(argc > 3) sscanf(argv[3], "%d", &num);
	printf("%s\n", spi.ask_index().c_str());
	spi.set_index("index.php");
	printf("%s\n", spi.ask_index().c_str());
	spi.set_index("index.html");
	if(argc <= 1) spi.run();
	else if(argc <= 2) spi.run(url);
	else if(argc <= 3) spi.run(url, dom);
	else spi.run(url, dom, num);
	spi.clear();
	
	return 0;
}
