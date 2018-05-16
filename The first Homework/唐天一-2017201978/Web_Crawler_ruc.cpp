#include<bits/stdc++.h>

using namespace std;

const string sensitive_words[100]={".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", ".bmp", ".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", "str = str+", "$", "words_end"};

void get_html(string &current_url, string &current_html, int &total){
	char operation[1000], number_html[1000];
	sprintf(number_html, "%d.html", ++total);
	sprintf(operation, "wget --tries=1 \"%s\" -O %s", current_url.c_str(), number_html);
	cout<<"*********"<<operation<<"*********"<<endl;
	system(operation);
	FILE* read_html = fopen(number_html, "r");
	char temp = fgetc(read_html);
	while (temp != EOF){
		current_html.push_back(temp);
		temp = fgetc(read_html);
	}
	fclose(read_html);
}

void find_next_url(string &current_url, string &current_html, queue<string> &url_queue, set<string> &url_set){
	int url_begin = current_html.find("href=");
	while (url_begin != -1){
		int url_end = current_html.find(current_html[url_begin + 5] == '\"' ? '\"' : '\'', url_begin + 6);
		string new_url = current_html.substr(url_begin + 6, url_end - url_begin - 6);
		url_begin = current_html.find("href=", url_end);
		if (new_url.find("ruc.edu.cn") != new_url.npos){
			if (new_url.find("http:") != new_url.npos)
				new_url.erase(0,7);
		}
		else if (new_url.find("http") == new_url.npos){
				if (new_url[0] == '/')
					new_url = current_url.substr(0, current_url.find_last_of('/') + 1) + new_url.substr(1);
				else new_url = current_url.substr(0, current_url.find_last_of('/') + 1) + new_url;
			}
		if (new_url.find("ruc.edu.cn") != new_url.npos){
			int flag = 0;
			for (int i = 0; sensitive_words[i] != "words_end"; ++i){
				if (new_url.find(sensitive_words[i]) != new_url.npos){
					flag = 1;
					break;
				}
			}
			if (flag)
				continue;
			if (!url_set.count(new_url)){
				url_set.insert(new_url);
				url_queue.push(new_url);
			}
		}
	}
}

void Web_Crawler(){
	queue<string> url_queue;
	while (!url_queue.empty())
		url_queue.pop();
	set<string> url_set;
	url_set.clear();
	
	int total = 0;
	string origin = "www.ruc.edu.cn/";
	url_queue.push(origin);
	url_set.insert(origin);
	while (!url_queue.empty()){
		string current_url = url_queue.front(), current_html = "";
		url_queue.pop();
		get_html(current_url, current_html, total);
		find_next_url(current_url, current_html, url_queue, url_set);
	}
	printf("There are %d websites in http://www.ruc.edu.cn.\n", total);
}

int main(){
	system("rm *.html");
	system("reset");
	Web_Crawler();
	return 0;
}

