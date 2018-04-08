#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;
void CreatCommand (string &linking ,const char *  transmission);//根据网址创建命令
void ExtractUrl (const string &input,const string &prefix) ;      //在string中提取url

string translate (string link);                                  //转换网址

string standard (string order);

string reput (string wenjian);

queue  <string> bfs;

int main ()
{
    set <string> set_of_link;
    set_of_link.clear ();
    bfs.push("info.ruc.edu.cn");
    while (!bfs.empty()){
    	string first_queue = bfs . front ();				//取出队列第一个元素
    	bfs . pop ();										//弹出
    	if (!set_of_link . count(first_queue)){
    	    set_of_link . insert (first_queue);				//加入set方便判重
    	    char * command  ;
    	    command = (char *) malloc (300 * sizeof (char));
    	    string store = first_queue ;                    //保存一下first_queue,因为后面函数中引用会修改
			CreatCommand (first_queue,command) ;
			first_queue = reput ( first_queue);
    	    const char * char_first_queue =first_queue.c_str() ;//把url转化成char数组形式，也就是相应文件名
    	    FILE * fp = fopen (char_first_queue,"r");
    	    fseek (fp,0,SEEK_END);
    	    int len = ftell(fp); 
    	    fseek(fp,0,SEEK_SET);                        //返回文件长度
    	    char * document_content;
    	    document_content = (char *) malloc (( len + 10 )* sizeof(char));
    	    fread (document_content,sizeof (char),len,fp);//将网页内容读到字符串里
     	    string find_url = document_content;           //将字符串赋值给string，方便进行操作
    	    ExtractUrl (find_url,store);				  //提取文件中的url并插入队列的函数
    	    free(document_content);						  //释放空间
    	    free(command);
    	    fclose (fp);								  //关闭文件
    	    }//读取url，补全为相对路径，插入队列
    }
    
    return 0;
}


void CreatCommand (string &linking,const char *  transmission ){
	string mid_value = standard(linking);
	string result = "wget -O ";
	linking = translate (linking);
	result = result + linking + " " + mid_value;
	transmission = result.c_str();
	system (transmission );                                //直接在函数中调用命令行下载
}



void ExtractUrl (const string &input,const string &prefix){//传入参数分别是整个网页文件，以及此时读的文件名
	const string wrong_first = "http";
	const string wrong_second = "www";
	const string right = "info";
	const char flag = '/';	
	int position_beg = 0;
	int position = 0;
	int prefix_length = prefix.size();
	while (position_beg != -1){
		position_beg = input.find("<a",position);
		if(position_beg == -1)
			break;
		position = input.find("href=\"",position_beg);
		if(position == -1)
			break;
		position += 6;
		int beg_pos = position;
		position = input.find('\"',position);
		if(position == -1)
			break;
		string url = input.substr(beg_pos,position-beg_pos);
		if((url.substr(0,4) == wrong_first) || (url.substr(0,3) == wrong_second))
			continue;
		else if (url.substr(0,4) == right);
		else{
			int last_pos = prefix.find_last_of(flag);
			if(last_pos == -1)
				url = prefix+flag+url;
			else{
				string value = prefix;                     //防止prefix不可改
				url = value.replace(last_pos+1,prefix_length-last_pos-1,url);
			}
		}
		bfs.push(url);
	}
}


string translate ( string link){                           //规范文件名格式    
    int link_len = link.size();
	for(int point = 0; point < link_len ; point++){
		if(link[point]=='/'||link[point]=='?')
			link[point]=',';
	}
	if(link[0] == '\"')
		return link;
	else{
		link.insert(0,"\"");
		link += "\"";
	}
	return link;
}

string standard (string order){                             //规范网址命令格式
	if(order[0] == '\"')
		return order;
	else{
		order.insert(0,"\"");
		order += "\"";
	}
	return order;
}

string reput (string wenjian ){
	if(wenjian[0] == '\"'){
		wenjian.erase(0,1);
		int wenjian_len = wenjian.size();
		wenjian.erase(wenjian_len-1,1);
	}
	return wenjian;
}






















    

































    
