#include <iostream>
#include "MyString.h"
#include "Format_Print.h"

int main(int argc, char *argv[]){
	format_print tty(argv[1], argv[2]);
	std::cout << tty;
	return 0;
}
