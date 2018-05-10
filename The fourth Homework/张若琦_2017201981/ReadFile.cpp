#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Parser.h"
#include "Reporterr.h"

string Parser :: get_file(const char * filename) const
{
	std :: ifstream infile(filename, std :: ios :: in | std :: ios :: binary);
	if (infile)
	{
		string ret;
		infile.seekg(0, std :: ios :: end);
		ret.resize(infile.tellg());
		infile.seekg(0, std :: ios :: beg);
		infile.read(&ret[0], ret.size());
		infile.close();
		return ret;
	}
	else
		Report_file_open_err(filename);
}

Parser :: Parser(const char * filename)
{
	htmlfile_ = get_file(filename);
}

Parser :: Parser(const string & url = "")
{ 
	url_ = url;
	if (url_[url_.size() - 1] != '/')
		url_.push_back('/');
	string command = "wget -q \"" + url_ + "\" -O tmp";
	system(command.c_str());

	htmlfile_ = get_file("tmp");
	system("rm tmp");
}
