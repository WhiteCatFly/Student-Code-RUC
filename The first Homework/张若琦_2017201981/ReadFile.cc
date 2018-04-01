#include <fstream>
#include <string>
#include "ReadFile.h"

string get_file(const char* filename)
{
	std :: ifstream infile(filename,std :: ios :: in | std :: ios :: binary);
	if (infile)
	{
		string ret;
		infile.seekg(0,std :: ios :: end);
		ret.resize(infile.tellg());
		infile.seekg(0,std :: ios :: beg);
		infile.read(&ret[0],ret.size());
		infile.close();
		return ret;
	}
}
