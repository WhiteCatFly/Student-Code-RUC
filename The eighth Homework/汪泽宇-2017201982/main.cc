#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include "include/thulac.h"
#include "search_engine.h"

using std::string;
using std::vector;
using std::pair;
using std::cin;

int main() {
	SE se;
	string qs;
	THULAC lac;
	lac.init(NULL, NULL, 1);

	while(getline(cin, qs)) {
		THULAC_result res;
		lac.cut(qs, res);
		vector<string> q;
		for(auto i = res.begin(); i != res.end(); i++) {
			q.push_back(i->first);
		}
		se.search(Doc(q));
	}
	return 0;
}
