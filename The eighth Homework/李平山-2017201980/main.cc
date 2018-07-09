#include "query.h"
#include "inforetrieval.h"



int main()
{
	read();
	build();
	Query Q(5);
	Q.init();
	Q.cal_score();
	Q.sort_k();
}
