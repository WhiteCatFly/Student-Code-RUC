#include <cstdio>
#include <cstring>

#include "global_settings.h"
#include "crawl.h"

int main(int argc, char *argv[]){
	vector<string> seed;
	vector<string> key_word;

	int running_mode = Restart;

	string input_file = "origin.log";
	string output_file = "origin.log";
	string error_file = "error.log";
	string save_directory = "./download/";
	int retry_count = 5;
	int timeout_time = 10;
	int time_interval = 50000;
	
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
			else if (option . find("--retry-count=") == 0){
				key = option . substr(strlen("--retry-count"));
				SetValue(retry_count, key);
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
	NormalizeSeed(seed);
	
	Crawler *crawler = new Crawler(seed, key_word, running_mode,
								   input_file, output_file, error_file,
								   save_directory, retry_count,
								   timeout_time, time_interval);
	crawler -> Crawl();
	return 0;
}
