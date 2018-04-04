#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <unistd.h>

//The Keyword List, Copyright CYS 2018
const char *forbidden_str[] = {"@", "#", "(", ")", "[", "]", "{", "}",
					".txt", ".doc", ".ppt", ".xls", ".pdf", ".PDF", "ftp://", "file://", "telnet://",
					".jpg", ".JPG", ".jpeg", ".JPEG", ".png", ".gif", ".bmp", ".rar", ".zip", ".7z", ".mp3", ".mp4", ".MP4",
					"javascript:void(0)", "javascript:;",
					".flv", ".wmv", ".avi", ".rmvb", ".mpeg", ".qt", ".mpg", ".mkv", ".rm",
					"twitter", "google", "facebook", "END_OF_FORBIDDEN_STRING"};

const char END_OFS[] = "END_OF_FORBIDDEN_STRING";

std::string UrlProcess(const std::string &FatherUrl, std::string url);
std::string UrlToDirectory(const std::string &url);
std::string UrlToFile(const std::string &url);
