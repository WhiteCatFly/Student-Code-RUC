#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Parser.h"
#include "Reporterr.h"

void Parser :: write_file(const stringstream & istr, const string & file_name) const
{
	const char * filename = file_name.c_str();
	std :: ofstream outfile(filename);
	if (!outfile)
	{
		Report_file_open_err(filename);
		exit(1);
	}
	outfile << istr.rdbuf();
	outfile.close();
}

void Parser :: output_picture(const string & url, const string & file_name) const
{
	string command = "wget -q \"" + url + "\" -O " + file_name;
	system(command.c_str());
}

void Parser :: write_file(const string & output, const string & file_name) const
{
	const char * filename = file_name.c_str();
	std :: ofstream outfile(filename, std :: ios :: out | std :: ios :: binary);
	if (outfile)
	{
		outfile.write(&output[0], output.size());
		outfile.close();
	}
	else
		Report_file_open_err(filename);
}