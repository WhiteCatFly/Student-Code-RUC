#include <set>
#include <string>

#include "set.h"

using namespace std;

bool IfMulti(const string &str)
{
	static set<pair<ULL, ULL> > hash_set;	
	int str_l = str.length();
	ULL hs = 0, hs2 = 0;
	for(int i = 0;i < str_l; ++i) hs = hs * SEED + (ULL)str[i], hs2 = hs2 * SEED2 + (ULL)str[i];
	if(hash_set.find(mk_pr(hs, hs2)) != hash_set.end()) return 1;
	else return hash_set.insert(mk_pr(hs, hs2)), 0;
}
