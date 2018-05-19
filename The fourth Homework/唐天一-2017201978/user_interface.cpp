#ifndef HTMLParser
#define HTMLParser
#include "HTMLParser.h"
#endif

void HTML::user_interface() const{
	cout << endl;
	cout << "1: get title" << endl;
	cout << "2: get urls" << endl;
	cout << "3: get main texts" << endl;
	cout << "4: get pictures" << endl;
	cout << "5: get files about certain type" << endl;
	cout << "6: get tree stucture" << endl;
	cout << "7: exit" << endl;
	cout << "Please enter you option:" << endl;
	
	int opt;
	cin >> opt;
	cout << endl;
	switch (opt){
		case 1:{
			get_title();
			continue_interface();
			break;
		}
		case 2:{
			get_url();
			continue_interface();
			break;
		}
		case 3:{
			get_main_text();
			continue_interface();
			break;
		}
		case 4:{
			get_img();
			continue_interface();
			break;
		}
		case 5:{
			cout << "Please enter the type you want to get:" << endl;
			string type;
			cin >> type;
			cout << endl;
			get_certain_pattern(type);
			continue_interface();
			break;
		}
		case 6:{
			get_tree_structure();
			continue_interface();
			break;
		}
		case 7:{
			exit(0);
		}
	}
}

void HTML::continue_interface() const{
	cout << endl;
	cout << "1: back to previous menu" << endl;
	cout << "2: exit" << endl;
	cout << "Please enter you option:" << endl;
	
	int opt;
	cin >> opt;
	cout << endl;
	if (opt == 1)
		user_interface();
}

