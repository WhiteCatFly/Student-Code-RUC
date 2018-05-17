#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<regex>
#include"HTMLParser.h"
#include"HTMLTree.h"
#include"HTMLtag.h"
const int N = 256;
const int M = 200051;
using namespace std;
Parser::Parser() { page = ""; }
Parser::Parser(fstream &File) { char buffer[N]; while (!File.eof()) { File.getline(buffer, N - 1); page += buffer; } }
Parser::Parser(stringstream &Str) { Str >> page;  }
Parser::Parser(string Str) { page = Str; }
Parser::~Parser() {}
string Parser::getag(string text)
{
	regex patterndel("((<[0-9a-zA-Z]+(>| ))|(/[0-9a-zA-Z]*>))");
	smatch titlematch;
	string::const_iterator text_iter = text.begin();
	string::const_iterator text_iterend = text.end();
	regex_search(text_iter, text_iterend, titlematch, patterndel);
	string tag = titlematch[0];
	regex delorder("<|>| ");
	tag = regex_replace(tag, delorder, string(""));
	return tag;
}
void Parser::getnature(string text,Tree *now)
{
	regex findequal("[0-9a-zA-Z]+?(?==\")");
	regex findouble("\".*?\"");
	regex deldouble("\"");
	string Snature,Snature2;
	smatch naturematch;
	smatch naturematch2;
	string::const_iterator nature_iter = text.begin();
	string::const_iterator nature_iterend = text.end();
	string::const_iterator nature_iter2 = text.begin();
	string::const_iterator nature_iterend2 = text.end();
	while (regex_search(nature_iter, nature_iterend, naturematch, findequal))
	{
		Snature = naturematch[0];
		nature_iter = naturematch[0].second;
		regex_search(nature_iter2, nature_iterend2, naturematch2, findouble);
		Snature2 = naturematch2[0];
		nature_iter2 = naturematch2[0].second;
		Snature2 = regex_replace(Snature2, deldouble, string(""));
		nature t(Snature,Snature2);
		now->value.Hclass.push_back(t);
	}
}
void Parser::getext(string text, Tree *now)
{
	regex patterntext(">.+?<");
	regex patterndel("<|>| ");
	string Snature;
	smatch naturematch;
	string::const_iterator nature_iter = text.begin();
	string::const_iterator nature_iterend = text.end();
	regex_search(nature_iter, nature_iterend, naturematch, patterntext);
	Snature = naturematch[0];
	nature_iter = naturematch[0].second;
	Snature = regex_replace(Snature, patterndel, string(""));
	now->value.text += Snature;
}
void Parser::dfs_tag(string type,Tree* root)
{
	int len = root->value.Hclass.size();
	for (int i = 0; i < len; i++)
		if (root->value.Hclass[i].tag == type)
			cout << "URL is:" << root->value.Hclass[i].text << endl;
	for (int i = 0; i < root->child.size(); i++)
		dfs_tag(type, root->child[i]);
}
void Parser::dfs_suffix(string type, Tree* root)
{
	regex patternsuffix(".+\." + type);
	int len = root->value.Hclass.size();
	for (int i = 0; i < len; i++)
	{
		//cout << regex_search(root->value.Hclass[i].text, patternsuffix) << " " << root->value.Hclass[i].text << endl;
		if (regex_search(root->value.Hclass[i].text, patternsuffix))
			cout << type << " is " << root->value.Hclass[i].text << endl;
	}
	for (int i = 0; i < root->child.size(); i++)
		dfs_suffix(type, root->child[i]);
}
void Parser::getstruct()
{
	regex patternleft("<[0-9a-zA-Z]+(>| )");
	regex patternright("/[0-9a-zA-Z]*>");
	regex patternnext(".*?((<[0-9a-zA-Z]+(>| ))|(/[0-9a-zA-Z]*>))");
	regex patterndel("((<[0-9a-zA-Z]+(>| ))|(/[0-9a-zA-Z]*>))");
	string title;
	string text;
	smatch pagematch;
	string::const_iterator page_iter = page.begin();
	string::const_iterator page_iterend = page.end();
	Tree* now=new Tree;
	while (regex_search(page_iter, page_iterend, pagematch, patternnext))
	{
		title = pagematch[0];
		text = regex_replace(title, patterndel, string(""));
		getnature(text,now);
		getext(text, now);
		string tag = getag(title);
		if (tag.find("/") != string::npos)
			now = now->father;
		else
		{
			Tree* newT = new Tree;
			newT->value = Htag(tag);
			newT->father = now;
			now->child.push_back(newT);
			now = newT;
		}
		page_iter = pagematch[0].second;
	}
	dfs_tag("href", now);
	dfs_suffix("php", now);
}