#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "goodstring.h"
using namespace std;

void gprint(const GoodString& s)
{
	cout << s << endl;
}

int main()
{
	string m1("string1");
	char m2[10] = {"string2"};
	GoodString s1(m1), s2(m2);
	printf("initialize s1 & s2;\n");
	printf("s1: ");
	gprint(s1);
	printf("s2: ");
	gprint(s2);
	printf("\ns1_length: ");
	cout << s1.length() << endl;
	printf("\nedit s1:\n");
	s1[6] = '0';
	printf("s1: ");
	gprint(s1);
	printf("\nedit s1 back:\n");
	s1[6] = '1';
	printf("s1: ");
	gprint(s1);
		
	{
		printf("\ninitialize s3 with s1;\n");
		GoodString s3(s1);
		printf("s3: ");
		gprint(s3);
		printf("\ndestroy s3;\n");
	}
	printf("s1: ");
	gprint(s1);
	
	{
		printf("\ncopy s4 with s1;\n");
		GoodString s4;
		s4 = s1;
		printf("s4: ");
		gprint(s4);
		printf("\ncopy s4 with s2;\n");
		s4 = s2;
		printf("s4: ");
		gprint(s4);		
		printf("\ndestroy s4;\n");		
	}
	printf("s1: ");
	gprint(s1);
	printf("s2: ");
	gprint(s2);
	
	printf("exit.\n");
	getchar();
	return 0;
}
