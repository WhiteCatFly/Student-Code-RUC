#include "../THULAC/include/thulac.h"
#include <iostream>
#include <string>
using namespace std;
int main(void){
	char* model_path = "../THULAC/models";
	char* user_path = NULL;
	char separator = '_';
	int just_seg = 0;
	int ufilter = 0;
	int t2s = 0;
	
	string test_sent = "我爱天安门";
	THULAC test;	
	THULAC_result ans;
	test.init(model_path, user_path, just_seg, t2s, ufilter, separator);
	test.cut(test_sent, ans);
	
	for(int i=0;i<ans.size();i++){
		cout<<ans[i].first<<ans[i].second<<" ";
	}
	
	return 0;
}
