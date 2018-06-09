#include "Numstring.h"
#include <string>

using namespace std;

string form;

int main()
{
	Numstring x;
	cin >> x;
	getline(cin, form);
	getline(cin, form);
	cout << x.Print(form.c_str()) << endl;	
}
