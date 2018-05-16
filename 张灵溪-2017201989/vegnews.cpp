#include <iostream>
#include "stringbad.h"
using namespace std;
void callme1(stringbad& rsb){
	cout<<"string passed by reference:   \""<<rsb<<"\"\n";
}
void callme2(stringbad sb){
	cout<<"string passed by value:   \""<<sb<<"\"\n";
}
int main(void){
	{	
		cout<<"Starting an inner block.\n";
		stringbad headline1("Celery Stalks at Midnight");
		stringbad headline2("Lettuce Prey");
		stringbad sports("Spinach Leaves Bowl for Dollars");
		cout<<"headline1: "<<headline1<<endl;
		cout<<"headline2: "<<headline2<<endl;
		cout<<"sports: "<<sports<<endl;
		callme1(headline1);
		cout<<"headline1: "<<headline1<<endl;
		callme2(headline2);
		cout<<"headline2: "<<headline2<<endl;
		cout<<"Initialize one object to another:\n";
		stringbad sailor=sports;
		cout<<"Sailor: "<<sailor<<endl;
		cout<<"Assign one object to another:\n";
		stringbad knot;
		knot=headline1;
		cout<<"Knot: "<<knot<<endl;
		cout<<"Exiting the block.\n";
	}
	cout<<"End of main()\n";
	return 0;
}
