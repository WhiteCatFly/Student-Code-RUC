#include <string>
#include "crawl.h"
using namespace std;
int main(void){
	string root_url="http://info.ruc.edu.cn";
	crawl spider(root_url);
	spider.crawl_web();
	return 0;
}
