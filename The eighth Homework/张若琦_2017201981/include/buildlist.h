#ifndef buildlist_H_
#define buildlist_H_

#include <string>
#include <map>

using std::string;

static const int MAXW = 60000;
static const int MAXL = 10 * MAXW + 10 * 2900000;

void DisposeDocumentPart(string filename, int DocID, int & totalwords, int & words,
                         std::map<string, int> * pdict, int ratio);
void DisposeDocument(string filename, int DocID, int & totalwords);
void buildlist();
void MakeListFile(int);

#endif // buildlist_H_