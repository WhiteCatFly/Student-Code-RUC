#include "htmlparser.h"
using namespace std;

Tag HtmlParser::find(const string& str) const{return _root -> find(str); }

vector<Tag> HtmlParser::find_all(const string& str) const{return _root -> find_all(str); }
