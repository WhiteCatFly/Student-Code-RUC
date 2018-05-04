#ifndef Reporterr_H_
#define Reporterr_H_

using std :: endl;
using std :: cerr;

void Report_file_open_err(const char * filename);
void Report_option_err(const char * opt);
void Report_option_err(const char opt);
void Report_err();

#endif // Reporterr_H_