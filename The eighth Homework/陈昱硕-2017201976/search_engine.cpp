#include "search_engine.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "search_result.h"
#include "segment_dll.h"
#include "set_color.h"
#include "kbhit.h"

using namespace std;

void SearchEngine::LoadFile(const size_t idx, const string &file_name, Index &index){
    ifstream in(file_name.c_str());
    if (!in.is_open()){
        fprintf(stderr, "can't open %s !\n", file_name.c_str());
    }
    else{
        istream_iterator<string> iter(in), eof;
        index.append(idx, vector<string>(iter, eof));
    }
    in.close();
}

SearchEngine::SearchEngine(const string &file_list) :
    file_list_(file_list),
    segmentor_(segmentor_create_segmentor("/home/cys/ltp/ltp_data/cws.model"))
{
    ifstream fin(file_list_.c_str());
    if (!fin.is_open()){
        fprintf(stderr, "can't open file_list!\n");
        exit(1);
    }

    string doc;
    while (getline(fin, doc)){
        size_t idx = doc_list_.append(doc);
        LoadFile(idx, doc + ".title", title_index_);
        LoadFile(idx, doc + ".body", body_index_);
    }

    fin.close();
    /*fprintf(stderr, "title :\n");
    title_index_.display();

    fprintf(stderr, "body :\n");
    body_index_.display();*/

    /*auto vec = body_index_.tot_number();
    sort(vec.rbegin(), vec.rend());
    FILE *fp = fopen("terms.txt", "w");
    // for (size_t i = 0; i < 100; i ++)
        // fprintf(fp, "%s\n", vec[i].second.c_str());
    for (auto ele : vec)
        fprintf(fp, "times = %lu, term = %s\n", ele.first, ele.second.c_str());
    fclose(fp);*/
}

PostingList SearchEngine::BaseSearch(const std::vector<Words> &query, const Index &idx){
    PostingList post;
    FlagStatus flag = none;
    for (auto & term : query){
        if (term.size() == 1){
            if (term[0] == "+"){
                flag = plus_flag;
                continue;
            }
            else if (term[0] == "-"){
                flag = minus_flag;
                continue;
            }
            else if (term[0] == "&"){
                flag = and_flag;
                continue;
            }
            else if (term[0] == "|"){
                flag = or_flag;
                continue;
            }
            else if (term[0] == "^"){
                flag = xor_flag;
                continue;
            }
        }
        PostingList cur;
        bool isfirst = true;
        for (auto & word : term){
            if (isfirst){
                cur = idx[word];
                isfirst = false;
            }
            else
                cur.link(idx[word]);
        }
        switch (flag){
            case none:
                post |= cur;
                break;
            case plus_flag:
                post &= cur;
                break;
            case minus_flag:
                post -= cur;
                break;
            case and_flag:
                post &= cur;
                break;
            case or_flag:
                post |= cur;
                break;
            case xor_flag:
                post ^= cur;
                break;
        }
    }
    return post;
}

PostingList SearchEngine::AccurateSearch(const std::vector<Words> & query){
    return BaseSearch(query, title_index_) | BaseSearch(query, body_index_);
}

PostingList SearchEngine::RankedSearch(const std::vector<Words> & query){

}

SearchResult SearchEngine::Search(const Query &query, const size_t limits)
{
    // if (query.accurate())
        return SearchResult(AccurateSearch(query.query()), query, doc_list_, limits);
    // else
        // return SearchResult(RankedSearch(query.query()), query, doc_list_, limits);
}

void SearchEngine::Run(){
    ResetScreen(cerr);
    Query query(segmentor_);
    SetColor(cerr, green);
    cerr << "搜索结果显示条数：";
    SetColor(cerr, white);
    size_t limits = 10;
    string line;
    getline(cin, line);
    stringstream in(line);
    in >> limits;
    cerr << Search(query, limits) << endl;
    InitKeyboard();
    CheckKeyboard();
    CloseKeyboard();
}