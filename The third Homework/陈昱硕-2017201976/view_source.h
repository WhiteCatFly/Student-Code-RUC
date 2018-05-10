#ifndef VIEW_SOURCE_H
#define VIEW_SOURCE_H

#include <curl/curl.h>

#include <cstdio>

#include <string>

using std :: string;

class Viewer{
    private :
        static const int kMaxFileLength = 10000000;
        static const int kMaxFileNameLength = 240;
        static const int kDNSCacheTimeout = 120000;
        
        CURL *curl_handle_;
        CURLcode return_code_;
        
        string error_file_;
        string save_directory_;
        
        int timeout_time_;
        int time_interval_;
        
        static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
        char *Normalize(const string &web_site, const string &content);
        void SaveFile(const string &web_site, const string &buffer);
        
    public :
        int Download(const string &web_site, string &content);
        
        Viewer(const string &error_file,
               const string &save_directory,
               const int &timeout_time,
               const int &time_interval);
        
        ~Viewer();
};

#endif
