#ifndef MYGOODSTRING_
#define MYGOODSTRING_


#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cstdio>
using namespace std;






class MyGoodString : public MyString {
	private:
		bool positive;
		bool negative;
		bool right ;
		bool space ;
		int len_plus;
		int len_tot;
	public:
		MyGoodString(const char * s);
		MyGoodString();
		MyGoodString(const MyGoodString & st);
		void print(MyGoodString & standard);
		int find(char flag , int pos_beg , int pos_end);
		MyGoodString & substr (const MyGoodString & st);
		
};


#endif
