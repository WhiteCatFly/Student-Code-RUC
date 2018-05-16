#ifndef DOWNLOAD_H_INCLUDED
#define DOWNLOAD_H_INCLUDED

#include <string>

const double SLEEP_LIMIT = 0.05;
#ifndef MAXLEN_
#define MAXLEN_
const int MAXLEN = 200;
#endif


inline static void download_sleep(const double utime = SLEEP_LIMIT);
void page_download(const std::string & web_page);
#endif
