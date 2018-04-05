#include <string>
#include <cstdlib>
#include <sstream>
#include "crawler.h"

void download(const std::string & cur_url, int cnt) {
	std::string command = "wget -O ";
	std::ostringstream sout(std::ios_base::app);
	sout << cnt << " ";
	command += sout.str() + cur_url;
	system(command.c_str());
//	std::string filename = cur_url + ".html";
//	command = "mv index.html " + filename;
//	system(command.c_str());
}
