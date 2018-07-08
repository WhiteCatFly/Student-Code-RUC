#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "result.h"
#include "enquiry.h"
#include "segment_dll.h"
#include "document.h"
#include "term.h"
#include "structure.h"

using namespace std;

void print(const string & str, map<string,bool> & enquiry_exist) {
	istringstream istr(str);
	string word_str;
	string line;
	while (getline(istr, line)) {
		istringstream iline(line);
		while (iline >> word_str) {
			if (enquiry_exist[word_str] == true) {
				cout << red_letter;
			}
			cout << word_str << ' ';
			if (enquiry_exist[word_str] == true) {
				cout << regular_letter;
			}
		}
		cout<<endl;
	} 
}

void print_res(result * res, const string & enquiry, const data_res & resource, const streambuf * default_buf, int branch_num) {
	int i = 0;
	while (res[i].ret_score() != 0) {
		if (i >= branch_num) {
			i++;
			continue;
		}
		int num = res[i].ret_num();
		string url = res[i].ret_url();
		vector<string> vs;
		if (cout.rdbuf() == default_buf) {
			cout << i + 1 << endl;
			cout << blue_letter;
			cout << "网址";
			cout << regular_letter;
			cout << " : " << url << endl;
			void * engine = segmentor_create_segmentor(segmentor_path.c_str());
			segmentor_segment(engine, enquiry, vs);
			segmentor_release_segmentor(engine);
			map<string,bool> enquiry_exist;
			enquiry_exist.clear();
			int size = vs.size();
			for (int j = 0;j < size; ++j) {
				enquiry_exist[vs[j]] = true;
			}
			cout << blue_letter;
			cout << "标题";
			cout << regular_letter;
			cout << " : ";
			print(resource.docu[num].ret_title(), enquiry_exist);
			cout << blue_letter;
			cout << "内容";
			cout << regular_letter;
			cout << " : " << endl;
			print(resource.docu[num].ret_content(), enquiry_exist);
		}
		else {
			cout << i + 1 << endl;
			cout << "网址" << " : " << url << endl;
			cout << "标题" << " : " << resource.docu[num].ret_title() << endl;
			cout << "内容" << " : " << resource.docu[num].ret_content() << endl;
		}
		i++;
		cout << "-------------------------------------------" << endl;
	}
	cout << green_letter;
	cout << "共有 " << i << " 条结果" << endl;
	cout << "已显示 " << min(i, branch_num) << " 条结果" << endl;
	cout << regular_letter;
}

static void segmentor(const string & enquiry, vector<string> & vs) {
	void * engine = segmentor_create_segmentor(segmentor_path.c_str());
	int len = segmentor_segment(engine, enquiry, vs);
	segmentor_release_segmentor(engine);
}

static void make_vector(const string & enquiry, document & question, const vector<string> & vs, data_res & resource) {
	int size = vs.size();
	
	int * exist = new int [term::term_num];
	
	for (int i = 0;i < term::term_num; ++i)
		exist[i] = 0;
	
	for (map<string,int>::iterator it = resource.docu_list.begin(); it != resource.docu_list.end(); ++it) {
		resource.docu[it -> second] = document(it -> first, 0, vs.size());
	}
	
	for (int i = 0;i < size;++i) {
		if (resource.word_list.find(vs[i]) == resource.word_list.end())
			continue;
		if (exist[resource.word_list[vs[i]]] == 0) {
			exist[resource.word_list[vs[i]]] = i + 1;
		}
		question.add_term(resource.word_list[vs[i]], exist[resource.word_list[vs[i]]] - 1, 1.0 / size);
		resource.word[resource.word_list[vs[i]]].make_docu(exist[resource.word_list[vs[i]]] - 1, resource);
	}
	
	
	
	question.regularize_crd();
	question.mult_idf(resource.word);
}

result * enquiry_processor(const string enquiry, data_res & resource) {
	vector<string> vs;
	segmentor(enquiry, vs);	
	document question(enquiry, 1, vs.size());
	
	make_vector(enquiry, question, vs, resource);
	result * res = new result [document::docu_num];
	for (int i = 0; i < document::docu_num; ++i) {
		resource.docu[i].regularize_crd();
		resource.docu[i].mult_idf(resource.word);
		res[i] = result(i, question, resource.docu);
	}
	
	sort(res, res + document::docu_num);
	return res;
}
