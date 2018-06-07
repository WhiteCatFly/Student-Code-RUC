#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "include/thulac.h"

using std::string;
using std::vector;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

void print(const vector<pair<string, string> > & res) {
	for(auto i = res.begin(); i != res.end(); i++) {
		cout << i->first << i->second << endl;
	}
}

int main() {
	THULAC lac;
	lac.init();

	string s;
	THULAC_result res;
	freopen("lac.in", "r", stdin);
	cin >> s;
	lac.cut(s, res);
	freopen("lac.out", "w", stdout);
	print(res);
	return 0;
}
