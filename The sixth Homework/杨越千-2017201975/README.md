# DigitalString class

## usage

run ./dstring

## intro

初始化和string相同.

### string sprint(const string& str, int pos) const;

str支持识别"%d","%f","%lf"类型,可加入".(number)","-(number)"等参数

pos表示以dstring标号为pos的字符(从0开始)作为第一个字符.

对整型:

"%(number)d" 取number个字符,未取足时在前面补若干空格补到number,缺省时默认取到末尾.

"%.(number)d" 同上,未取足时在前面补若干0补到number,不能缺省.

"%(num1).(num2)d" 取num2个字符,不足补0,num1>num2时右对齐

"%-(num1).(num2)d" 同上,num1>num2时左对齐

对实型:

"%(num1).(num2)lf" 取num1个字符,保留到小数点后num2位,num1缺省时默认取到dstring末尾,num2缺省时默认6位.

详见main.cpp.

### int is(int pos) const;

返回dstring标号pos位上数字.
