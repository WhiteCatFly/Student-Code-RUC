#include "CWSPOS.h"

using namespace std;

void CWSPOS::dp_CWS(int i)
{
	if(vis[i])
		return;
	
	vis[i] = true;
	
	if(i >= sentence.size())
	{
		f[i] = 0.0;
		return;
	}
	
	f[i] = log(alltimes) * (sentence.size() - i);
	for(int j = i; j < sentence.size(); j++)
	{
		dp_CWS(j + 1);
		double p;
		if(!dictionary.count(sentence.substr(i, j - i + 1)))
			p = log(alltimes) * (j - i + 1) + f[j + 1];
		else
			p = log(alltimes) - log(dictionary[sentence.substr(i, j - i + 1)].times) + f[j + 1];
		if(p < f[i])
		{
			f[i] = p;
			choice[i] = j;				
		}
	}
}

vector<string> CWSPOS::GetCWS()
{
	if(!vis[0])
		dp_CWS(0);
	
	int x = 0;
	while(x < sentence.size())
	{
		CWS.push_back(sentence.substr(x, choice[x] - x + 1));
		x = choice[x] + 1;
	}
	
	return CWS;
}
