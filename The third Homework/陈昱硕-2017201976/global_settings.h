#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <string>
#include <vector>

using std :: string;
using std :: vector;

enum eRuninngMode{Restart, Load};

void HelpMessage();
void SetArray(const string &keys, vector<string> &array);
void SetValue(int &value, const string &key);
void NormalizeSeed(vector<string> &seed);

#endif
