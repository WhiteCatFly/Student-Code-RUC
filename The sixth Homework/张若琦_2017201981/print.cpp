#include <iostream>
#include "print.h"


// %[flags][width][.precision][length]specifier

// flag : - -> Left-justify
//        + -> preceed the result with a plus or minus sign
//        0 -> use 0 to pad instead of space
// can't find both {0, -}

// width : Minimum number of characters

// precision :
// %f : number of digits after '.' 
// %d : minimum number of digits

// 0 can be omitted

// construction & deconstruction
OString::OString(const char ch) :
	String(ch) {};

OString::OString(const char * s) :
	String(s) {};

OString::OString(const OString & st) :
	String(st) {};

OString::OString(const OString & st, size_t pos, size_t len) :
	String(st, pos, len) {};

OString::OString(const char * s, size_t n) :
	String(s, n) {};

OString::OString(size_t n, const char ch) :
	String(n, ch) {};

// function
bool OString::is_flag(const char * ptr) const
{
	return *ptr == '-' || *ptr == '+' || *ptr == '0';
}

bool OString::is_spec(const char * ptr) const
{
	return *ptr == 'd' || *ptr == 'f';
}

int OString::cal_len(char * ptr) const
{
	if (*ptr == '-' || *ptr == '+')
		ptr ++;
	char * src = ptr;
	for (; *src != '\0'; src ++)
		;
	return src - ptr;
}

void OString::print_int(int width, int prcs, bool sgn, bool lft_jst, bool zero) const
{
	char * ptr = const_cast<char *> (c_str());
	bool sgn_dig = sgn || *ptr == '-';
	int len_num = cal_len(ptr);
	if (prcs < len_num)
		prcs = len_num;
	if (width < prcs + sgn_dig)
		width = prcs + sgn_dig;

	if (zero)
	{
		if (sgn_dig)
			putchar(*ptr == '-' ? '-' : '+');
		if (*ptr == '-' || *ptr == '+')
			ptr ++;
		for (int i = 0; i < width - sgn_dig - len_num; i ++)
			putchar('0');
		for (; *ptr != '\0'; ptr ++)
			putchar(*ptr);
	}
	else
	{
		if (lft_jst)
		{
			if (sgn_dig)
				putchar(*ptr == '-' ? '-' : '+');
			if (*ptr == '-' || *ptr == '+')
				ptr ++;
			for (; *ptr != '\0'; ptr ++)
				putchar(*ptr);
			for (int i = 0; i < width - sgn_dig - len_num; i ++)
				putchar(' ');
		}
		else
		{
			for (int i = 0;i < width - sgn_dig - prcs; i ++)
				putchar(' ');
			if (sgn_dig)
				putchar(*ptr == '-' ? '-' : '+');
			if (*ptr == '-' || *ptr == '+')
				ptr ++;
			for (int i = 0;i < prcs - len_num; i ++)
				putchar('0');
			for (; *ptr != '\0'; ptr ++)
				putchar(*ptr);
		}
	}
}

char * OString::find_dot(char * ptr) const
{
	if (*ptr == '-' || *ptr == '+')
		ptr ++;
	char * src = ptr;
	for (; *src != 0 && *src != '.'; src ++)
		;
	return *src == 0 ? NULL : src;
}

bool OString::round(char * &ptr, char * &pdot, int prcs, int len_aft, char * tmp) const
{
	if (prcs >= len_aft)
		return false;

	if (*ptr == '-' || *ptr == '+') // copy
		*tmp = *ptr;
	*(tmp + (pdot - ptr)) = '.';

	char * lst = pdot + prcs;
	bool tag = *(lst + 1) >= '5';
	for (; lst > pdot; lst --) // aft
	{
		if (*lst == '9' && tag)
			*(tmp + (lst - ptr)) = '0';
		else
		{
			*(tmp + (lst - ptr)) = *lst + tag;
			tag = 0;
		}
	}
	char * rend = *ptr == '-' || *ptr == '+' ? ptr + 1 : ptr;
	for (lst = pdot - 1; lst >= rend; lst --)
	{
		if (*lst == '9' && tag)
			*(tmp + (lst - ptr)) = '0';
		else
		{
			*(tmp + (lst - ptr)) = *lst + tag;
			tag = 0;
		}
	}

	pdot = pdot - ptr + tmp;
	ptr = tmp;
	return tag;
}

