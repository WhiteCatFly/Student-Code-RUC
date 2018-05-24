#ifndef DIGIT_H
#define DIGIT_H
#include "String.h"

class digit : public String{
	private:
	const String format,origin;
	int type, precision, widen, align;
	bool sign, zero, blank, decimal;
	int after_point, before_point;
	void initial();
	int extract(int front, int rear);
	void cnt_org();
	void transform(int type);
	void update_str(const String&);
	void add_space(int mode, int cnt);
	void add_zero(int mode, int cnt);
	void signs();
	void cutoff(int cnt);
	public:
	digit(const String& origin, const String& format);
	~digit(){};
};
#endif

