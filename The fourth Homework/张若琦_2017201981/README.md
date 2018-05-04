HTML Parser

格式：
> ./parser [OPTINES] [ARGUMENTS]


选项参数说明：

（除help）要求第一个参数必须为:

``--src=url url`` 或者 ``--src=file filename``

表示将要解析的文件来自url或者文件filename

``-t filename``

``--title=filename``

将文件标题存储到filename文件中，filename默认为title.txt

``-w filename``

``--text=filename``

将文件中所有文本文字存储在filename文件中，filename默认为text.txt

``-p filename``

``--picture=filename``

将html文件里面所有图片存储为filename0，filename1,...filename默认为空

*只有指定url才可以哦～*

``-u URL``

``-s filename``

``--url=URL``

``--url-save=filename``

将所有url链接存储到filename中，默认为urls.txt，url格式为URL（正则表达式），默认为所有url

*只有指定url才可以哦～*

*url请不要输入多余括号……emmmm*

*若指定url格式请在url-save之前输入*


``-h``

``--help``

并没有用的帮助

*支持短选项组合（但不可带参）*


ex. ``-pw``

-------------

用户体验真的是极差呢……(摊手

**感谢陈大佬！%%%**
