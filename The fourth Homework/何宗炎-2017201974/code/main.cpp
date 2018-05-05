#include "Parser.h"
#include "global_setting.cpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	Parser Test("test.html");
	Test.ShowBody(Title | Text);
	return 0;
}
