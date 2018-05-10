#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

const string sensitive_words[100]={"css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", ".bmp", ".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", "str = str+", "$", "end_word"};
const string trans_words[100][2] = {{"&ldquo;", "“"}, {"&rdquo;", "”"}, {"&nbsp;", " "}, {"&gt;", ">"}, {"&quot;", "'"}, {"end_word"}};
const string http = "http://", https = "https://", end_word = "end_word";

class HTML{
private:
	string htmlcode, origin_html, http_feature;
public:
	HTML(string &file_or_code);
	HTML();
	string get_htmlcode(){return htmlcode;}
	void initialize_string();
	void get_url() const;
	void get_title() const;
	void get_img() const;
	void get_main_text() const;
	void get_certain_pattern(const string &type) const;
	void get_tree_structure() const;
	void user_interface() const;
	void continue_interface() const;
	string combine_origin_new(const string &new_url) const;
};

