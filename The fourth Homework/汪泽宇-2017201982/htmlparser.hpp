#ifndef HTMLPARSER
#define HTMLPARSER

#include <cctype>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <regex>

using std::string;
using std::ifstream;
using std::ostringstream;
using std::cout;
using std::endl;
using std::set;
using std::regex;

class HTMLParser {
private:
	const static string blankstr;
	const static set<string> voidele;
	struct Node {
		string type, key;
		Node * c[2];
		// 0: element, 1: attribute
		Node * sib;
		Node() = default;
		Node(Node *p) {
			c[0] = c[1] = sib = p;
		}
	}*null, *root;
	void build(Node *&t, const string &, size_t &) ;
	void select(Node *t, const string & type) const ;
	void Init(string & html) const ;
	void reg_find_text(Node *t, const regex & reg) const ;
public:
	HTMLParser() {
		null = new Node();
		null->c[0] = null->c[1] = null->sib = null;
		root = null;
	}
	HTMLParser(string & html): HTMLParser() {
		size_t p = 0;
		Init(html);
		build(root, html, p);
	}
	HTMLParser(ifstream & fin): HTMLParser() {
		ostringstream sout;
		sout << fin.rdbuf();
		size_t p = 0;
		string html = sout.str();
		Init(html);
		build(root, html, p);
	}
	void select_title() const {
		cout << "-------------------title:" << endl;
		select(root, "title");
		cout << endl;
	}
	void select_text() const {
		cout << "-------------------text:" << endl;
		select(root, "text");
		cout << endl;
	}
	void select_href() const {
		cout << "-------------------href:" << endl;
		select(root, "href");
		cout << endl;
	}
	void select_regex(const string & reg) const {
		cout << "------------------- text match " << reg << endl;
		reg_find_text(root, regex(reg));
		cout << endl;
	}
};
const string HTMLParser::blankstr = " \n\t";
const set<string> HTMLParser::voidele = {"area", "base", "br", "col",
	"command", "embed", "hr", "img", "input", "keygen", "link", "meta",
	"param", "source", "track", "wbr"};

#endif

