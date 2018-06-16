## 基本作业:使用THULAC库

### 平台: ubuntu 16.04

### 使用方法:

#### 1.下载thulac包和事先训练好的模型包,模型包解压后把models放到根目录

#### 2. 根目录下make, 得到可执行文件thulac

#### 3. ./thulac -input inputfile -output outputfile

inputfile,outputfile为输入、输出文件名,注意一定要是这个名字.

得到分词、词性标注后的语料.

#### 4. 接口使用:根目录建立cpp:

#include "include/thulac.h"

##### 初始化:

THULAC lac;

lac.init(...);

##### 分词&词性标注:

lac.cut(std::string&, THULAC_result& result);

std::string& 是待处理语料;

THULAC_result 为 std::vector<std::pair<std::string, std::string> > 重定义, pair.first为每一个分词, pair.second为词性.

附：check.cpp 实例

## 高级作业: CRF++中文切词

### 平台: windows 10

### 使用方法:

#### 1. 下载CRF++ 0.58

#### 2. ./crf_learn template train model 得到model

#### 2. ./crf_learn -m model test 得到分词结果(B,S,E形式)

附：CRF++result
