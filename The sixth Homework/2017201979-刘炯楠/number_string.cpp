#include <cctype>
#include "String.h"
#include "number_string.h"

using namespace std;

char * initialize(char * number) {
	mp[plus_sign] = 1;
	mp[minus_sign] = 2;
	mp[space_sign] = 3;
	mp[zero] = 4;
	mp[pound_sign] = 5; 
	//char * normal_number = new char [max_number_len];
	String init_string(number);
	bool flag = false;
	if (number[0] == plus_sign) {
		init_string = init_string.substr(1);
	}
	if (number[0] == minus_sign) {
		flag = true;
		init_string = init_string.substr(1);
	}
	
	while (init_string[0] == zero)
		init_string = init_string.substr(1);
		
	if (init_string.find('.') == String::npos) {
		init_string = init_string + dot + zero;
	}
	else {
		if (init_string.find(dot) == 0) {
			init_string = zero + init_string;
		}
	}
	
	if (flag == true)
		init_string = minus_sign + init_string;
	
	int length = init_string.length();
	for (int i = length; i < max_number_len; ++i) {
		init_string = init_string + zero;
	}
	return init_string.c_str();
}

number_string::number_string() : String() {
}

number_string::number_string(char * number) : String(number) {
	dot_plc = find(dot);	
}

number_string::number_string(const String & number) : String(number) {
	dot_plc = find(dot);
}

number_string::~number_string() {
}

int number_string::ret_dot_plc() const {
	return dot_plc;
}
number_string number_string::turn_to_int() const {
	return number_string(substr(0, dot_plc));
}

number_string number_string::round_in_n(int n) const {
	String str = substr(0, dot_plc + n + (n != 0));
	char digit = (*this)[dot_plc + n + 1];
	if (digit <= four) {
		return number_string(str);
	}
	if (digit >= five) {
		int len = str.length();
		bool carry = true;
		for (int i = len - 1; i >= 0; --i) {
			if (str[i] == dot)
				continue;
			if (str[i] < nine) {
				str[i] = str[i] + 1;
				carry = false;
				break;
			}
			else {
				str[i] = zero;
				carry = 1;
			}
		}
		if (carry == 1)
			str = one + str;
	}
	return number_string(str);
}


//sign 
//+ - space 0 #
//+ 強制符號
//- 改爲左對齊
//0 前面加零
//space 正數前面多個空格
//# 強制輸出小數點（default .0f無小數點）

//width

//precision
//.x 
//int equal to　0xd but strong than it
//float round_to_n(x)

number_string & number_string::operator = (const number_string & temp) {
	if (this == &temp)
		return *this;
	String::operator = (temp);
	dot_plc = temp.dot_plc;
	return *this;
}

number_string number_string::normalize_width(int sign, int width) const{
	number_string temp;
	temp = (*this);
	int len = length();
	if (len < width) {
		if (sign & (1 << mp[minus_sign])) {
			for (int i = len + 1; i <= width; ++i)
				temp = temp + space_sign;
		}
		else {
			if ((sign & (1 << mp[zero])) == 0) {
				for (int i = len + 1; i <= width; ++i)
					temp = space_sign + temp;
			}
		}
	}
	return temp;
	
}

number_string number_string::normalize_sign() const{
	number_string temp;
	temp = (*this);
	if (temp[0] == minus_sign && length() == 2 && temp[1] == zero)
		temp = temp.substr(1);
	return temp;
}

static int get_sign(char * & format, int & next) {
	int format_len = strlen(format);
	int sign = 0;
	map<char,int>::iterator it;
	it = mp.find(format[next]);
	while (it != mp.end()) {
		sign = sign | (1 << (it -> second));
		if ((sign & (1 << mp[minus_sign])) && (format[next] == zero))
			sign = sign - (1 << (it -> second));
		next++;
		it = mp.find(format[next]);
	}
	return sign;
}

static int get_width(char * & format, int & next) {
	int format_len = strlen(format);
	int width = 0;
	for (; next < format_len && isdigit(format[next]) == true; ++next)
		width = width * 10 + format[next] - '0';
	return width;
}

static int get_precision(char * & format, int & sign, int opt, int & next) {
	int format_len = strlen(format);
	int precision = 0;
	if (opt == 1) precision = default_precision;
	if (format[next] == dot) {
		if ((sign & (1 << mp[zero])) && opt == 0) 
			sign = sign - (1 << mp[zero]);
		next++;
		precision = 0;
		for (; next < format_len && isdigit(format[next]) == true; ++next)
			precision = precision * 10 + format[next] - '0';
	}
	return precision;
}

number_string number_string::normalize(char * & format) const {
	int format_len = strlen(format);
	int next = 1;
	
	int sign = get_sign(format,next);
	int width = get_width(format,next);
	int opt = (format[format_len - 1] == float_sign);
	int precision = get_precision(format,sign,opt,next);
	
	number_string number;
	if (opt == 0) {
		number = this -> turn_to_int();
		number = number.normalize_sign();
	}
	else 
		number = this -> round_in_n(precision);

	bool minus_flag = false;
	if (number[0] == minus_sign) {
		number = number.substr(1);
		minus_flag = true;
	}
	
	if (opt == 0) {
		int len = number.length();
		for (int i = len + 1; i <= precision; ++i) {
			number = zero + number;
		}
	}
	if (opt == 1) {
		if ((sign & (1 << mp[pound_sign])) && (precision == 0)) {
			number = number + dot;
		}
	}
	
	int len = number.length();
	if ((sign & (1 << mp[plus_sign])) || (sign & (1 << mp[space_sign])))
		len++;
	if (sign & (1 << mp[zero])) {
		for (int i = len + 1; i <= width; ++i) 
			number = zero + number;
	}
	
	if (minus_flag == false) {
		if (sign & (1 << mp[plus_sign]))
			number = plus_sign + number;
		if (sign & (1 << mp[space_sign]))
			number = space_sign + number;
	}
	else 
		number = minus_sign + number;
	//cout<<number<<endl;
	//cout<<number.ret_dot_plc()<<endl;
		
	number = number.normalize_width(sign, width);
	
	//cout<<number<<endl;
	//cout<<number.ret_dot_plc()<<endl;
	
	return number;
}

