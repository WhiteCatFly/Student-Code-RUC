#include "global_settings.cpp"
#include "Init.h"
#include "InputDeal.h"
#include "Search.h"
using namespace std;
vector <string> KeyWords;
map <string, Words> Mp;
vector <WebPage> WP;

bool SearchBody = true, rebuild = false;;
int ShowLines = 20;


int main(int argc, const char * argv[]) {
	for(int i = 1; i < argc; ++i) {
		int tp = CheckInput(argv[i]);
		if(tp == -1) InputWords( (string) argv[i], KeyWords);
		if(tp == 0) {
			++i;
			ShowLines = atoi(argv[i]);
			//SetShowLines(atoi(argv[i]), ShowLines);
		}
		if(tp == 1) {
			++i;
			string tmp = argv[i];
			SearchBody = (tmp == No);
			//SetSearchRange(tmp == Yes);
		}
		if(tp == 3) {
		    ++i;
		    string tmp = argv[i];
		    rebuild = (tmp == Yes);
		}
		    
	}
	if(rebuild)
	    ReBuild(Mp, WP);
	else
	    InitFromSave(Mp, WP);
	Search(KeyWords, Mp, WP, ShowLines, SearchBody);
	return 0;
}
	
