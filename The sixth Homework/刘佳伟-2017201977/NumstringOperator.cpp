#include "Numstring.h"

using namespace std;

istream& operator>>(istream &input, Numstring &s0)
{
	int i = 0;
	bool allzero = true;
	
	if(s0.str != NULL)
		delete []s0.str;
	char *s1 = new char[32768];
	input >> s1;
	
	for(int i = 0; s1[i] != '\0'; i++)
		if(!(i == 0 && s1[i] == '-') && s1[i] != '0')
		{
			allzero = false;
			break;
		}
	
	if(allzero)
	{
		s0.len = 1;
		s0.str = new char[2];
		s0.str[0] = '0';
		s0.str[1] = '\0';
	}
	else
	{
		s0.len = strlen(s1);
		s0.str = new char[s0.len + 1];
		strcpy(s0.str, s1);
		s0.str[s0.len] = '\0';
	}
	
	delete []s1;
	
	for(; i < s0.len; i++)
		if(s0.str[i] == '.')
		{
			i++;
			break;
		}
	
	s0.floatdigit = s0.len - i;
	
	cout << "数据内部信息：" << s0.str << endl << s0.len << ' ' << s0.floatdigit << endl << endl;
	
	return input;
}
