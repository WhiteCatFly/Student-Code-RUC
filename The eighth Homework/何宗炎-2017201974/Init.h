#ifndef Init_Hzy_H_
#define Init_Hzy_H_
#include "global_settings.cpp"
#include <cstring>
#include <set>
#include <map>
#include <vector>
void ReBuild(std::map <std::string, Words> & Mp, std::vector <WebPage> & WP) ;
void InitFromSave(std::map <std::string, Words> & Mp, std::vector <WebPage> & WP) ;
void SaveData(std::map <std::string, Words> & Mp, std::vector <WebPage> & WP) ;

#endif
