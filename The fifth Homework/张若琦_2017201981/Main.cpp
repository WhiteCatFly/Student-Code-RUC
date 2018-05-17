#include <iostream>
#include "String.h"
using std :: cout;

void callme1(String &);
void callme2(String);

int main()
{
	/******************************************************
	// test 1 , from c++ primer plus
	
	using std :: endl;
	{
		cout << "Starting an inner block.\n";
		String headline1("headline1 www");
		String headline2("headline2 www");
		String sports("sports www");
		cout << "headline1: " << headline1 << endl;
		cout << "headline2: " << headline2 << endl;
		cout << "sports: " << sports << endl;
		callme1(headline1);
		cout << "headline1: " << headline1 << endl;
		callme2(headline2);
		cout << "headline2: " << headline2 << endl;
		cout << "Initialize one object to another:\n";
		String sailor = sports;
		cout << "sailor: " << sailor << endl;
		cout << "Assign one object to another:\n";
		String knot;
		knot = headline1;
		cout << "knot: " << knot << endl;
		cout << "Exiting the block.\n";
	}
	cout << "End of main()\n";
	
	******************************************************/

	//  test 2 , to test more function
	using std::cout;
	using std::endl;
	String a("hello world", 5);
	String b(a, 2, 2);
	String c(3, 'w');
	cout << a << ' ' << b << ' ' << c << endl;
	a += b + "qwq" + b;
	cout << a << endl;
	String aa = a;
	aa[6] = 'k';
	cout << aa << ' ' << (a > aa) << endl;
	swap(a, b);
	cout << a.size() << ' ' << b.c_str() << endl;
	b.erase(5, 2);
	cout << b << endl;
	b.insert(5, "tatat", 3);
	cout << b << ' ' << b.find("tat", 1) << endl;
	c.replace(1, 1, 1, 'q');
	cout << c << endl;
	c.replace(2, 1, c, 1, 1);
	cout << c << ' ' << c.substr(1,2) << endl;

	return 0;
}

void callme1(String & rsb)
{
	cout << "String passed by reference:\n";
	cout << "   \"" << rsb << "\"\n";
}

void callme2(String sb)
{
	cout << "String passed by value:\n";
	cout << "   \"" << sb << "\"\n";
}