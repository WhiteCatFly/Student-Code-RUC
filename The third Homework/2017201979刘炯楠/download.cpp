#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include "download.h"
#include "normalization.h"

using namespace std;

inline static void wrong_put() {
	cerr<<"wrong!"<<endl;
	cout<<"the standord format is :"<<endl;
	cout<<"./web_crawler start_page -L=limit_page -T=per_time -N=try_number -S=sleep_time"<<endl;
	cout<<"default:"<<endl;
	cout<<"limit_page = start_page"<<endl;
	cout<<"per_time = 5.0"<<endl;
	cout<<"try_number = 3"<<endl;
	cout<<"sleep_time = 0.05"<<endl;
	exit(1);
}

inline static double stringtof(string tp) {
	int len = tp.length();
	char figure[MAXLEN];
	for (int i = 0; i < len; ++i)
		figure[i] = tp[i];
	figure[len] = '\0';
	return atof(figure);
}

inline static int strington(string tp) {
	int number = 0;
	int len = tp.length();
	for (int i = 0;i < len; ++i)
		number = number * 10 + tp[i] - '0'; 
	return number;
}

void order::work(const string &temp, const int kind) {
	if (kind == 0) {
		m_limit_name = "";
		int len = temp.length();
		for (int i = option_len; i < len; ++i)
			m_limit_name += temp[i];
	}
	if (kind == 1) {
		int len = temp.length();
		string tp = "";
		for (int i = option_len; i < len; ++i) {
			tp += temp[i];
			if ((temp[i] < '0' || temp[i] > '9')&&(temp[i] != '.'))
				wrong_put();
		}
		m_per_time = stringtof(tp);
	}
	if (kind == 2) {
		int len = temp.length();
		string tp = "";
		for (int i = option_len; i < len; ++i) {
			tp += temp[i];
			if (temp[i] < '0' || temp[i] > '9')
				wrong_put();
		}
		m_number = strington(tp);
	}
	if (kind == 3) {
		int len = temp.length();
		string tp = "";
		for (int i = option_len; i < len; ++i) {
			tp += temp[i];
			if ((temp[i] < '0' || temp[i] > '9')&&(temp[i] != '.'))
				wrong_put();
		}
		m_sleep_time = stringtof(tp);
	}
}

void order::download(const string &web_page) const {
	char * web_page_name = (char *) malloc (MAXLEN * sizeof(char));
	const int len = web_page.length();

	for (int i = 0; i < len; ++i) {
		web_page_name[i] = web_page[i];
	}
	web_page_name[len] = '\0';
	char * instruction_1 = (char *) malloc ((MAXLEN + EXTRA_LEN)* sizeof (char));
	char * directory = normalize_directory(web_page);
	sprintf(instruction_1,"mkdir -p '%s'",directory);
	system(instruction_1);

	char * file_name = normalize_file_name(web_page);
	char * instruction_2 = (char *) malloc ((2 * MAXLEN  + EXTRA_LEN)* sizeof (char));
	sprintf(instruction_2, "wget -O '%s' '%s' --tries=%d -T%lf",file_name, web_page_name,m_number,m_per_time);
	cout<<instruction_2<<endl;

	system(instruction_2);

	usleep(CLOCKS_PER_SEC * m_sleep_time);

	free(web_page_name);
	free(file_name);
	free(directory);
	free(instruction_1);
	free(instruction_2);
}

order::order(const int number,const char ** value) {
	m_limit_name = value[1];
	m_per_time = 5.0;
	m_number = 3;
	m_sleep_time = 0.05;
	//cout<<number<<' '<<value[1]<<' '<<value[2]<<' '<<value[3]<<endl;
	if (number <= 1) wrong_put();
	else {
		for (int i = 2; i < number;++i) {
			//cout<<value[i]<<endl;
			string temp = value[i];
			int cnt = 0;
			for (int j = 0;j < 4;++j) {cout<<temp<<' '<<option[j]<<endl;
				if (temp.find(option[j]) == 0) {
					//cout<<i<<' '<<j<<endl;
					cnt++;
					work(temp, j);
				}}
			if (cnt != 1)
				wrong_put();
		}
	}
}
