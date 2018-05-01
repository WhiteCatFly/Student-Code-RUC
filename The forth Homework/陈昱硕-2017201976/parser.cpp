#include "parser.h"

#include <cstdio>
#include <cstdlib>
#include <cctype>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

#define FOR(it, arr, re) for (re_iter it(arr.begin(), arr.end(), re);\
                            it != end_iter; it ++)

typedef sregex_iterator re_iter;
typedef regex_constants :: syntax_option_type syntax_option_type;

static const re_iter end_iter;//枚举regex匹配用的

const string Parser :: main_pattern_("<!--.*?-->|<(/?[a-z]+).*?>");
const string Parser :: links_pattern_("href\\s*=\\s*('.*?'|\".*?\")");
const string Parser :: simple_tags_pattern_("br|hr|img|input|param|meta|link|base");
const string Parser :: title_pattern_("/title");
const string Parser :: content_tags_pattern_("/p|/h[1-6]|/a|/body");
const string Parser :: script_pattern_("/?script");

static const auto icase = regex_constants :: icase;
const regex Parser :: main_regex_(Parser :: main_pattern_, icase);
const regex Parser :: links_regex_(Parser :: links_pattern_, icase);
const regex Parser :: simple_tags_regex_(Parser :: simple_tags_pattern_, icase);
const regex Parser :: title_regex_(Parser :: title_pattern_, icase);
const regex Parser :: content_tags_regex_(Parser :: content_tags_pattern_, icase);
const regex Parser :: script_regex_(Parser :: script_pattern_, icase);

stack<PairOfString> Parser :: stack_of_tags_;

inline void Parser :: DeleteSpaceChar(string &str){
    string res;
    for (auto ch : str){
        if (isspace(ch)){
            if (!isspace(*res.rbegin()))
                res.push_back(' ');
        }
        else{
            res.push_back(ch);
        }
    }
    str = res;
}

inline void Parser :: ClearOutput(){
    ofstream output(output_file_name_);
    output.close();
}

inline static bool isspace(const string &str){
    for (auto ch : str)
        if (!isspace(ch))
            return false;
    return true;
}

inline void Parser :: Output(const string &str){
    if (!isspace(str)){
        ofstream output(output_file_name_, ios_base :: out | ios_base :: app);
        for (int i = stack_of_tags_.size(); i > 0; i --)
            output << '\t';
        output << str << endl;
        output.close();
    }
}

inline static bool isequal(const string &s1, const string &s2){
    int len = s1.length();
    if (len != (int)s2.length())
        return false;
    for (int i = 0; i < len; i ++)
        if (tolower(s1[i]) != tolower(s2[i]))
            return false;
    return true;
}

void Parser :: Build(string str){
    ClearOutput();
    DeleteSpaceChar(str);
    while (!stack_of_tags_.empty())
        stack_of_tags_.pop();

    int cur_position, last_position = 0;
    int script_count = 0;
    FOR(it, str, main_regex_){
        string all = it -> str();//main_regex_所匹配的整个标签
        string tag = it -> str(1);//标签名
        cur_position = it -> position();
        string gap(str.substr(last_position, cur_position - last_position));
        //当前标签和上个标签之间的内容

        if (!stack_of_tags_.empty()){//把内容连到前面一个标签里
            PairOfString top = stack_of_tags_.top();
            stack_of_tags_.pop();
            top.second += gap;
            stack_of_tags_.push(top);
        }

        Output(gap);
        Output(all);
        if (all[1] == '!'){
            //注释
        }
        else{//非注释
            FOR(href, all, links_regex_){//提取链接
                string link = href -> str(1);
                link = link.substr(1, link.length() - 2);
                if (link != "")
                    links_.push_back(link);
            }

            if (regex_match(tag, simple_tags_regex_)){
                //简单标签
            }
            else{
                if (tag[0] == '/'){//结束标签
                    if (regex_match(tag, script_regex_))
                        script_count --;
                    if (script_count == 0){//判断是否在<script></script>内
                        if (stack_of_tags_.empty()){
                            cerr << "invaild pages!" <<
                                " tag = '" << tag << "'" << endl;
                            exit(1);
                        }
                        PairOfString top = stack_of_tags_.top();
                        stack_of_tags_.pop();
                        if (!isequal("/" + top.first, tag)){
                            cerr << "invaild pages!" <<
                                " top.first = '" << top.first <<
                                "' tag = '" << tag << "'" << endl;
                            exit(1);
                        }
                        if (regex_match(tag, title_regex_)){//是标题
                            if (top.second != "")
                                titles_.push_back(top.second);
                        }
                        if (regex_match(tag, content_tags_regex_)){//是正文
                            if (top.second != "")
                                bodies_.push_back(top.second);
                            }
                    }
                }
                else{//开始标签
                    if (script_count == 0)
                        stack_of_tags_.push(make_pair(tag, ""));
                    if (regex_match(tag, script_regex_))//判断是否在<script></script>内
                        script_count ++;
                }
            }
        }
        last_position = cur_position + it -> length();
    }

    Output(str.substr(last_position));
}

Parser :: Parser(const string &str, Mode stat,
                 const char *output_file_name) :
    output_file_name_(output_file_name)
{
    if (stat == FROM_STRING){
        content_ = str;
        Build(str);
    }
    else{
        ifstream input(str.c_str());
        if (!input.is_open()){
            cerr << "please give a vaild input file name!" << endl;
            exit(1);
        }
        string tmp, res;
        while (getline(input, tmp))
            res += tmp + "\n";
        input.close();
        content_ = res;
        Build(res);
    }
}

vector<string> * Parser :: GetFromRegex(const regex &user_regex){
    vector<string> *array = new vector<string>;
    FOR(it, content_, user_regex)
        array -> push_back(it -> str());
    return array;
}