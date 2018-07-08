#include <iostream>
#include <string>
#include <vector>

#include "result.h"
#include "document.h"

using namespace std;

static string make_url(const string & path) {
	return path.substr(pred_name_len);
}

result::result() {
	num = 0;
	score = 0;
	page_url = "";
}

result::result(int docu_pos, const document & question, const vector<document> & docu) {
	num = docu_pos;
	page_url = make_url(docu[docu_pos].ret_path());
	score = question ^ docu[docu_pos];
	//if (score != 0) {
	//	cout<<docu_pos<<' '<<score<<endl;
	//}
	//cout<<question.length()<<' '<<docu[docu_pos].length()<<endl;
	//if (question.length() == 0 || docu[docu_pos].length() == 0)
	//	score = -1;
	//else 
	//	score = score / (question.length() * docu[docu_pos].length());
	//cout<<score<<endl;
}

result::~result() {
}

int result::ret_num() const {
	return num;
}

string result::ret_url() const {
	return page_url;
}
	
bool operator < (const result & a, const result & b) {
	return a.score > b.score;
}
