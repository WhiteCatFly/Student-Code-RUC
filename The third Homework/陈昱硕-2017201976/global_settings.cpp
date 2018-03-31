#include "global_settings.h"

#include <cstdio>
#include <ctime>
#include <cstring>

#include <iostream>

#include <string>
#include <vector>

using namespace std;

static const int kLengthOfReadMe = 100000;

void HelpMessage(){
	FILE *fp = fopen("README.md", "r");
	char *message;
	message = (char *) malloc(sizeof(char) * kLengthOfReadMe);
	fread(message, sizeof(char), kLengthOfReadMe, fp);	
	fclose(fp);
	fprintf(stderr, "%s\n", message);	
	free(message);
}

void SetArray(const string &keys, vector<string> &array){
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

void SetValue(int &value, const string &key){
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

void NormalizeSeed(vector<string> &seed){
	for (auto it = seed . begin(); it != seed . end(); it ++)
		NormalizeWebSite(*it);
}
