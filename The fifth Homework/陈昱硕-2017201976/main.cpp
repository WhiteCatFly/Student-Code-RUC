#include "my_string.h"

#include <iostream>

using namespace std;

int main(){
    MyString a("hello ");
    MyString b("world!");
    cout << a + b << endl;
    cout << (a < b) << endl;
    return 0;
}