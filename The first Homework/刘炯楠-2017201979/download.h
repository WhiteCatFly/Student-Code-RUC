#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <string>

#define SLEEP_LIMIT 50000
#ifndef MAXLEN
#define MAXLEN 200
#endif

using namespace std;

static void download_sleep();
void page_download(string web_page);
#endif
