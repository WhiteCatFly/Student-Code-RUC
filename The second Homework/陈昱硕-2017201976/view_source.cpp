#include "view_source.h"

#include <curl/curl.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <cctype>

#include <iostream>

#include <string>

#include "convert.h"

using namespace std;

extern string error_file;
extern string save_directory;

extern int timeout_time;
extern int time_interval;

const static int kMaxFileLength = 10000000;
const static int kMaxFileNameLength = 240;

static CURL *curl_handle;
static CURLcode return_code;

void InitViewer(){
	FILE *fp = fopen(error_file . c_str(), "w");
	fclose(fp);	
	
	return_code = curl_global_init(CURL_GLOBAL_ALL);
	if (return_code != CURLE_OK){
		fprintf(stderr, "global_init failed!\n");
		exit(2);
	}
	
	curl_handle = curl_easy_init();
	if (curl_handle == NULL){
		fprintf(stderr, "get a handle failed!\n");
		curl_global_cleanup();
		exit(2);
	}
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream){
	if (strlen((char *)stream) + size * nmemb > kMaxFileLength - 1) return 0;
	strncat((char *)stream, (char *)ptr, size * nmemb);
	return size * nmemb;
}

inline static char *Normalize(const char *web_site, char *content){
	size_t length_of_web_site = strlen(web_site);
	static char site[kMaxFileNameLength * 2];
	memcpy(site, web_site, sizeof(char) * length_of_web_site);
	site[length_of_web_site] = '\0';
	
	size_t length = strlen(content);
	string text = string(content);
	string :: size_type begin = text . find("charset=");
	static char buffer[kMaxFileLength];
	if (begin == string :: npos)
		return site;
	begin += strlen("charset=");
	if (isalpha(text . at(begin)) == false){
		begin = min(text . find("'", begin), text . find("\"", begin));
		if (begin == string :: npos)
			return site;
		begin ++;
	}
	if (toupper(text[begin]) == 'U'){
		if (toupper(text[begin + 1]) == 'N'){//unicode
			memset(buffer, 0, sizeof(char) * strlen(buffer));
			CodeConvert("unicode", "UTF-8", site, length, buffer, kMaxFileLength);
			return buffer;
		}
		else
			return site;
	}
	else if (toupper(text[begin]) == 'G'){//gbk
		memset(buffer, 0, sizeof(char) * strlen(buffer));
		CodeConvert("GBK", "UTF-8", site, length, buffer, kMaxFileLength);
		printf("url = %s\n", buffer);
		return buffer;
	}
	return site;
}

inline static void SaveFile(const char *web_site, char *buffer){
	string *site = new string(Normalize(web_site, buffer));
	string :: size_type begin = site -> find("://", 0) + strlen("://");
	string :: size_type end = site -> find_last_of("/");
	FILE *fp;
	string *directory, *file_name;
	if (begin != string :: npos){
		if (end == string :: npos || begin >= end){
			directory = new string(site -> substr(begin) + "/");
			file_name = new string("index.html");
		}
		else{
			directory = new string(site -> substr(begin, end - begin));
			file_name = new string(site -> substr(end));
			if (file_name -> length() > kMaxFileNameLength)
				file_name -> erase(kMaxFileNameLength);
			if (file_name -> find(".") == string :: npos)
				*file_name = *file_name + ".html";
		}
		
		system(("mkdir -p '" + save_directory + *directory + "'") . c_str());
		fp = fopen((save_directory + *directory + *file_name + ".download") . c_str(), "wb");
		
		if (fp == NULL){
			fp = fopen(error_file . c_str(), "a+");
			fprintf(fp, "failed to save : %s, %s\n", web_site, site -> c_str());
			fprintf(fp, "%s\n", buffer);
			fclose(fp);
		}
		else{
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fclose(fp);
		}
		delete directory;
		delete file_name;
	}
	delete site;
}

char *Download(const char *web_site){
	static char buffer[kMaxFileLength];
	memset(buffer, 0, sizeof(char) * strlen(buffer));
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, web_site);
	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, timeout_time);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, &write_data);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, buffer);
	curl_easy_setopt(curl_handle, CURLOPT_DNS_CACHE_TIMEOUT, 120000);
	
	static clock_t last_time = 0;
	static clock_t interval = clock() - last_time;
	if (last_time != 0 && interval < time_interval)
		usleep(interval);
	last_time += interval;
	
	return_code = curl_easy_perform(curl_handle);
	if (return_code != CURLE_OK){
		FILE *fp = fopen(error_file . c_str(), "a+");
		fprintf(fp, "%50s: %s\n", curl_easy_strerror(return_code), web_site);
		fclose(fp);
		return NULL;
	}
		
	SaveFile(web_site, buffer);
	
	return buffer;
}

void CloseViewer(){
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();
}
