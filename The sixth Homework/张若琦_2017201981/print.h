#ifndef PRINT_ZRQ_H_
#define PRINT_ZRQ_H_

#include "String.h"

class OString : public String
{
private:
	static const size_t MAXN = 1024 + 5;
	bool is_flag(const char * ptr) const;
	bool is_spec(const char * ptr) const;
	int cal_len(char * ptr) const;
	void print_int(int width, int prcs, bool sgn, bool lft_jst, bool zero) const;
	
	char * find_dot(char * ptr) const;
	bool round(char * &ptr, char * &pdot, int prcs, int len_aft, char * tmp) const;
	void print_float_flag(bool sgn_dig, char * &ptr) const;
	void print_float_bef(bool rd_up, char * pdot, char * ptr) const;
	void print_float_aft(int prcs, int len_aft, char * pdot) const;
	void print_float(int width, int prcs, bool sgn, bool lft_jst, bool zero) const;

public:
	OString(const char ch);
	OString(const char * s);
	OString(const OString & st);
	OString(const OString & st, size_t pos, size_t len = npos);
	OString(const char * s, size_t n);
	OString(size_t n, const char ch);
	~OString() {};

	void print(const char * cntrl) const;
};

#endif // PRINT_ZRQ_H_