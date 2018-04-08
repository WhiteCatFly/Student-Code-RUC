这是一个简单的网络爬虫。

简介：
	
	./main [OPTION]..
	
描述：
	
	-s URL
	--seed=URL1,URL2,...,URLn
		设置爬虫的种子，此选项在使用断点加载是无效
	
	-k KEY
	--key-word=KEY1,KEY2,...,KEYn
		设置抓取页面域名的关键字
	
	-l file
	--load=file
		从file文件进行断点加载，否则默认是重新爬取
		
	-h
	--help
		显示帮助信息
	
	--break-point=file
		file为保存断点的文件名，默认是origin.log
		
	--error=file
		file为保存错误信息的文件名，默认是error.log
		
	--retry-count=5
		设置重试次数，默认为5
	
	--timeout=number
		设置超时时间，number为整数，单位是s，默认是10s
	
	--time-interval=number
		设置爬取间隔时间，number为整数，单位是ms，默认是50ms
	
	--save-directory=directory
		设置爬取页面的保存路径，默认是在当前路径下创建一个download文件夹
		
	运行中可以按p键暂停
	暂停时可以按p键继续，按q键退出
