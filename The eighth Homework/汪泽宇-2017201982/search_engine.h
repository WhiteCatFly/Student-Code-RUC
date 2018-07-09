#ifndef SEARCH_ENGINE_H_
#define SEARCH_ENGINE_H_

#include <map>
#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::map;
using std::string;
using std::pair;

typedef pair<string, double> psd;

class Doc {
private:
	/*vector<string> term;
	vector<int> tf;*/
	vector<pair<string, double> > term;
	int n;
	map<string, int> mp;
	string path;
public:
	Doc();
	Doc(const string &);
	Doc(const vector<string> &);
	psd & operator [] (int x) {
		return term[x];
	}
	const psd operator [] (int x) const {
		return term[x];
	}
	double & operator [] (const string & s) {
		return term[mp[s]].second;
	}
	const double operator [] (const string & s) const {
		return term[mp.at(s)].second;
	}
	const int N() const {
		return n;
	}
	const bool has (const string &s) const {
		return mp.find(s) != mp.end();
	}
	const string Path() const {
		return path;
	}
};

class SE {
private:
	const static int N = 6100;
	Doc d[N];
	map<string, int> mp;
	int dn, tn;
	vector<double> idf;

public:
	SE();
	void search(const Doc &, int k = 10) const;
};

#endif

