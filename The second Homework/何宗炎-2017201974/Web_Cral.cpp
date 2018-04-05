#ifndef Web_Cral_Hzy_CPP_
#define Web_Cral_Hzy_CPP_

#include "Web_Cral.h"
#include "global_setting.h"
#include "Hzydef.h"


string GetFileName(string s)
{
	int n = s.size(), i; string Name("");
	if(s[n - 1] == '/') s.erase(n - 1, 1), n--;
	if(n == 0) Name = HostName;
	else
		{
			for(i = n - 1; i >= 0; --i) if(s[i] == '/') break;
			for(++i; i < n; ++i) Name += s[i];
		}
	return Name;
}

void Cral_Web(string s)
{
	static clock_t pre = clock();
	while(clock() - pre < time_interval);
	pre = clock();
	system((Ins + GetFileName(s) + " " + Base_Site + "/" + s).c_str());
}

#else
#endif
