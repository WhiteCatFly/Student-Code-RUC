#ifndef HITS_H
#define HITS_H

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Hits{
	private:
	size_t rank;
	vector< pair<int, double> > res;
	
	public:
	Hits(int rk) : rank(rk){}
	void insert(pair<int, double>);
	void print();
	~Hits(){}
};

#endif
