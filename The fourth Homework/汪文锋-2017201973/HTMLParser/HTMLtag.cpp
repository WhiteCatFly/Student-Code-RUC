#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include"HTMLtag.h"
using namespace std;
nature::nature() { tag = ""; text = ""; }
nature::nature(string tag_, string text_) { tag = tag_; text = text_; }
nature::~nature() {}
Htag::Htag() { tag = ""; }
Htag::Htag(string tag_) { tag = tag_;}
Htag::~Htag() {}
