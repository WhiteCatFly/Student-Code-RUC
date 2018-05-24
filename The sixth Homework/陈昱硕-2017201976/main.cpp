#include "my_string.h"
#include "number_string.h"

#include <iostream>

using namespace std;

int main(){
    NumberString number;
    MyString fmt;
    cin >> number >> fmt;
    MyString result = number.FormatOutput(fmt.c_str());
    cout << "'" << result << "'" << endl;
    return 0;
}
