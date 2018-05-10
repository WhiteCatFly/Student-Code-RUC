#include <cstdlib>
#include <cstring>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "parser.h"

using namespace std;

void HelpMessage();
template <class T>
ostream & operator << (ostream &os, const vector<T> &array);

int main(int argc, char *argv[]){
    string str;
    Parser :: Mode read_mode = Parser :: FROM_STRING;
    string output_file_name = "output.html";
    vector<string> list_mode;
    for (int i = 1; i < argc; i ++){
        string cur = argv[i], key;
        if (cur[0] == '-'){
            if (cur == "-s" || cur.find("--string=") == 0){
                key = (cur == "-s") ? argv[++ i] : cur.substr(strlen("--string="));
                str = key;
            }
            else if (cur == "-m" || cur.find("--mode=") == 0){
                key = (cur == "-m") ? argv[++ i] : cur.substr(strlen("--mode="));
                if (key == "from_file")
                    read_mode = Parser :: FROM_FILE;
                else if (key == "from_string")
                    read_mode = Parser :: FROM_STRING;
                else{
                    cerr << "read mode must be from_file or from_string" << endl;
                    HelpMessage();
                }
            }
            else if (cur == "-o" || cur.find("--open=") == 0){
                key = (cur == "-o") ? argv[++ i] : cur.substr(strlen("--open="));
                output_file_name = key;
            }
            else if (cur == "-l" || cur.find("--list=") == 0){
                key = (cur == "-l") ? argv[++ i] : cur.substr(strlen("--list="));
                list_mode.push_back(key);
            }
            else
                HelpMessage();
        }
        else
            HelpMessage();
    }

    Parser *parser = new Parser(str, read_mode, output_file_name.c_str());
    for (const auto &ele : list_mode){
        if (ele == "title"){
            cerr << "title : " << endl;
            cerr << parser -> GetTitle() << endl;
        }
        else if (ele == "body"){
            cerr << "body : " << endl;
            cerr << parser -> GetBody() << endl;
        }
        else if (ele == "links"){
            cerr << "links : " << endl;
            cerr << parser -> GetLinks() << endl;
        }
        else{
            try{
                cerr << "regex : " << ele << endl;
                regex re(ele, regex_constants :: icase);
                vector<string> *vec = parser -> GetFromRegex(re);
                cerr << (*vec) << endl;
                delete vec;
            }
            catch (regex_error &e){
                cerr << e.what() << endl;
                cerr << "error code : " << e.code() << endl;
            }
        }
    }
    return 0;
}

void HelpMessage(){
    ifstream input("README.md");
    if (!input.is_open()){
        cerr << "missing README.md!" << endl;
        exit(1);
    }
    string tmp, total;
    while (getline(input, tmp))
        total += tmp + "\n";
    input.close();
    cerr << total << endl;
    exit(1);
}

template <class T>
ostream & operator << (ostream &os, const vector<T> &array){
    ostream_iterator<T> out_iter(cerr, "\n");
    copy(array.begin(), array.end(), out_iter);
    return os;
}