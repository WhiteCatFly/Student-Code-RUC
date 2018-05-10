#include "parser.h"

using namespace std;

int main()
{
	int key1 = 1, key2, key3;
	Parser *parser = NULL;
	
	while(key1 != 2)
	{
		key1 = 2;
		cout << "--------------------请选择您的操作--------------------" << endl;
		cout << "1.处理新的网页" << endl;
		cout << "2.退出程序" << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> key1;
		if(key1 == 1)
		{
			key2 = 0;
			cout << "--------------------请选择输入网页代码的方式--------------------" << endl;
			cout << "1.来自键盘" << endl;
			cout << "2.来自文件" << endl;
			cout << "3.来自URL" << endl;
			cout << "0.返回上层" << endl;
			cout << "------------------------------------------------------------" << endl;
			cin >> key2;
			if(key2 == 1)
			{
				cout << "**********请输入网页代码，最后请输入单独一行</html>结束**********" << endl;
				string buf, code = "";
				while(buf != "</html>")
				{
					getline(cin, buf);
					code += buf;
					code += '\n';
				}
				parser = new Parser(code);
			}
			else if(key2 == 2)
			{
				string filename;
				getline(cin, filename);
				getline(cin, filename);
				parser = new Parser(filename.c_str());	
			}
			else if(key2 == 3)
			{
				string url;
				cin >> url;
				string order = "wget --tries=3 -O ";
				order += url;
				order += ".html '";
				order += url;
				order += "'";
				system(order.c_str());
				
				url += ".html";
				parser = new Parser(url.c_str());
			}
			
			if(key2 == 1 || key2 == 2 || key2 == 3)
			{
				cout << "**********网页代码已输入程序，并已将其树形结构存入文件 TreeStructure_网页名.out**********" << endl << endl;
				
				key3 = 1;
				while(key3 != 0)
				{
					cout << "--------------------请选择您对该网页的操作--------------------" << endl;
					cout << "1.获取标题" << endl;
					cout << "2.获取正文" << endl;
					cout << "3.获取超链接" << endl;
					cout << "4.获取图片链接" << endl;
					cout << "5.自定义抽取" << endl;
					cout << "0.返回上层" << endl;
					cout << "------------------------------------------------------------" << endl;
					cin >> key3;
					
					vector<string> result;
					string RegExp;
					
					switch(key3)
					{
						case 1:
							parser->Get_Title(result);
							break;
						case 2:
							parser->Get_Body(result);
							break;
						case 3:
							parser->Get_Href(result);
							break;
						case 4:
							parser->Get_img(result);
							break;
						case 5:
							cout << "--------------------请输入正则表达式--------------------" << endl;
							cin >> RegExp;
							parser->Extract(regex(RegExp.c_str()), result);
							break;
					}
					
					if(key3 != 0)
					{
						ofstream fout("result.out");
						for(int i = 0; i < result.size(); i++)
							fout << result[i] << endl;
						fout.close();
					
						cout << "**********结果已输出到result.out**********" << endl;
					}
				}
			}
			delete parser;
		}
	}
	
	return 0;
}
