# htmlparser
## intro

this is a simple htmlparser

author: yyq

特点: 使用了HtmlParser类和Tag类,并基于XML标准建立了标签树;
	  使用了正则表达式(可见consts.h)

## environment

linux (tested in ubuntu 16.04)

## general usage

1.在当前目录下运行make得到可执行文件htmlparser

```
make
```

2.在htmlparser.in里输入三个参数(第三个可省略):

[html] 本地待解析文件(html/php/...)

[dom] 待解析文件对应的主站url(如http://www.baidu.com, http://info.ruc.edu.cn)

[mode] (default mode = 0)

	   mode = 0 : HtmlParser类使用ifstream读入
	   
	   mode = 1 : HtmlParser类使用stringstream读入
	   
	   具体实现方法可见main.cpp

3.运行./htmlparser (出现error: XXX是正常现象)

```
./htmlparser
```

  控制台会输出该文件的title, 爬取link, image, sound, word的数量, 其中link 表示url链接, image表示图片, sound表示音频, word表示各类常用文件(word,pdf...),

  并在当前目录下建立四个子文件夹:link, image, sound, word,分别存储以上四种文件.

## how to test

   针对四种提取方法提供了三个实例:

   1.测试image:
   
     在htmlparser.in输入

		academic_faculty.php http://info.ruc.edu.cn

   2.测试sound:

	 在htmlparser.in输入

		sope.html http://sope.ruc.edu.cn

   3.测试word:

	 在htmlparser.in输入

		codeforces.html http://codeforces.com

## optional usage

(详见htmlparser.h)

### HtmlParser类提供的接口

    Tag* root();

    返回根标签的指针,没有返回NULL
   
    std::string title() const;

    返回标题
   
    Tag head() const;

    返回<head>标签,没有返回nul_tag (const)
   
    Tag body() const;

    返回<body>标签,没有返回nul_tag
	
    int links(std::string path = def_path, const std::string& file = def_file);

    爬取当前文件所有链接并存在一个文件里, path 表示存储目录, file表示存储在哪个文件, 默认path = "link", file = "links.txt"
   
    int images(const std::string& path = def_path);

    爬取所有图片, path 表示存储目录
   
    int sounds(const std::string& path = def_path);

    爬取所有音频文件, path 表示存储目录
   
    int words(const std::string& path = def_path);

    爬取所有办公文件, path 表示存储目录

    Tag find(const std::string& str) const;

    查找名字为str的标签, 若有多个返回第一个, 否则返回nul_tag (const)
   
    std::vector<Tag> find_all(const std::string& str) const;

    查找名字为str的标签, 返回一个包含所有标签的vector, 若没有返回一个空vector

### Tag类提供的接口

    std::string name;

    返回标签名
   
    std::vector<std::string> strs, cmts;

    标签的正文(strs)和注释(cmts)
	
    std::map<std::string, std::string> attrs;

    标签的属性的map
   
    const std::string& operator [](const std::string& str) const;

    返回当前标签的属性str的值,如果没有这个属性返回nul_str (const)
   
    int links(std::string path = def_path, const std::string& file = def_file);

    爬取当前标签下(包括子标签)所有链接并存在一个文件里, path 表示存储目录, file表示存储在哪个文件, 默认path = "link", file = "links.txt"
   
    int images(const std::string& path = def_path);

    爬取当前标签下(包括子标签)所有图片, path 表示存储目录
   
    int sounds(const std::string& path = def_path);

    爬取当前标签下(包括子标签)所有音频文件, path 表示存储目录
   
    int words(const std::string& path = def_path);

    爬取当前标签下(包括子标签)所有办公文件, path 表示存储目录

    Tag find(const std::string& str) const;

    查找当前标签下名字为str的标签, 若有多个返回第一个, 否则返回nul_tag (const)
   
    std::vector<Tag> find_all(const std::string& str) const;

    查找当前标签下名字为str的标签, 返回一个包含所有标签的vector, 若没有返回一个空vector

	Tag* prev() const;

	返回与当前标签平行的上一个标签(与之有共同父亲的标签),没有返回NULL
	
	Tag* next() const;

	返回与当前标签平行的下一个标签(与之有共同父亲的标签),没有返回NULL
	
	Tag* fa() const;

	返回父亲标签,没有返回NULL
	
	Tag* son() const;

	返回第一个儿子的标签,没有返回NULL
