#ifndef LoadDict_H_
#define LoadDict_H_

#include <string>
#include <vector>

static const int MAXD = 7000;

typedef std::pair<int, double> pii;

void GetDictionary(std::string * pdictionary, std::vector<pii> * plist, int & totalwords);
void GetUrlList(std::string * purl, int & totalfiles);

#endif // LoadDict_H_