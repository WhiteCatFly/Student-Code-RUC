#include <iostream>
#include "parser.h"
#include "standardize.h"

using std::string;
using std::stringstream;

int main()
{
	const string  page = "http://info.ruc.edu.cn";
	Parser tmp (page);
	tmp.get_url();
	tmp.get_title();
	tmp.get_text();
	tmp.get_tag("div");
}
