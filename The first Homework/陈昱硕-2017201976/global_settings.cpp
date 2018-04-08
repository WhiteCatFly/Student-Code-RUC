#include "global_settings.h"

#include <cstdio>
#include <ctime>
#include <cstring>

#include <iostream>

#include <string>
#include <vector>

using namespace std;

vector<string> seed;//string("http://wenxueyuan.ruc.edu.cn/article/?3679.html"); = string("http://www.ruc.edu.cn");
vector<string> key_word;

int running_mode = Restart;

string input_file = string("origin.log");
string output_file = string("origin.log");
string error_file = string("error.log");
string save_directory = string("./download/");
int timeout_time = 10;
int time_interval = 50000;

inline static void HelpMessage(){
	FILE *fp = fopen("README.md", "r");
	char *message;
	message = (char *) malloc(sizeof(char) * 100000);
	fread(message, sizeof(char), 100000, fp);	
	fclose(fp);
	fprintf(stderr, "%s\n", message);	
	free(message);
}

inline static void SetArray(const string &keys, vector<string> &array){
	string :: size_type begin = 0;
	string :: size_type end;
	do{
		end = keys . find(",", begin);
		if (end == string :: npos)
			end = keys . length();
		
		array . push_back(keys . substr(begin, end - begin));
		
		begin = end + 1;
	}while (end != keys . length());
}

inline static void SetValue(int &value, const string &key){
	for (auto iter : key){
		if (!isdigit(iter)){
			fprintf(stderr, "%s isn't an positive interger\n\n", key . c_str());
			HelpMessage();
			exit(1);
		}
	}
	value = atoi(key . c_str());
}

inline static void NormalizeWebSite(string &web_site){
	if (web_site . find("://") == string :: npos)
		web_site = "http://" + web_site;
	if (web_site . at(web_site . length() - 1) == '/')
		web_site . erase(web_site . length() - 1);
}

inline static void NormalizeSeed(){
	/*for (auto it : seed){
		NormalizeWebSite(it);
		cerr << it << endl;
	}*/
	for (auto it = seed . begin(); it != seed . end(); it ++)
		NormalizeWebSite(*it);
}

inline static void PrintSettings(){
	cout << "seed : " << endl;
	for (auto it : seed)
		cout << '\t' << (it) << endl;
	cout << "key word : " << endl;
	for (auto it : key_word)
		cout << '\t' << (it) << endl;
	cout << "running mode = " << running_mode << endl;
	cout << "input file = " << input_file << endl;
	cout << "output file = " << output_file << endl;
	cout << "error file = " << error_file << endl;
	cout << "save directory = " << save_directory << endl;
	cout << "timeout time = " << timeout_time << endl;
	cout << "time interval = " << time_interval << endl;
	cout << "---------------------------------" << endl;
}

void InitGlobalSettings(const int &argc, char *argv[]){
	string option, key;
	for (char **ptr = argv + 1; *ptr != NULL; ptr ++){
		if (*ptr[0] == '-'){
			option = string(*ptr);
			if (option == "-s" || option . find("--seed=") == 0){
				if (option == "-s"){
					ptr ++;
					key = string(*ptr);
				}
				else{
					key = option . substr(strlen("--seed="));
				}
				SetArray(key, seed);
			}
			else if (option == "-k" || option . find("--key-word=") == 0){
				if (option == "-k"){
					ptr ++;
					key = string(*ptr);
				}
				else{
					key = option . substr(strlen("--key-word="));
				}
				SetArray(key, key_word);
			}
			else if (option == "-l" || option . find("--load=") == 0){
				running_mode = Load;
				if (option == "-l"){
					ptr ++;
					key = string(*ptr);
				}
				else{
					key = option . substr(strlen("--load="));
				}
				input_file = key;
			}
			else if (option == "-h" || option . find("--help") == 0){
				HelpMessage();
				exit(0);
			}
			else if (option . find("--break-point=") == 0){
				output_file = option . substr(strlen("--break-point="));
			}
			else if (option . find("--error=") == 0){
				error_file = option . substr(strlen("--error="));
			}
			else if (option . find("--timeout=") == 0){
				key = option . substr(strlen("--timeout="));
				SetValue(timeout_time, key);
			}
			else if (option . find("--time-interval=") == 0){
				key = option . substr(strlen("--time-interval="));
				SetValue(time_interval, key);
				time_interval *= 1000;
			}
			else if (option . find("--save-directory=") == 0){
				key = option . substr(strlen("--save-directory="));
				int result = system(("mkdir -p '" + key + "'") . c_str());
				if (result != 0){
					fprintf(stderr, "please give a legal path!\n\n");
					HelpMessage();
					exit(1);
				}
				save_directory = key;
			}
			else{
				HelpMessage();
				exit(1);
			}
		}
		else{
			HelpMessage();
			exit(1);
		}
	}
	NormalizeSeed();
	PrintSettings();
}
