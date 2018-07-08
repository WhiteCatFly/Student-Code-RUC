#include <iostream>
#include <cstring>
#include <sstream>
#include "String.h"
#include "Stringout.h"


using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

bool is_flag(char s)
{
	if(s == '0' || s == '#' || s == '-' ) return true;
	return false;	
}
bool is_sign(char s)
{
	if(s == '+') return true;
	return false;	
}
bool is_tag(char s)
{
	if(s != '%') return false;
	else return true;
}
Stringout::Stringout(const char *s, const char fl, const int wid, const int si, const int prec, const char ty) : String(s)
{
	flag = fl;
	width = wid;
	sign = si;
	precision = prec;
	type = ty;
}

Stringout::Stringout(const String &st, const char fl, const int wid, const int si, const int prec, const char ty) : String(st)
{
	flag = fl;
	width = wid;
	sign = si;
	precision = prec;
	type = ty;
}
Stringout::Stringout(const String &format, const String &st) : String(st)
{
		int pos = 0;
		sign = 0;
		if(!is_tag(format[0]))
		{
			cout<<"Wrong format input!"<<std::endl;
			return;			
		}
		
		flag = ' ';
		for(int i = 1; ; i++)
		{
			if(!is_sign(format[i]) && !is_flag(format[i])) 
			{
				pos=i;
				break;	
			}
			else 
			{
				if(is_flag(format[i])) flag = format[i];
				if(is_sign(format[i])) sign = 1;
			}
		}
		int pos_dot = 0;
		type = 'f';
		for(int i = pos; i < format.length(); i++)
		{
			if(format[i] == 'd') 
			{
				type = 'd';
				break;
			}
			if(format[i] == '.') pos_dot = i;
		}
		width = 0;
		precision = 0;
		
		if(type == 'd') pos_dot = format.length() - 1;
		for(int i = pos; i < pos_dot; i++ )
			width = width * 10 + (format[i]-'0');	
		
		for(int i = pos_dot+1; i < format.length() - 2; i++)
			precision = precision * 10 + (format[i] - '0');
		if(format[format.length()-3] == '.' && !precision) precision = 6;
}

String & Stringout::display()
{

	char * s = new char [1025];
	strcpy(s,str);

	delete [] str;	
	if(type == 'd')
	{
		if(sign && s[0] != '-') width--;
		if(width <= len) 	width = len;
		str = new char [width+1];	
		int pos = 0;
 		if(flag == ' ' || flag == '0')
		{
			for(int i = 0; i < width - len; i++ )
				str[i] = flag;		
		 pos = width - len;
		}
		if(sign && s[0] != '-') 
		{
			str[pos] = '+';
			pos ++;
		}
		for(int i = 0; i < len; i++)
		{
			str[pos] = s[i];	
			pos++;
		}
		if(flag == '-')
		for(int i = 0; i < width-len; i++)
		{
			str[pos] = ' ';
			pos++;	
		}
		str[pos] = '\0';
	}

	else 
	{
		int plus = 0;
		int pos_dot = -1;
		for(int i = 0; i < len; i ++)
			if(s[i] == '.')
				pos_dot = i;
		char first[1024];
		char last[1024];
		if(pos_dot ==-1) 
		for(int i = 0; i < precision; i++)
		{
			last[i] = '0';	
		}
		else 
		{
			for(int i = 0; i < precision; i++)
			{
				if(i+pos_dot+1<len)
				last[i] = s[i+pos_dot+1];
				else last[i] = '0';	
			}
			if(precision+pos_dot+1<len && s[precision+pos_dot+1] >= '5')
			{
				plus = 1;
				for(int i = precision-1; i >= 0; i--)
				{
					int now = last[i] - '0' + plus;
					if(now < 10)
					{
						last[i] = now + '0';
						plus = 0;
						break;	
					}
					else 
						last[i] = now - 10 + '0';	
				}
			}
		}
		

		if(pos_dot == -1) pos_dot = len;
		if(sign && s[0] == '-') sign = 2;
		if(sign && s[0] != '-') sign = 1;
		 
		int pos = 0;
		
		if(sign ==2) pos++;
		int k = 0;
		for(int i = pos; i < pos_dot; i++)
		{
			
			first[i] = s[i];		
			k++;	
		}
		if(plus)
		{
			for(int i = k-1; i >=0; i--)
			{
				int now = first[i] - '0' + plus;
				if(now < 10)
				{
					first[i] = now + '0';
					plus = 0;
					break;	
				}
				else 
					first[i] = now - 10 + '0';	
			}
		}
		pos = 0;
		char real_first[1024];
		if(flag == ' ' || flag == '0')
		{
			
			for(int i = 0; i < width - (precision) - (sign == 1) - (precision != 0) - k - plus; i++ )
			{
				real_first[pos] = flag;
				pos++;	
			}
		}
		if(sign == 1)
		{
			real_first[pos] = '+';
			pos++;	
		}
		else if(sign == 2)
		{
			real_first[pos] = '-';
			pos++;	
		}
		if(plus)
		{
			real_first[pos] = '1';
			pos++;	
		}
		for(int i = 0; i < k; i++)
		{
			real_first[pos] = first[i];
			pos++;	
		}
		if(precision)
		{
			real_first[pos] = '.';
			pos++;	
		}
		if(width <= pos + precision) width = pos + precision;
		str = new char [width];	
		for(int i = 0; i < pos; i++)
		str[i] = real_first[i];
		for(int i = 0; i < precision; i++)
		str[pos++] = last[i];
		if(flag == '-')
		for(int i = pos; i < width; i++)
		{
			str[pos] = ' ';
			pos++;	
		}
		
		str[pos] = '\0';
	}
	
	delete [] s;
	len = width;
	return *this;
}
