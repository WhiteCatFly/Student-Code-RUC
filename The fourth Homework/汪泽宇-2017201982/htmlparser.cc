#include <cctype>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <regex>
#include "htmlparser.hpp"

using std::string;
using std::ifstream;
using std::ostringstream;
using std::cout;
using std::endl;
using std::set;
using std::regex;

void HTMLParser::build(Node *&t, const string & html, size_t & p) {
	if((p = html.find('<', p))
		== string::npos) return;
	while(html[p + 1] == '!') p = html.find('<', p + 1);
	t = new Node(null);
	size_t np = html.find_first_of('>' + blankstr, p);
	t->type = html.substr(p + 1, np - p - 1);
//		cout << '<' << t->type << endl;
	if(t->type == "script") {
		p = html.find("</script", p) + 1;
		return;
	}
	if(isspace(html[np])) np = html.find_first_not_of(blankstr, np);
	Node * cp;
	while(html[np] != '>' && html[np] != '/') {
		cp = new Node(null);
		p = np;
		np = html.find_first_of("= ", p);
		cp->type = html.substr(p, np - p);
//			cout << cp->type << endl;
		p = html.find('"', np) + 1;
		np = html.find('"', p);
		cp->key = html.substr(p, np - p);
		np = html.find_first_not_of(blankstr, np + 1);
		cp->sib = t->c[1];
		t->c[1] = cp;
	}
	p = html.find('>', np) + 1;
	if(voidele.find(t->type) != voidele.end()) return;
	while((p = html.find_first_not_of(blankstr, p)) != string::npos) {
		if(html[p] != '<') {
			cp = new Node(null);
			cp->type = "text";
			np = html.find('<', p);
			cp->key = html.substr(p, np - p);
			p = np;
			cp->sib = t->c[0];
			t->c[0] = cp;
		}
		else {
			if(html[p + 1] != '/') {
				build(cp, html, p);
				cp->sib = t->c[0];
				t->c[0] = cp;
				p = html.find('<', p);
			}
			else break;
		}
	}
	p = html.find('>', p) + 1;
}
void HTMLParser::select(Node *t, const string & type) const {
	if(t == null) return;
	if(t->type == type) {
		if(!t->key.empty()) cout << t->key << endl;
//			select(t->c[0], "text");
	}
	if(t->type != "script") select(t->c[0], type);
	select(t->c[1], type);
	select(t->sib, type);
}
void HTMLParser::Init(string & html) const {
	if(html[0] == -17) html.erase(0, 3);
}
void HTMLParser::reg_find_text(Node *t, const regex & reg) const {
	if(t == null) return;
	if(t->type == "text") {
		std::smatch res;
		string s = t->key;
		while(std::regex_search(s, res, reg)) {
			cout << *res.begin() << endl;
			s = res.suffix().str();
		}
	}
	reg_find_text(t->c[0], reg);
	reg_find_text(t->sib, reg);
}
