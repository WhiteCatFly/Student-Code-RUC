#include "number_string.h"

#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

static const int NEGA = 0x1;
static const int PLUS = 0x2;
static const int SPACE = 0x4;
static const int ZERO = 0x8;

static int GetFlag(const char *fmt, int &begin, int end){
    int result = 0;
    bool in_flag = true;
    while (in_flag && begin != end){
        switch (fmt[begin]){
            case '-':
                result |= NEGA;
                break;
            case '+':
                result |= PLUS;
                break;
            case ' ':
                result |= SPACE;
                break;
            case '0':
                result |= ZERO;
                break;
            default:
                in_flag = false;
                break;
        }
        if (in_flag)
            begin ++;
    }
    return result;
}

static int GetDigit(const char *fmt, int &begin, int end){
    bool is_negative = false;
    if (fmt[begin] == '-'){
        is_negative = true;
        begin ++;
    }

    int result = 0;
    while (isdigit(fmt[begin]) && begin != end){
        result = result * 10 + (fmt[begin] - '0');
        begin ++;
    }
    return is_negative ? -result : result;
}

static int GetPrecision(const char *fmt, int &begin, int end, int dft){
    int precision = dft;
    if (fmt[begin] == '.'){
        begin ++;
        int res = GetDigit(fmt, begin, end);
        if (res >= 0)
            precision = res;
    }
    return precision;
}

static void FormatWithFlag(MyString &result, int flag, int width){
    if (flag & PLUS){
        if (result[0] != '-')
            result = "+" + result;
    }
    else if (flag & SPACE){
        if (result[0] != '-')
            result = " " + result;
    }

    MyString temp;
    if (flag & NEGA){
        for (int i = 0; i < width - (int)result.length(); i ++)
            temp.append(' ');
        result += temp;
    }
    else if (flag & ZERO){
        for (int i = 0; i < width - (int)result.length(); i ++)
            temp.append('0');
        result = temp + result;
    }
}

static bool is_carry(const MyString &res, int pos){
    if (pos >= (int)res.length() || res[pos] < '5')
        return false;
    if (res[pos] > '5')
        return true;
    for (int i = pos + 1; i < (int)res.length(); i ++)
        if (res[pos] != '0')
            return true;
    return false;
}

static void Round(MyString &res, int pos){
    bool carry = is_carry(res, pos);
    res.erase(res.begin() + pos);
    for (int i = pos - 1; i >= 0 && carry; i --){
        if (res[i] == '.')
            continue;
        if (carry){
            res[i] ++;
            carry = false;
        }
        if (res[i] > '9'){
            res[i] = '0';
            carry = true;
        }
    }
    if (carry)
        res = "1" + res;
}

MyString NumberString :: PrintDigit(const char *fmt, int begin, int end){
    int flag = GetFlag(fmt, begin, end);
    int width = GetDigit(fmt, begin, end);
    int precision = GetPrecision(fmt, begin, end, 0);

    char *point = find('.'), *beg = this -> begin();
    MyString result;
    for (int i = 0; i < precision - (int)(point - beg); i ++)
        result.append('0');
    result += this -> substr(beg, point - beg);

    FormatWithFlag(result, flag, width);
    return result;
}

MyString NumberString :: PrintFloat(const char *fmt, int begin, int end){
    int flag = GetFlag(fmt, begin, end);
    int width = GetDigit(fmt, begin, end);
    int precision = GetPrecision(fmt, begin, end, 6);

    MyString result(*this);
    char *point = find('.'), *ed = this -> end();
    if (point != ed)
        Round(result, (result.find('.') - result.begin()) + precision + 1);
    else
        result.append('.');
    for (int i = 0; i < precision - (int)(ed - point); i ++)
        result.append('0');

    FormatWithFlag(result, flag, width);
    return result;
}

MyString NumberString :: FormatOutput(const char *fmt){
    int length = strlen(fmt);

    if (fmt[0] != '%'){
        cerr << "Wrong format!" << endl;
        exit(1);
    }

    enum status{d, f} stat;
    int begin = 1, end;
    switch (fmt[length - 1]){
        case 'd':
            stat = d;
            end = length - 1;
            break;
        case 'f':
            stat = f;
            if (fmt[length - 2] == 'l')
                end = length - 2;
            else
                end = length - 1;
            break;
        default:
            cerr << "Wrong format!" << endl;
            exit(1);
    }

    return (stat == d) ? PrintDigit(fmt, begin, end) : PrintFloat(fmt, begin, end);
}