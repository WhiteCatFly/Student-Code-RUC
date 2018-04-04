#include <cstdlib>
#include <string>
#include <sstream>
#include "download.h"

void download(const std::string & cur_url, int cnt) {
	std::string command = "cd files\nwget -O ";
	std::ostringstream sout(std::ios_base::app);
	sout << cnt << " ";
	command += sout.str() + cur_url;
	system(command.c_str());
//	std::string filename = cur_url + ".html";
//	command = "mv index.html " + filename;
//	system(command.c_str());
}
