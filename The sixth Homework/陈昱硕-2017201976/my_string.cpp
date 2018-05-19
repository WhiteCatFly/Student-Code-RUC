#include "my_string.h"

#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

const size_t MyString :: kCinLimit_ = 1025;
size_t MyString :: number_of_strings_ = 0;

MyString :: MyString() : length_(0), size_(16), str_(new char [size_]){
    number_of_strings_ ++;
}

MyString :: MyString(const char *str){
    length_ = strlen(str);
    size_ = length_ + 1;
    str_ = new char [size_];
    strcpy(str_, str);
    number_of_strings_ ++;
}

MyString :: MyString(const MyString &str) :
    length_(str.length_), size_(str.size_), str_(new char [size_])
{
    strcpy(str_, str.str_);
    number_of_strings_ ++;
}

MyString & MyString :: operator = (const MyString &str){
    if (this == &str)
        return *this;
    length_ = str.length_;
    size_ = str.size_;
    delete [] str_;
    str_ = new char [size_];
    strcpy(str_, str.str_);
    return *this;
}

MyString & MyString :: operator += (const MyString &str){
    char *ptr = new char [size_ + str.size_];
    strcpy(ptr, str_);
    strcpy(ptr + length_, str.str_);
    size_ += str.size_;
    length_ += str.length_;
    delete [] str_;
    str_ = ptr;
    return *this;
}

const MyString operator + (const MyString &s1, const MyString &s2){
    MyString ans(s1);
    ans += s2;
    return ans;
}

void MyString :: append(char ch){
    if (++ length_ == size_){
        size_ <<= 1;
        char *ptr = new char [size_];
        strcpy(ptr, str_);
        delete [] str_;
        str_ = ptr;
    }
    str_[length_ - 1] = ch;
    str_[length_] = '\0';
}

char * MyString :: find(char ch){
    char *ptr = str_;
    for (;*ptr != ch && ptr != end(); ptr ++)
        ;
    return ptr;
}

void MyString :: erase(char *beg, char *ed){
    if (beg >= end() || beg >= ed)
        return;
    char *ender = end();
    char *p1 = beg, *p2 = ed;
    while (p2 != ender)
        *p1++ = *p2++;
    *p1 = '\0';
    length_ -= (ed - beg);
}

istream & operator >> (istream &is, MyString &str){
    char *temp = new char[MyString :: kCinLimit_];
    is.get(temp, MyString :: kCinLimit_);
    if (is)
        str = temp;
    delete [] temp;
    while (is && is.get() != '\n')
        ;
    return is;
}

ostream & operator << (ostream &os, const MyString &str){
    os << str.str_;
    return os;
}

MyString :: ~MyString(){
    delete [] str_;
    number_of_strings_ --;
}