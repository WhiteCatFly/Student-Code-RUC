#ifndef SE_H
#define SE_H
#include<iostream>
#include<map>
#include<fstream>
#include<utility>
#include<math.h>
#include<string>
#include"segment_dll.h"

using namespace std;






class Rucsearch{
	private:
		map < string , int > query ;
		map < string , double > score ;
		map < string , double > length ;
		map <string , map<string,double> > elect;
	public:
		void search_score();
		void topk(int k);
		void input_form();
		void query_cut(string question);
};
#endif
