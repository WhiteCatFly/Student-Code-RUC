#include"HTMLParser.h"
#include"HTMLtype.h"
#include<sstream>
#include<string>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main()
{
	Parser a("<div class=\"link\"><a href=\"overview_contact.php\">AAAAAA </a>|<a href=\"mailto:rucinfo@ruc.edu.cn\"> BBBBBB </a>|<a href=\"en / index.php\"> English </a>|<a href=\"teacherlogin.html\"> CCCCCC </a></div>");
	a.getstruct();
	return 0;
}