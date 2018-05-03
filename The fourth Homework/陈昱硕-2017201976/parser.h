#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <regex>
#include <stack>

using std :: pair;
using std :: vector;
using std :: string;
using std :: regex;
using std :: stack;

typedef std :: sregex_iterator re_iter;
typedef pair<string, string> PairOfString;//first : tag  second : content

class Parser{
public:
    enum Mode {FROM_FILE, FROM_STRING};

private:
    const static re_iter end_iter; //枚举regex匹配用的

    const static string main_pattern_; //枚举标签用的正则表达式
    const static string links_pattern_; //枚举链接用的正则表达式
    const static string simple_tags_pattern_; //枚举简单标签的正则表达式
    const static string title_pattern_; //枚举标题的正则表达式
    const static string content_tags_pattern_; //枚举正文的正则表达式
    const static string script_pattern_; //枚举script的正则表达式

    const static regex main_regex_; //枚举标签用的
    const static regex links_regex_; //枚举链接用的
    const static regex simple_tags_regex_; //枚举简单标签
    const static regex title_regex_; //枚举标题
    const static regex content_tags_regex_; //枚举正文
    const static regex script_regex_; //枚举script

    static stack<PairOfString> stack_of_tags_; //标签的栈

    const char *output_file_name_; //格式化后HTML源码的输出文件
    vector<string> titles_; //标题
    vector<string> bodies_; //正文
    vector<string> links_; //链接
    string content_; //全部内容

    void Build(string str);
    void DeleteSpaceChar(string &str);
    void ClearOutput();
    void Output(const string &str);

public:
    Parser() = default;
    Parser(const string &str, Mode stat = FROM_STRING,
           const char *output_file_name = "output.html");

    ~Parser() = default;

    const vector<string> &GetTitle(){return titles_;}
    const vector<string> &GetBody(){return bodies_;}
    const vector<string> &GetLinks(){return links_;}
    vector<string> *GetFromRegex(const regex &user_regex);
};

#endif