#include "htmlparser.h"
using namespace std;

static Tag* dfs(const Tag* ct, const string& str)
{
	Tag* res = NULL;
	if(str == ct -> name) return (Tag*)ct;
	Tag* p = ct -> son();
	while(p != NULL && p -> next() != NULL) p = p -> next();
	for(;p != NULL;p = p -> prev())
	{
		res = dfs(p, str);
		if(res != NULL) return res;
	}
	return res;
}

static void dfs(const Tag* ct, const string& str, vector<Tag>& vec)
{
	if(str == ct -> name) vec.push_back(*ct);
	Tag* p = ct -> son();
	while(p != NULL && p -> next() != NULL) p = p -> next();
	for(;p != NULL;p = p -> prev())	
		dfs(p, str, vec);
}

Tag Tag::find(const string& str) const
{
	const Tag* res = dfs(this, str);
	if(res != NULL) return *res;
	else return nul_tag;
}

vector<Tag> Tag::find_all(const string& str) const
{
	vector<Tag> tag_vec;
	tag_vec.clear();
	dfs(this, str, tag_vec);
	return tag_vec;
}
