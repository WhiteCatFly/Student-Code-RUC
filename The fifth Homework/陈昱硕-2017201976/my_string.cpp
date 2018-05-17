#include "my_string.h"

#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

const size_t MyString :: kCinLimit_ = 100;
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

const MyString MyString :: operator + (const MyString &str){
    MyString ans(*this);
    ans += str;
    return ans;
}

istream & operator >> (istream &is, MyString &str){
    char temp[MyString :: kCinLimit_];
    is.get(temp, MyString :: kCinLimit_);
    if (is)
        str = temp;
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