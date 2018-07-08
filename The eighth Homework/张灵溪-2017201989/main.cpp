#include "index_search.h"
#include "dictionary.h"

using namespace std;

int main(void){
	dictionary dic;
	index_search index(dic, 3);
	index.search("哥伦比亚大学");
	return 0;		
}
