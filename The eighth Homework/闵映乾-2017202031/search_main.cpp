#include "search_engine.h"

int main(){
	Rucsearch engine;
	string ask;
	cin >> ask;
	engine.input_form();
	engine.query_cut(ask);
	engine.search_score();
	engine.topk(5);
	

	
	return 0;
}
