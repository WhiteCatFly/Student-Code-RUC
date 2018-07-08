#include <iostream>
#include <sstream>
#include <string>

#include "resource.h"
#include "enquiry.h"
#include "result.h"
#include "processor.h"
#include "structure.h"

using namespace std;

int getnum() {
	string line;
	int num;
	getline(cin,line);
	istringstream iss(line);
	iss >> num;
	return num;
}

int main(int argc, char ** argv) {
	const streambuf * default_buf = cout.rdbuf();
	string root_path = argument_processor(argc, argv);
	string enquiry;
	
	data_res resource;
	resource = resource_initialize(root_path);
	
	cerr << "请输入关键字:" << endl;
	getline(cin,enquiry);
	while (enquiry != "exit") {
		cerr << "请输入最多显示条数:" <<endl;
		int num = getnum();
		result * res;
		res = enquiry_processor(enquiry,resource);
		print_res(res, enquiry, resource, default_buf, num);
		delete[] res;
		cerr << "请输入关键字:" << endl;
		getline(cin,enquiry);
	}
}
