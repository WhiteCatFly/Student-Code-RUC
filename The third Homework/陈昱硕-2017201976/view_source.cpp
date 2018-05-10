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

const int Viewer :: kMaxFileLength;
const int Viewer :: kMaxFileNameLength;
const int Viewer :: kDNSCacheTimeout;

Viewer :: Viewer(const string &error_file,
                 const string &save_directory,
                 const int &timeout_time,
                 const int &time_interval) :
    error_file_(error_file), save_directory_(save_directory),
    timeout_time_(timeout_time), time_interval_(time_interval)
{
    FILE *fp = fopen(error_file_ . c_str(), "w");
    fclose(fp);
    
    return_code_ = curl_global_init(CURL_GLOBAL_ALL);
    if (return_code_ != CURLE_OK){
        fprintf(stderr, "global_init failed!\n");
        exit(2);
    }
    
    curl_handle_ = curl_easy_init();
    if (curl_handle_ == NULL){
        fprintf(stderr, "get a handle failed!\n");
        curl_global_cleanup();
        exit(2);
    }
}

inline size_t Viewer :: write_data(void *ptr, size_t size, size_t nmemb, void *stream){
    string *str = (string *) stream;
    *str = *str + string((char *) ptr, size * nmemb);
    return size * nmemb;
}

char *Viewer :: Normalize(const string &web_site, const string &content){
    auto length = web_site . length();
    static char site[kMaxFileNameLength * 2];
    strcpy(site, web_site . c_str());
    
    static char buffer[kMaxFileNameLength * 2];
    
    string :: size_type begin = content . find("charset=");
    
    if (begin == string :: npos)
        return site;
    begin += strlen("charset=");
    if (isalpha(content . at(begin)) == false){
        begin = min(content . find("'", begin), content . find("\"", begin));
        if (begin == string :: npos)
            return site;
        begin ++;
    }
    
    if (toupper(content[begin]) == 'U'){
        if (toupper(content[begin + 1]) == 'N'){//unicode
            memset(buffer, 0, sizeof(char) * strlen(buffer));
            CodeConvert("unicode", "UTF-8", site, length, buffer, kMaxFileNameLength * 2);
            return buffer;
        }
        else
            return site;
    }
    else if (toupper(content[begin]) == 'G'){//gbk
        memset(buffer, 0, sizeof(char) * strlen(buffer));
        CodeConvert("GBK", "UTF-8", site, length, buffer, kMaxFileNameLength * 2);
        //printf("url = %s\n", buffer);
        return buffer;
    }
    return site;
}

void Viewer :: SaveFile(const string &web_site, const string &buffer){
    string *site = new string(Normalize(web_site, buffer));
    string :: size_type begin = site -> find("://", 0) + strlen("://");
    string :: size_type end = site -> find_last_of("/");
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
        }

        if (system(("mkdir -p '" + save_directory_ + *directory + "'") . c_str()) != 0){
            FILE *fp = fopen(error_file_ . c_str(), "a+");
            fprintf(fp, "failed to mkdir : %s\n", directory -> c_str());
            fprintf(fp, "%s\n", buffer . c_str());
            fclose(fp);
        }
        else{
            FILE *fp = fopen((save_directory_ + *directory + *file_name + ".download") . c_str(), "wb");
            if (fp == NULL){
                fp = fopen(error_file_ . c_str(), "a+");
                fprintf(fp, "failed to save : %s, %s\n", web_site . c_str(), site -> c_str());
                fprintf(fp, "%s\n", buffer . c_str());
                fclose(fp);
            }
            else{
                fwrite(buffer . c_str(), sizeof(char), buffer . length(), fp);
                fclose(fp);
            }
        }
        delete directory;
        delete file_name;
    }
    delete site;
}

int Viewer :: Download(const string &web_site, string &content){
    content = "";
    
    curl_easy_setopt(curl_handle_, CURLOPT_URL, web_site . c_str());
    curl_easy_setopt(curl_handle_, CURLOPT_TIMEOUT, timeout_time_);
    curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, &write_data);
    curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(curl_handle_, CURLOPT_DNS_CACHE_TIMEOUT, kDNSCacheTimeout);
    
    static clock_t last_time = 0;
    static clock_t interval = clock() - last_time;
    if (last_time != 0 && interval < time_interval_)
        usleep(interval);
    last_time += interval;
    
    return_code_ = curl_easy_perform(curl_handle_);
    if (return_code_ != CURLE_OK){
        FILE *fp = fopen(error_file_ . c_str(), "a+");
        fprintf(fp, "%50s: %s\n", curl_easy_strerror(return_code_), web_site . c_str());
        fclose(fp);
        return 1;
    }
    
    SaveFile(web_site, content);
    return 0;
}

Viewer :: ~Viewer(){
    curl_easy_cleanup(curl_handle_);
    curl_global_cleanup();
}
