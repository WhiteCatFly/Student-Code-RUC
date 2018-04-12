#include <string>
#include <sstream>
#include "crawl.h"

const char *domain_name = "info.ruc.edu.cn";

int main(int argc, char **argv) {
	std::string seed_url;
	std::ostringstream sout;
	if(argc > 1) sout << argv[1];
	else sout << "info.ruc.edu.cn";
	seed_url = sout.str();

	crawl(seed_url);

	return 0;
}
