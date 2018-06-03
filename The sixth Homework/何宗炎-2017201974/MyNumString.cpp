#ifndef MyNumString_HZY_CPP_
#define MyNumString_HZY_CPP_
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "MyNumString.h"


void Move(char * s, int tail, int new_tail) {
	for(int i = 0; i <= tail; ++i)
		s[new_tail - i] = s[tail - i];
	for(int i = new_tail - tail - 1; i >= 0; --i) s[i] = ' ';
}

MyString MyNumString::Standard(bool LRAlign, int width, int precision) {
	char * s = to_str();
	int slen = strlen(s), size = (slen > width ? slen : width) + precision + 1;
	char * tmp = new char[size];
	/*<-------------Open the Space----------->*/	
	int i = 0;
	while(i < slen && s[i] != '.') tmp[i] = s[i], i++;
	/*<------------Deal with integer----------->*/
	if(precision && s[i] == '.' && i + 1 != slen) {
		tmp[i] = s[i], ++i;
		int j;
		for(j = 1; j <= precision && i < slen; ++i, ++j)
			tmp[i] = s[i];
		for(; j <= precision; ++j) tmp[i++] = '0';
		char c = s[i];
		if(c >= '5' && c <= '9') {
			tmp[i - 1]++;
			for(j = i - 1; j > 0; --j)
				if(tmp[j] > '9') {
					tmp[j] -= 10;
					if(tmp[j - 1] == '.') j--;
					tmp[j - 1]++;
				}
				else break;
			if(tmp[0] > '9') {
				Move(tmp, i - 1, i);
				tmp[1] -= 10;
				tmp[0] = '1';
				i++;
			}
		}
	}
	/*<----------------Deal with decimals--------------->*/
	if(LRAlign && i < width) Move(tmp, i, width), i = width;
	else 
		for(;i < width; ++i) tmp[i] = ' ';
	/*<---------------left or right align-------------->*/
	tmp[i] = '\0';
	MyString temp(tmp);
	return temp;
}
					
#endif	
