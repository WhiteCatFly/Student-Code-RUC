#ifndef Search_Hzy_H_
#define Search_Hzy_H_
#include "global_settings.cpp"

void TF(std::string s, db * res, std::map <std::string, Words> & Mp, std::vector <WebPage> & WP, int ShowLines, bool SearchBody);

db IDF(std::string s, std::map <std::string, Words> & Mp, std::vector <WebPage> & WP, int ShowLines, bool SearchBody) ;

void Search(std::vector <std::string> & words, std::map <std::string, Words> & Mp, std::vector <WebPage> & WP, int ShowLines, bool SearchBody) ;

#endif
