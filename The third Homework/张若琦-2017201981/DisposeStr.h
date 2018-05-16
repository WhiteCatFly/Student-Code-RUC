#ifndef DisposeStr_H_
#define DisposeStr_H_

using std :: string;

const int ROOT_URL_LEN = 15;

const struct url_prefix {
	string pre;
	int len;
} UrlPre[3] = {
	{"www.",4},
	{"http://www.",11},
	{"https://www.",12}
};

class URLS {
private :
	string url_;
public :
	URLS(string url = "") {url_ = url;}
	~URLS() {};

	void insert();
	void push();

	bool check_out_site(const string & root_url) const;
	bool check_in_set() const;
	bool check_php() const;
	bool check_html() const;
	bool check_css() const;
	bool check_js() const;
	bool check_suf() const;
	bool check_pre() const;
	void filter_blank_character();
	void Get_whole_url(const string & root_url,string now_url);
};

#endif // DisposeStr_H_