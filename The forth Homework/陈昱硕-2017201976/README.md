这是一个简单的HTMLparser

用法：

    ./main [OPTION]..

描述：
    -s STRING
    --string=STRING
    设置读入字符串

    -m MODE
    --mode=MODE
    设置读入模式，只接受两种模式from_file和from_string
    from_file表示输入字符串为文件名，from_string表示输入字符串为源码
    默认为from_string

    -o FILE
    --open=FILE
    设置HTML树的输出文件，默认为output.html

    -l MODE
    --list=MODE
    设置提取方式，MODE如果是title, body, links中的某一个，则输出对应的内容
    否则将MODE视为正则表达式，匹配模式忽视大小写

    -h
    --help
    显示帮助信息