#include <bits/stdc++.h>

#include "parser.h"

using namespace std;

int main(){
    Parser *parser = new Parser("test.html", Parser :: FROM_FILE);
    for (const auto &title : parser -> GetLinks()){
        cout << title << endl;
    }
    return 0;
}