#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include"HTMLTree.h"
using namespace std;
Tree::Tree() { father = NULL; }
Tree::Tree(Htag tag) { value = tag; father = NULL; }
//Tree<T>::Tree(T tag, Tree<T>* father_) { value = tag; father = father_; }
Tree::~Tree() { }

