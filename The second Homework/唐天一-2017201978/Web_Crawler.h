#include <set>
#include <queue>
#include <string>

const std::string sensitive_words[100]={".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", ".bmp", ".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", "str = str+", "$", "words_end"};

void get_html(const std::string &current_url, std::string &current_html, const int total);

void find_next_url(const std::string &current_url, const std::string &current_html, std::queue<std::string> &url_queue, std::set<std::string> &url_set, const std::string &origin);

void Web_Crawler_BFS(const char* crawled_web);
