#include "String.h"
#include <cstring>
#include "digit.h"

int Int = 0,Double = 1,Right = 0,Left = 1;
char mark = '+', point = '.', line = '-', pound = '#', D = 'f', I = 'd';
String Zero("0"), Space(" "), plus("+"), dot(".");

int digit::extract(int front, int rear){
	int temp = 0;
	for(int i = front; i < rear; i++){
		if(isdigit(format[i])){
			if(format[i] == '0')
				zero = true;
			while(isdigit(format[i])){
				temp *= 10;
				temp += format[i] -'0';
				i++;
			}
			return temp;
		}
	}
}

void digit::initial(){
	precision = 6; widen = 0; align = Left;
	zero = false; sign = false; decimal = false;
	if(format.Find(line) != Npos)
		align = Right;
	if(format.Find(mark) != Npos)
		sign = true;
	if(format.Find(pound) != Npos)
		decimal = true;
	if(format.Find(' ') != Npos){
		blank = true; sign = true;
	}
	if(format.Find(I) != Npos){
		type = Int;
		widen = extract(0, format.length());
	}
	if(format.Find(D) != Npos){
		type = Double;
		if(format.Find(point) != Npos){
			int cur = format.Find(point);
			widen = extract(0, cur);
			precision = extract(cur, format.length());
		}
		else
			widen = extract(0, format.length());	
	}	
}

void digit::cnt_org(){
	if(origin.Find(point) == Npos){
		before_point = len;
	}
	else{
		int temp = origin.Find(point);
		before_point = temp;
		after_point = len - temp - 1;
	}
}

void digit::cutoff(int cnt){
	if(cnt <= 0)
	return;
	if(precision == 0)
	cnt++;
	len -= cnt;
	char *temp = new char[len + 1];
	strncpy(temp, str, len);
	temp[len] = '\0';
	delete [] str;
	str = new char[len + 1];
	strcpy(str, temp);
	delete [] temp;
}

void digit::update_str(const String& temp){
	delete [] str;
	str = new char[len + 1];
	strcpy(str, temp.str_());
	str[len] = '\0';
}

void digit::signs(){
	if(origin.Find(line) != Npos)
		return;
	if(origin.Find(mark) == Npos){	
		if(!sign)
			return;		
		len++;
		String temp(str);
		if(blank)
			temp = Space + temp;
		else
			temp = plus + temp;
		update_str(temp);
	}			
	else if(!sign || blank){
			len -= 1;
			String temp(str + 1);
			if(blank){
				temp = Space + temp;
				len++;
			}
			update_str(temp);
	}
}

void digit::add_space(int mode, int cnt){
	if(cnt <= 0)
	return;
	String space, temp(str);
	for(int i = 0; i < cnt; i++)
		space = Space + space;
	len += cnt;
	if(mode == Left)
		temp = space + temp;
	else
		temp = temp + space;
	update_str(temp);
}

void digit::add_zero(int mode, int cnt){
	if(cnt <= 0)
	return;
	String space, temp(str);
	for(int i = 0; i < cnt; i++)
		space = Zero + space;
	len += cnt;
	if(mode == Left)
		temp = space + temp;
	else
		temp = temp + space;
	update_str(temp);
}	
				
void digit::transform(int type){
	if(type == Double){
		cutoff(after_point - precision);
		if(origin.Find(point) == Npos && (precision || decimal)){
			String temp(str);
			temp = temp + dot;
			len++;
			update_str(temp);
		}
		add_zero(Right, precision - after_point);
		after_point = precision;
		signs();
		add_space(align, widen - after_point - before_point);
	}
	if(type == Int){
		signs();
		if(zero)
			add_zero(Left, widen - before_point);
		else
			add_space(align, widen - before_point);
	}
}

digit::digit(const String& origin, const String& format):String(origin), origin(origin), format(format){
	initial();
	cnt_org();
	transform(type);
}	
