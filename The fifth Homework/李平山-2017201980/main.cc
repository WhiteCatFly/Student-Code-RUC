#include <iostream>
#include <cstring>
#include <sstream>
#include "String.h"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

int main(int argc, char *argv[])
{		
	for(int i = 1; i < argc; i++)
	{
		std::stringstream s;
		s<<(*(argv+i));
		String tmp;
		s>>tmp;
		//String tmp(*(argv+i));
		cout<<tmp<<endl;
		//cout<<tmp.sum()<<endl;
		//cout<<*(argv+i)<<endl;
	}

}
