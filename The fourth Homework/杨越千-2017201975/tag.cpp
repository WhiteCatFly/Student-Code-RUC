#include "htmlparser.h"
using namespace std;

bool Tag::operator ==(const Tag& tg) const
{
	if(_fa == tg._fa && _pre == tg._pre && _nxt == tg._nxt && _son == tg._son && url == tg.url) return 1;
	else return 0;
}

bool Tag::operator !=(const Tag& tg) const {return !(*this == tg); }
