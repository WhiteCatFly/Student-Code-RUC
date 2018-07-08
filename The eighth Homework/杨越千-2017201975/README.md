# Naive RucInfoSearch

this is a naive RucInfoSearchEngine.(on terminal, ubuntu)

environment: ubuntu 16.04 (64-bit)

由于data文件夹和thulac文件夹太大(约500M)没有上传到github, 仅上传include和programs文件夹,分别存放.h和.cpp文件.

data文件夹和陈大佬的一样,内部为download文件夹和file_list.txt,搜索引擎初始化时按file_list.txt找.

thulac文件夹含model.

## usage

```
make
```

得到可执行文件se.

若是首次使用,读入data内的数据初始化:

```
./se init
```

完成后会显示"find:",直接输入查询词后回车即可,默认查看前10个结果.

不是首次使用:

```
./se
```

完成后同上.