#include "number_string.h"
#include <cstring>

using namespace std;

int main() {
	char * input = new char [max_number_len];
	char * format = new char [max_number_len];
	while (true) {
		cout << "please input a number: " <<endl;
		cin >> input;
		input = initialize(input);
		number_string number(input);
		cout << "please input a format:" << endl;
		cin>>format;
		cout << ":" << number.normalize(format) << ":" << endl;
	}
	delete[] input;
	delete[] format;
}
