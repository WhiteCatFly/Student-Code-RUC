#ifndef FILTER_H
#define FILTER_H

#include <string>

using std :: string;

#ifdef FILTER_CPP
const char *forbidden_string[] = {"@", "#", "(", ")", "[", "]", "{", "}",
					".txt", ".doc", ".ppt", ".xls", ".XLS", ".pdf", ".PDF", "ftp://", "file://", "telnet://",
					".jpg", ".JPG", ".jpeg", ".png", ".gif", ".bmp", ".rar", ".zip", ".7z", ".mp3", ".MP3", ".mp4", ".MP4",
					"javascript:void(0)", "javascript:;",
					".flv", ".wmv", ".avi", ".rmvb", ".mpeg", ".qt", ".mpg", ".mkv", ".rm",
					"twitter", "google", "facebook", "END"};
const char space_char[] = "\t" "\f" "\v" "\n" "\r" " ";
#endif

void SetPage(std :: string *web_site, std :: string *page_content);
string *GetNextUrl();

#endif
