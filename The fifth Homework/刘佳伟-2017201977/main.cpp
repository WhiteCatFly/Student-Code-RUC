#include "Mystring.h"

using namespace std;

void callme1(Mystring &);
void callme2(Mystring);

int main()
{
	cout << "Starting an inner block.\n";
	Mystring headline1("Celery Stalks at Midnight");
	Mystring headline2("Lettuce Prey");
	Mystring sports("Spinach Leaves Bowl for Dollars");
	cout << "headline1: " << headline1 << endl;
	cout << "headline2: " << headline2 << endl;
	cout << "sports: " << sports << endl;
	callme1(headline1);
	cout << "headline1: " << headline1 << endl;
	callme2(headline2);
	cout << "headline2: " << headline2 << endl;
	cout << "Initialize one object to another:\n";
	Mystring sailor = sports;
	cout << "sailor: " << sailor << endl;
	cout << "Assign one object to another:\n";
	Mystring knot;
	knot = headline1;
	cout << "knot: " << knot << endl;
	cout << "Exiting the block.\n";
	
	cout << "End of main()\n";
	return 0;
}

void callme1(Mystring &rsb)
{
	cout << "String passed by reference:\n";
	cout << "	\"" << rsb << "\"\n";
}

void callme2(Mystring sb)
{
	cout << "String passed by value:\n";
	cout << "	\"" << sb << "\"\n";
}
