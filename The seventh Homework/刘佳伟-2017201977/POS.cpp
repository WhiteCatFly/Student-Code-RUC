#include "CWSPOS.h"

using namespace std;

int CWSPOS::GetTypeTimes(string &word, int t)
{
	if(dictionary.count(word))
		return dictionary[word].type_times[t];
	return 0;
}

void CWSPOS::dp_POS(int i, int j)
{
	if(vis2[i][j])
		return;
	
	vis2[i][j] = true;
	
	if(i >= CWS.size())
	{
		f2[i][j] = 0.0;
		return;
	}
	
	if(i == 0)
	{
		if(dictionary.count(CWS[i]))
		{
			int maxi = 0;
			int maxi_k = 0;
			for(int k = 1; k <= type_n; k++)
				if(GetTypeTimes(CWS[i], k) > maxi)
				{
					maxi = GetTypeTimes(CWS[i], k);
					maxi_k = k;
				}
			dp_POS(i + 1, maxi_k);
			f2[i][j] = log(dictionary[CWS[i]].times) - log(GetTypeTimes(CWS[i], maxi_k)) + f2[i + 1][maxi_k];
			choice2[i][j] = maxi_k;
		}
		else
		{
			dp_POS(i + 1, 33);
			f2[i][j] = log(type_alltimes[0]) + f2[i + 1][33];
			choice2[i][j] = 33;
		}
		return;
	}
	
	f2[i][j] = CWS.size() * log(type_alltimes[0]);
	
	if(dictionary.count(CWS[i]))
	{
		for(int k = 1; k <= type_n; k++)
		{
			dp_POS(i + 1, k);
			double p;
			if(GetTypeTimes(CWS[i], k) > 0 && type_mat[j][k] > 0)
				p = log(type_alltimes[j]) - log(type_mat[j][k]) + log(dictionary[CWS[i]].times) - log(GetTypeTimes(CWS[i], k)) + f2[i + 1][k];
			else
				p = log(type_alltimes[j]) + log(dictionary[CWS[i]].times) + f2[i + 1][k];
			if(p < f2[i][j])
			{
				f2[i][j] = p;
				choice2[i][j] = k;
			}
		}
	}
	else
	{
		dp_POS(i + 1, 33);
		if(type_mat[j][33] > 0)
			f2[i][j] = log(type_alltimes[j]) - log(type_mat[j][33]) + f2[i + 1][33];
		else
			f2[i][j] = log(type_alltimes[j]) + log(type_alltimes[0]) + f2[i + 1][33];
		choice2[i][j] = 33;
	}
}

vector<string> CWSPOS::GetPOS()
{
	if(!vis2[0][0])
		dp_POS(0, 0);
	
	int x = 0;
	for(int i = 0; i < CWS.size(); i++)
	{
		POS.push_back(type[choice2[i][x]]);
		x = choice2[i][x];
	}
	
	return POS;
}
