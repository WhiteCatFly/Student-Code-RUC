#include <iostream>
#include <string>
#include <vector>

#include "LoadDict.h"
#include "Search.h"

#include "../THULAC/include/thulac.h"

using std::string;

string Urls[MAXN];
string dictionary[MAXW];
std::vector<std::pair<int, double>> list[MAXW];

int totalwords = 0;
int totalfiles = 0;


void QueryParse(std::string & str, THULAC_result & result);

void showhelp()
{
	std::cerr << "请根据提示输入待搜索内容" << std::endl;
	exit(0);
}

int main(int argc, char ** argv)
{
	if (argc != 1)
		showhelp();

	GetDictionary(dictionary, list, totalwords);
	GetUrlList(Urls, totalfiles);

	std::cout << "请输入将要显示的结果条数：" << std::endl;

	short res_num = 0;
	std::cin >> res_num;
	
	std::cin.ignore(1024, '\n');

	//while (true)
	{
		std::cout << "接下来一行请输入待搜索内容：" << std::endl;

		string str;
		getline(std::cin, str);

		THULAC_result result;
		QueryParse(str, result);

		SRC ans(res_num);
		for (int i = 0; i < result.size() - 1; i ++) {
			ans.add(result[i].first);
			std::cout<<"res: "<<result[i].first<<std::endl;
		}
		ans.show();
	}
	
	return 0;
}

void QueryParse(string & str, THULAC_result & result)
{
	char model_path_[] = "./THULAC/models/";
	char * model_path_char = model_path_;
	char * user_specified_dict_name = NULL;
	int seg_only = 1;
	int useT2S = 0;
	int useFilter = 0;
	char separator = '_';

	THULAC lac;
	lac.init(model_path_char, user_specified_dict_name, seg_only, useT2S, useFilter);

	lac.cut(str, result);
}