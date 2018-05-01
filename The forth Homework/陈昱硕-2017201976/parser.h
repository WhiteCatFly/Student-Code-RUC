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

typedef pair<string, string> PairOfString;//first : tag  second : content

class Parser{
public:
    enum Mode {FROM_FILE, FROM_STRING};

private:
    const static string main_pattern_;
    const static string links_pattern_;
    const static string simple_tags_pattern_;
    const static string title_pattern_;
    const static string content_tags_pattern_;
    const static string script_pattern_;

    const static regex main_regex_;
    const static regex links_regex_;
    const static regex simple_tags_regex_;
    const static regex title_regex_;
    const static regex content_tags_regex_;
    const static regex script_regex_;

    static stack<PairOfString> stack_of_tags_;

    const char *output_file_name_;
    vector<string> titles_;
    vector<string> bodies_;
    vector<string> links_;
    string content_;

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