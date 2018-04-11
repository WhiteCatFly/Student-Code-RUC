# spider
## intro

this is a simple RUC crawler

## usage

1.<br>
在当前目录下运行 <br>
make <br>
在当前目录下得到spider <br>
./spider url dom time <br>

[url] is the web's url that you want to crawl first (default: http://www.ruc.edu.cn) <br>

[dom] is such limitation that it should be included in each url the spider crawl (default: ruc.edu.cn ) <br>

[time] shows crawling frequency: crawl 10 webs / sleep [time] (microsecond) (default: 500000 (0.5s)) <br> 

note: you should omit arguments from right to left orderly, or it will get error <br>

然后在当前目录下会按建多级目录的形式生成爬取的网页.<br>

2.<br>
提供了一个爬虫类: spider.h <br>
Needed: spider.cpp bfs.cpp findurl.cpp set.cpp <br>
You can set: main.cpp <br>

## others

default download web: index.html

查看当前默认index方法: ask_index()

修改当前默认index方法: set_index(string)
