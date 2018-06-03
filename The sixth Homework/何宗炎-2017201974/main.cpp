#include "MyNumString.h"
using namespace std;

int main() {
	freopen("test.out", "w", stdout);
	MyNumString s("998.245");
	s = s + "33";
	cout << s.Standard(0, 10, 2) << endl;
	cout << s.Standard(1, 10, 2) << endl;
	cout << s.Standard(0, 4, 4) << endl;
	return 0;
}
		
