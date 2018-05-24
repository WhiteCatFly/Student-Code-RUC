#include <iostream>
#include <cstring>
#include <sstream>
#include "String.h"
#include "Stringout.h"
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

int main(int argc, char *argv[])
{	
	String format,content;
	if(argc)
	{
		std::stringstream s;
		s<<(*(argv+1));
		s>>format;
		std::stringstream ss;
		ss<<(*(argv+2));
		ss>>content;
	}
	else cin>>format>>content;
	Stringout std_out(format,content);
	cout<<std_out.display()<<std::endl;

}
