## ������ҵ:ʹ��THULAC��

### ƽ̨: ubuntu 16.04

### ʹ�÷���:

#### 1.����thulac��������ѵ���õ�ģ�Ͱ�,ģ�Ͱ���ѹ���models�ŵ���Ŀ¼

#### 2. ��Ŀ¼��make, �õ���ִ���ļ�thulac

#### 3. ./thulac -input inputfile -output outputfile

inputfile,outputfileΪ���롢����ļ���,ע��һ��Ҫ���������.

�õ��ִʡ����Ա�ע�������.

#### 4. �ӿ�ʹ��:��Ŀ¼����cpp:

#include "include/thulac.h"

##### ��ʼ��:

THULAC lac;

lac.init(...);

##### �ִ�&���Ա�ע:

lac.cut(std::string&, THULAC_result& result);

std::string& �Ǵ���������;

THULAC_result Ϊ std::vector<std::pair<std::string, std::string> > �ض���, pair.firstΪÿһ���ִ�, pair.secondΪ����.

����check.cpp ʵ��

## �߼���ҵ: CRF++�����д�

### ƽ̨: windows 10

### ʹ�÷���:

#### 1. ����CRF++ 0.58

#### 2. ./crf_learn template train model �õ�model

#### 2. ./crf_learn -m model test �õ��ִʽ��(B,S,E��ʽ)

����CRF++result
