#include <string>
#include <cstdlib>
#include <iostream>
#include "buildlist.h"

void showhelp()
{
	std::cerr << "init help :\n\n"
	             "usage : ./init [--clean] [--help] \n\n"
	             "\t./init         预处理文件建立字典倒排表\n"
	             "\t./init --clean 删除建立的字典倒排表\n"
	             "\t./init --help  帮助\n";
	exit(0);
}

void clean()
{
	if (system("rm ./list/* -rf"))
	{
		std::cerr << "error occured when remove!" << std::endl;
		exit(1);
	}
	exit(0);
}

int main(int argc, char ** argv)
{
	if (argc != 1)
	{
		if (argc != 2)
			showhelp();
		
		std::string arg = argv[1];
		if (arg == "--clean")
			clean();
		else
			showhelp();
	}
	
	buildlist();

	return 0;
}