#include "my_string.h"

#include <iostream>

using namespace std;

void callme1(MyString &);
void callme2(MyString);

int main(){
    {
        cout << "Start an inner block.\n";
        MyString headline1("Celery Stalks at Midnight");
        MyString headline2("Lettuce Prey");
        MyString sports("Spinach Leaves Bowl for Dollars");
        cout << "headline1: " << headline1 << endl;
        cout << "headline2: " << headline2 << endl;
        cout << "sports: " << sports << endl;
        callme1(headline1);
        cout << "headline1: " << headline1 << endl;
        callme2(headline2);
        cout << "headline2: " << headline2 << endl;
        cout << "Initialize one object to another:\n";
        MyString sailor = sports;
        cout << "sailor: " << sailor << endl;
        cout << "Assign one object to another:\n";
        MyString knot;
        knot = headline1;
        cout << "knot: " << knot << endl;
        cout << "Exiting the block.\n";
    }
    cout << MyString :: howmany() << endl;
    cout << "End of main()\n";
    return 0;
}

void callme1(MyString &rsb){
    cout << "String passed by reference:\n";
    cout << "    \"" << rsb << "\"\n";
}

void callme2(MyString sb){
    cout << "String passed by value:\n";
    cout << "    \"" << sb << "\"\n";
}