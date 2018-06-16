#include "query.h"

#include <cstdio>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "set_color.h"
#include "segment_dll.h"

using namespace std;

Query::Query(void *segmentor) : accurate_(false){
    SetColor(stderr, green);
    fprintf(stderr, "请输入关键字：");
    SetColor(stderr, white);
    string line;
    getline(cin, line);
    stringstream in(line);
    string term;
    while (in >> term){
        if (term == "+" || term == "-" || term == "&" || term == "|" || term == "^"){
            accurate_ = true;
            query_.push_back(vector<string>{term});
            continue;
        }
        vector<string> words;
        int len = segmentor_segment(segmentor, term, words);
        for (int i = 0; i < len; i ++){
            //stop words
        }
        query_.push_back(words);
    }
}