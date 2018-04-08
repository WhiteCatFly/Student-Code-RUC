#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;
queue  <string> url_process;

string translate (string link);                                  //转换网址

string standard (string order);

string reput (string wenjian);


class Crawl{
	private:
		string in_first_queue ;                                  //保存完整url
		string in_find_url;                                      //保存网页源代码
		set <string> set_of_link;
	public:
		Crawl();
		void AssignmentUrl(char * m_doucument);
		void AssignmentQueue(string front);
		void CreatCommand(const char *  transmission);          //根据网址创建命令
		void ExtractUrl(const string &prefix);                  //在string中提取url
		bool ThisIfDone(string looking_page);
		void PutIn(string no_repet);
		string show();
		
};

 
int main ()
{
    Crawl bfs_url;
    url_process.push("info.ruc.edu.cn");
    while (!url_process.empty()){
    	bfs_url.AssignmentQueue(url_process.front());			//取出队列第一个元素
    	url_process.pop ();										//弹出
    	if (bfs_url.ThisIfDone(bfs_url.show())){
    	    bfs_url.PutIn(bfs_url.show());				//加入set方便判重
    	    char * command  ;
    	    command = (char *) malloc (300 * sizeof (char));
			bfs_url.CreatCommand(command);
			string first_queue = reput ( translate(bfs_url.show())); 
			const char * char_first_queue =first_queue.c_str() ;//把url转化成char数组形式，也就是相应文件名
    	    FILE * fp = fopen (char_first_queue,"r");
    	    fseek (fp,0,SEEK_END);
    	    int len = ftell(fp); 
    	    fseek(fp,0,SEEK_SET);                        //返回文件长度
    	    char * document_content;
    	    document_content = (char *) malloc (( len + 10 )* sizeof(char));
    	    fread (document_content,sizeof (char),len,fp);//将网页内容读到字符串里
     	    bfs_url.AssignmentUrl(document_content) ;          //将字符串赋值给string，方便进行操作
    	    bfs_url.ExtractUrl(bfs_url.show());				  //提取文件中的url并插入队列的函数
    	    free(document_content);						  //释放空间
    	    free(command);
    	    fclose (fp);								  //关闭文件
    	    }//读取url，补全为相对路径，插入队列
    }
    
    return 0;
}


void Crawl::CreatCommand (const char *  transmission ){
	string linking = in_first_queue;
	string mid_value = standard(linking);
	string result = "wget -O ";
	linking = translate (linking);
	result = result + linking + " " + mid_value;
	transmission = result.c_str();
	system (transmission );                                //直接在函数中调用命令行下载
}



void Crawl::ExtractUrl (const string &prefix){//传入参数分别是整个网页文件，以及此时读的文件名
	string input = in_find_url;
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
		url_process.push(url);
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

inline void Crawl::AssignmentQueue(string front){
	in_first_queue = front;
}

inline void Crawl::AssignmentUrl(char * m_doucument){
	in_find_url = m_doucument;
}
Crawl::Crawl(){
	set_of_link.clear();
}

inline bool Crawl::ThisIfDone(string looking_page){
	if(set_of_link.count(looking_page) == 0){
		return true;
	}
	else
		return false;
}
inline void Crawl::PutIn(string no_repet){
	set_of_link.insert(no_repet);
}
inline string Crawl::show(){
	return in_first_queue;
}














    

































    
