#ifndef STRING_H_
#define STRING_H_
#include <iostream>
using std::ostream;
using std::istream;
class String{
	protected:
    char* str;             
    int len;    
    private:           
    static const int CINLIM = 1024;
	public:
	int Npos;
    String(const char* s); 
    String();               
    String(const String&); 
    virtual ~String();            
    int length() const { return len; } 
    char* str_() const { return str; }
    int Find(char t) const;
    int Find(char t, int cur) const;    
    String& operator=(const String&);
    String& operator=(const char*);
    String operator+(const String&)const;
    char& operator[](int i);
    const char& operator[](int i) const; 
    friend bool operator<(const String& st, const String& st2);
    friend bool operator>(const String& st1, const String& st2);
    friend bool operator==(const String& st, const String& st2);
    friend ostream& operator<<(ostream& os, const String& st);
    friend istream& operator>>(istream& is, String& st);
};
#endif
