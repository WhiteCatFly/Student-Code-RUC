#ifndef VIEW_SOURCE_H
#define VIEW_SOURCE_H

#include <string>

using namespace std;

#ifdef VIEW_SOURCE_CPP
static const string save_directory = string("/media/workspace/download from www.ruc.edu.cn/");
#endif

void InitViewer();
char *Download(const char *filename);
void CloseViewer();

#endif
