#include <iostream>
#include "Reporterr.h"

void Report_file_open_err(const char * filename)
{
	cerr << "Error : file " << filename << " failed to open!" << endl;
	exit(1);
}

void Report_option_err(const char * opt)
{
	cerr << "Error : option " << opt << " not found!" << endl;
	exit(1);
}

void Report_option_err(const char opt)
{
	cerr << "Error : option " << opt << " not found!" << endl;
	exit(1);
}

void Report_err()
{
	cerr << "Error : Wrong command format!" << endl;
	exit(1);
}