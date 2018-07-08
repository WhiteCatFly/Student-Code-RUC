#include"document.h"
#include"index.h"
#include"score.h"
#include<cstdio>
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<utility>
#include<fstream>
#include<cstring>

using namespace std;

extern map<string,Dict> index_;
extern map<int,Doc> collection;

int main()
{
	string rootpath = "./data/file_list.txt";
	ifstream is(rootpath.c_str());
	string root = "./data/";
	string tmp_path;
	cout << "Loading..." << endl << "Please wait for a while" << endl;
	while(getline(is,tmp_path)) {
cout << "~~~~~~~~~~~~~~~~~~~" << endl;
		tmp_path = root + tmp_path.substr(2);
		add_collection(tmp_path.c_str());	
		//forget the stop word	
		
		add_index(tmp_path+".title",cnt_collection);
		add_index(tmp_path+".body",cnt_collection);
	}
cout << "?!!?!???!??!?!?!?!?!?!?" << endl; 		
	string query;
	int topmany;
	for(map<string,Dict>::iterator itr = index_.begin();
		itr != index_.end();
		itr++)
cout << itr->first << ' ';
	for(;;) {
		cout << "input the query correctly"
		" (tokenize,no stop words,end with newline)" << endl
		<< "input \"qqq\" to quit" << endl;
		getline(cin,query);
		if (query == "qqq") break;
		cout << "How many result do u want" << endl
		<< endl;
		cin >> topmany;
		cin.get();
		if (topmany == 0) break;
		answer(query,topmany);
	}
}

//input should be normalized which is tokenized and without stop words
