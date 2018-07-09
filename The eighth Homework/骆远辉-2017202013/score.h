#ifndef _SCORE_
#define _SCORE_

#include"index.h"
#include"document.h"

void answer(const string& query,int topk);
double cal_tf(int );
void output(map<int,double>&,int topk);


#endif
