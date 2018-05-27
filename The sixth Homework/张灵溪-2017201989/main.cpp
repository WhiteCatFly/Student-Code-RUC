#include <cstring>
#include <iostream>
#include "digit.h"
using std::cout;
using std::endl;
int main(void){
	digit c1("+453", "% d");
	cout<<c1.str_()<<endl;
	digit c2("-453.678","%5.1f");
	cout<<c2.str_()<<endl;
	digit c3("453","%#.0f");
	cout<<c3.str_()<<endl;
	return 0;
}
