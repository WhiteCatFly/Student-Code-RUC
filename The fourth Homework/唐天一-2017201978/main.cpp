#ifndef HTMLParser
#define HTMLParser
#include "HTMLParser.h"
#endif

int main(){
	cout << "Please enter the website you need to parse. (You can enter html texts, a url or a file name.)" << endl;
	string website;
	cin >> website;
	HTML html(website);
	html.user_interface();
}

