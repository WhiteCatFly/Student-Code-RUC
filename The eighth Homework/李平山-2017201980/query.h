#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <math.h>
#include <cstring>
#include "include/thulac.h"

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

extern map< string, map< string, double > > chart;
class Query{
	private:
		int k;
		map < string , int > query ;
		map < string , double > score ;
		map < string , double > length ;
	public:
		Query() {};
		Query(int tmp) {k = tmp;}
		~Query() {};
		void init(); 
		void cal_score();
		void sort_k();
		void print(const vector<pair<string, string> > & res);
		friend bool cmp(const pair<string,double> &p1,const pair<string,double> &p2); 
};

#endif
