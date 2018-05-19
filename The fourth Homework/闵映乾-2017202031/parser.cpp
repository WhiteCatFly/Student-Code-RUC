#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


class Parser{
	private:
		string html_content;                                                                //存储html内容
		vector<string> p_node;                                                              //存储p标签
		vector<string> h_node;                                                              //存储h标签
		vector<string> url;                                                                 //存储url
		string title;                                                                       //存储网页标题
	public:
		//Parser(string html_code);
		Parser(int order , char * file_name = "defult_file" , string html_code = "defult_code");
		void ExtractP();
		void ExtractH();
		void ExtractTitle();
		void ExtractUrl();
		
};

char file_name_input[] = "defult_file";
string website_input = "defult_code";

int main(){
    const int file_choice = 0;
    const int website_choice = 1;
	int choice = 2;
	cout << "If you want to use a file , please press 0" << endl
		 << "If you want to use a website , please press 1" << endl;
	cin >> choice;
	cout << "Now please input the information you want to provide" << endl;
	if(choice == file_choice){
		cin >> file_name_input;
	}
	else if(choice == website_choice){
		cin >> website_input;
	}
	else{
		cout << "You have input wrong information" << endl;
		return 0;
	}
	Parser analysis(choice , file_name_input , website_input);
	analysis.ExtractP();
	analysis.ExtractH();
	analysis.ExtractTitle();
	analysis.ExtractUrl();
	return 0;		
}

Parser::Parser(int order , char * file_name  , string html_code  ){
	if(order == 0){
		ifstream fin;
		fin.open(file_name);
		if(fin.is_open()){
			string line_content;
			while(getline(fin , line_content)){
				html_content += line_content;
			}
			fin.close();
		}
		else{
			cout << "Running error" << endl;
		}
	}
	else{
		html_content = html_code;
	}
	//cout << html_content <<endl;
}


void Parser::ExtractTitle(){
 	const string flag_title_beg = "<title>";
 	const string flag_title_end = "</title>";
 	const int difference = 7 ;
 	int pos_beg = 0;
 	int pos_end = 0;
	pos_beg = html_content.find(flag_title_beg);
	pos_end = html_content.find(flag_title_end , pos_beg);
	int len_title = pos_end - pos_beg - difference;
	title = html_content.substr(pos_beg + difference , len_title);
	//cout << title << endl;
}

void Parser::ExtractP(){
	const string flag_p_beg = "<p";
	const string flag_p_end = "</p>";
	int position_beg = 0;
	int position_end = 0;
	int len_p = 0;
	while(position_beg != -1){
		position_beg = html_content.find(flag_p_beg , position_end);
		if(position_beg == -1)
		break;
		else{
			position_beg = html_content.find('>' , position_beg) + 1;
			position_end = html_content.find(flag_p_end , position_beg);
			len_p = position_end - position_beg;
			string mid_p = html_content.substr(position_beg , len_p);
			int correct_p_beg = 0;
			int correct_p_end = 0;
			while(correct_p_beg != -1){
				correct_p_beg = mid_p.find('<' , correct_p_beg);
				if(correct_p_beg == -1)
				break;
				else{
					correct_p_end = mid_p.find('>' , correct_p_beg);
					mid_p.erase(correct_p_beg , correct_p_end - correct_p_beg + 1);
				}
			}
			//cout << mid_p <<endl;
			p_node.push_back(mid_p);
		}
	}
	
}

void Parser::ExtractH(){
	const string flag_h_beg = "<";
	const string flag_h_end = ">";
	int site_beg = 0;
	int site_end = 0;
	int len_h = 0;
	site_beg = html_content.find("<body>" , site_beg) + 6;
	while(site_beg != -1){
		site_beg = html_content.find(flag_h_beg , site_end);
		if(site_beg == -1)
		break;
		else{
			site_end = html_content.find(flag_h_end , site_beg);
			if(html_content.substr(site_beg + 1 , 6) == "script")
			continue;
			site_beg = site_end;
			site_end = html_content.find(flag_h_beg , site_end);
			len_h = site_end - site_beg - 1;
			string mid_h = html_content.substr(site_beg + 1 , len_h);
			int len_mid_h = mid_h.size();
			int count_h = 0;
			for(int i = 0 ; i < len_mid_h ; i++){
				if(mid_h[i] != ' ')
				count_h ++ ;
			}
			if(count_h == 0)
			continue;
			//cout << mid_h << endl;
			h_node.push_back(mid_h);
		}
	}
}

void Parser::ExtractUrl(){
	const string flag_url_beg_first = "<a";
	const string flag_url_beg_second = "href=\"";
	const string flag_url_end = ">";
	int place_beg = 0;
	int place_end = 0;
	int len_url = 0;
	while(place_beg != -1){
		place_beg = html_content.find(flag_url_beg_first , place_end);
		if(place_beg == -1)
		break;
		else{
			place_beg = html_content.find(flag_url_beg_second , place_beg) + 6;
			place_end = html_content.find(flag_url_end , place_beg) - 1;
			len_url = place_end - place_beg ;
			url.push_back(html_content.substr(place_beg , len_url));
			//cout << html_content.substr(place_beg , len_url) << endl;
		}
	}
}

























































