void OString::print_float_flag(bool sgn_dig, char * &ptr) const
{
	if (sgn_dig)
		putchar(*ptr == '-' ? '-' : '+');
	if (*ptr == '-' || *ptr == '+')
		ptr ++;
}

void OString::print_float_bef(bool rd_up, char * pdot, char * ptr) const
{
	if (rd_up)
		putchar('1');
	else if (pdot != NULL && (pdot == ptr || *(pdot - 1) == '+' || *(pdot - 1) == '-'))
		putchar('0');
	for (; *ptr != 0 && *ptr != '.'; ptr ++)
		putchar(*ptr);
}

void OString::print_float_aft(int prcs, int len_aft, char * pdot) const
{
	if (prcs)
	{
		putchar('.');
		if (pdot == NULL)
		{
			for (int i = 0; i < prcs;i ++)
				putchar('0');
			return;
		}
		for (int i = 1; i <= len_aft && i <= prcs; i ++)
			putchar(*(pdot + i));
		for (int i = 0; i < prcs - len_aft; i ++)
			putchar('0');
	}
}

void OString::print_float(int width, int prcs, bool sgn, bool lft_jst, bool zero) const
{
	char * ptr = const_cast<char *> (c_str());
	bool sgn_dig = sgn || *ptr == '-';
	int len_num = cal_len(ptr);
	char * pdot = find_dot(ptr);
	int len_bef = pdot == NULL ? 0 : pdot - ptr - (*ptr == '-' || *ptr == '+');
	int len_aft = 0;
	if (len_bef == -1) // not found
		len_bef = len_num;
	else
		len_aft = len_num - len_bef - 1;
	if (len_bef == 0)
		len_bef = 1;

	char tmp[MAXN] = {0};
	bool rd_up = round(ptr, pdot, prcs, len_aft, tmp);

	if (width < prcs + (prcs > 0 ? 1 : 0) + len_bef + sgn_dig + rd_up)
		width = prcs + (prcs > 0 ? 1 : 0) + len_bef + sgn_dig + rd_up;

	int num_0 = width - (prcs + (prcs > 0 ? 1 : 0) + len_bef + sgn_dig + rd_up);
	if (zero)
	{
		print_float_flag(sgn_dig, ptr);

		for (int i = 0; i < num_0; i ++)
			putchar('0');
		
		print_float_bef(rd_up, pdot, ptr);
		print_float_aft(prcs, len_aft, pdot);
		
	}
	else if (lft_jst)
	{
		print_float_flag(sgn_dig, ptr);
		print_float_bef(rd_up, pdot, ptr);
		print_float_aft(prcs, len_aft, pdot);

		for (int i = 0; i < num_0; i ++)
			putchar(' ');
	}
	else
	{
		for (int i = 0; i < num_0; i ++)
			putchar(' ');

		print_float_flag(sgn_dig, ptr);
		print_float_bef(rd_up, pdot, ptr);
		print_float_aft(prcs, len_aft, pdot);
	}
}

void OString::print(const char * cntrl) const
{
	int width = 0, prcs = 0;
	bool block_flag = 0, flags = 1, dot = 0, lft_jst = 0, sgn = 0, zero = 0;

	for (; *cntrl != 0; cntrl ++)
	{
		if (block_flag)
		{
			if (flags && is_flag(cntrl))
			{
				switch (*cntrl)
				{
					case '+' : sgn = true; break;
					case '-' : lft_jst = true; break;
					case '0' : zero = true; break;
				}
				continue;
			}
			flags = 0;

			if (*cntrl == '.')
			{
				dot = 1;
			}
			else if (!is_spec(cntrl))
			{
				if (dot == 0)
					width = width * 10 + *cntrl - '0';
				else
					prcs = prcs * 10 + *cntrl - '0';
			}
			else
			{
				// std::cout << width << ' ' << prcs << ' ' << sgn << ' ' << lft_jst << ' ' << zero << " * ";
				if (*cntrl == 'd')
					print_int(width, prcs, sgn, lft_jst, zero);
				else
					print_float(width, prcs, sgn, lft_jst, zero);

				// clear()
				width = prcs = 0;
				block_flag = dot = sgn = zero = false;
				flags = 1;

			}
		}
		else
		{
			if (*cntrl == '%')
				block_flag = flags = true;
			else if (*cntrl == '\\')
			{
				cntrl ++;
				switch (*cntrl)
				{
					case 'n' : putchar('\n'); break;
					case 't' : putchar('\t'); break;
					default: putchar(*cntrl);
				}
			}
			else
				putchar(*cntrl);
		}
	}
}