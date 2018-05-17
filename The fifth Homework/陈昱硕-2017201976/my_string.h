#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstddef>
#include <cstring>

#include <iostream>

class MyString{
private:
    static const size_t kCinLimit_;
    static size_t number_of_strings_;
    size_t length_, size_;
    char *str_;

public:
    MyString();
    MyString(const char *str);
    MyString(const MyString &str);

    size_t length() const{return length_;}
    static size_t howmany(){return number_of_strings_;}
    char & operator [] (size_t idx){return str_[idx];}
    const char & operator [] (size_t idx) const{return str_[idx];}

    MyString & operator = (const MyString &str);
    MyString & operator += (const MyString &str);
    const MyString operator + (const MyString &str);

#define makeoper(op) \
    const bool operator op (const MyString &str) const{\
        return strcmp(str_, str.str_) op 0;\
    }
    makeoper(< )
    makeoper(<=)
    makeoper(> )
    makeoper(>=)
    makeoper(==)
    makeoper(!=)
#undef makeoper

    friend std :: istream & operator >> (std :: istream &is, MyString &str);
    friend std :: ostream & operator << (std :: ostream &os, const MyString &str);

    ~MyString();
};

#endif