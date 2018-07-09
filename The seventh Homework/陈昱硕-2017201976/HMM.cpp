#include "HMM.h"

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

class MyMap{
public:
    enum Status{ADDING, READING};

private:
    unordered_map<string, int> umap_;
    vector<string> vec_of_str_;
    int number_;
    Status stat_;

public:
    MyMap() : number_(0), stat_(ADDING){}
    void ChangeStat(Status stat){stat_ = stat;}
    int GetId(const string &str){
        auto res = umap_.find(str);
        if (res == umap_.end()){
            if (stat_ == ADDING){
                umap_.insert(make_pair(str, number_++));
                vec_of_str_.push_back(str);
                return number_;
            }
            else return -1;
        }
        else return res -> second;
    }
    int GetNumber(){return number_;}

    string operator [] (int idx){
        if (idx < 0)
            return string();
        return vec_of_str_[idx];
    }
};

static const int kMaxTags = 60;
static const int kMaxWords = 500000;
static const int kMaxLength = 50000;
static const double kInfinite = 1E300;

static MyMap map_of_tags, map_of_words;
static double initial[kMaxTags];
static double word_in_tag[kMaxWords][kMaxTags];
static double tag_to_tag[kMaxTags][kMaxTags];
static double P[kMaxLength][kMaxTags];
static int choise[kMaxLength][kMaxTags];
static int final_choise[kMaxLength];

static inline void GetTag(string &word, string &tag){
    size_t pos = word.find("/");
    tag = word.substr(pos + 1);
    word.erase(pos);
}

static void Read(const char *train_file){
    ifstream in(train_file);
    if (!in.is_open()){
        cerr << "wrong input file!" << endl;
        exit(1);
    }
    string line;
    while (getline(in, line)){
        istringstream is(line);
        string word, tag, block;
        int last_tag = -1, pre_tag = -1, block_tag = -1;
        enum BlockStat{out, in, end};
        BlockStat stat = out;
        while (is >> word){
            size_t pos;
            if ((pos = word.find("[")) != string::npos){
                stat = in;
                pre_tag = last_tag;
                word.erase(pos, 1);
                block.clear();
            }
            else if ((pos = word.find("]")) != string::npos){
                stat = end;
                tag = word.substr(pos + 1);
                block_tag = map_of_tags.GetId(tag);
                word.erase(pos);
            }

            GetTag(word, tag);
            int now_tag = map_of_tags.GetId(tag);
            int now_word = map_of_words.GetId(word);
            if (last_tag == -1)
                initial[now_tag] ++;
            else
                tag_to_tag[now_tag][last_tag] ++;
            word_in_tag[now_word][now_tag] ++;

            last_tag = now_tag;
            if (stat != out){
                block += word;
                if (stat == end){
                    int now_word = map_of_words.GetId(block);
                    if (pre_tag != -1)
                        tag_to_tag[block_tag][pre_tag] ++;
                    word_in_tag[now_word][block_tag] ++;
                    last_tag = block_tag;
                    stat = out;
                }
            }
        }
    }
    cerr << "tag number = " << map_of_tags.GetNumber()
        << " word number = " << map_of_words.GetNumber() << endl;
}

static void PreWork(){
    map_of_tags.ChangeStat(MyMap :: READING);
    map_of_words.ChangeStat(MyMap :: READING);

    double sum = 0;
    for (int i = 0; i < map_of_tags.GetNumber(); i ++)
        sum += initial[i];
    for (int i = 0; i < map_of_tags.GetNumber(); i ++){
        initial[i] /= sum;
        initial[i] = log(initial[i]);
    }

    for (int j = 0; j < map_of_tags.GetNumber(); j ++){
        double sum = 0;
        for (int i = 0; i < map_of_tags.GetNumber(); i ++)
            sum += tag_to_tag[i][j];
        for (int i = 0; i < map_of_tags.GetNumber(); i ++){
            tag_to_tag[i][j] /= sum;
            tag_to_tag[i][j] = log(tag_to_tag[i][j]);
        }
    }

    for (int j = 0; j < map_of_tags.GetNumber(); j ++){
        double sum = 0;
        for (int i = 0; i < map_of_words.GetNumber(); i ++)
            sum += word_in_tag[i][j];
        for (int i = 0; i < map_of_words.GetNumber(); i ++){
            word_in_tag[i][j] /= sum;
            word_in_tag[i][j] = log(word_in_tag[i][j]);
        }
    }
}

void Init(const char *train_file){
    Read(train_file);
    PreWork();
}

static void Answer(const string &line, ostream &os){
    istringstream is(line);
    istream_iterator<string> it(is), eof;
    vector<string> vec_of_str(it, eof);
    //memset(P, 0, sizeof(P));
    //memset(choise, -1, sizeof(choise));
    memcpy(P[0], initial, sizeof(P[0]));

    int n = vec_of_str.size();
    int m = map_of_tags.GetNumber();
    for (int t = 1; t < n; t ++){
        string word = vec_of_str[t];
        int i = map_of_words.GetId(word);
        if (i == -1){
            cerr << "no such word" << word << endl;
            exit(1);
        }
        for (int j = 0; j < m; j ++){
            P[t][j] = -kInfinite;
            choise[t][j] = -1;
            for (int k = 0; k < m; k ++){
                if (P[t][j] < P[t - 1][k] + tag_to_tag[j][k] + word_in_tag[i][j]){
                    P[t][j] = P[t - 1][k] + tag_to_tag[j][k] + word_in_tag[i][j];
                    choise[t][j] = k;
                }
            }
        }
    }

    double ans = 0;
    memset(final_choise, -1, sizeof(final_choise));
    for (int j = 0; j < map_of_tags.GetNumber(); j ++){
        if (ans < P[n - 1][j]){
            ans = P[n - 1][j];
            final_choise[n - 1] = j;
        }
    }
    for (int i = n - 2; i >= 0; i --)
        final_choise[i] = choise[i + 1][final_choise[i + 1]];

    for (int i = 0; i < n; i ++){
        os << vec_of_str[i] << "/" << map_of_tags[final_choise[i]] << ' ';
    }
    os << endl;
}

void Test(const char *test_input, const char *test_output){
    ifstream in(test_input);
    if (!in.is_open()){
        cerr << "wrong test file!" << endl;
        exit(1);
    }
    ofstream out(test_output);
    string line;
    while (getline(in, line)){
        Answer(line, out);
    }
}