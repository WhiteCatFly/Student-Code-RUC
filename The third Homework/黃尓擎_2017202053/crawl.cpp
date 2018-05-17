#include<iostream>
#include<string>
#include<set>
#include<queue>
#include <bits/stdc++.h>
#include<ctype.h>
#include<fstream>
using namespace std;
set<string> m_all_urls;                  //所有合法url
queue<string> m_new_urls;               //所有沒被爬取的url
set<string> m_ced_urls;                 //所有已被爬取的url
class Crawl {
private:
  string m_now_url;                   //當前url
  string m_filename;                  //對應文件名
  string done_url;                    //預處理過的url
  char chs_filename1[120];
  char chs_filename2[128];
  char chs_crawl[128];
  char chs_now_url[128];
  bool Is_url(string temp);                  //判斷是否合法
  int cnt;
public:
  Crawl(string str);
  Crawl();
  void Re_now_url();
  void Make_filename();
  void Make_crawl();
  void Do_url();
  void Get_urls();
  bool Have_done();
  void Done() { m_ced_urls.insert(m_now_url);}
  void Count(){ cnt++;cout<<cnt<<endl;}
};

int main()
{
  Crawl crawl_url=Crawl("info.ruc.edu.cn");
  // cout<<"done"<<endl;
  while(!m_new_urls.empty())
  {
    // cout<<"done"<<endl;
    if(crawl_url.Have_done()==true) {
      crawl_url.Re_now_url();
      continue;
    }
    crawl_url.Make_filename();
    crawl_url.Make_crawl();
    crawl_url.Do_url();
    crawl_url.Get_urls();
    crawl_url.Done();
    crawl_url.Count();
    crawl_url.Re_now_url();
  }
  return 0;
}
Crawl::Crawl() {
  m_now_url="info.ruc.edu.cn";
  while(!m_new_urls.empty()) {
    m_new_urls.pop();
  }
  m_new_urls.push(m_now_url);
  m_ced_urls.clear();
  cnt=0;
}
Crawl::Crawl(string str) {
  m_now_url=str;
  while(!m_new_urls.empty()) {
    m_new_urls.pop();
  }
  m_new_urls.push(m_now_url);
  m_ced_urls.clear();
  cnt=0;
}
void Crawl::Re_now_url() {
  m_new_urls.pop();
  if(!m_new_urls.empty())
  m_now_url=m_new_urls.front();
}
void Crawl::Make_filename() {
  m_filename=m_now_url;
  int num=m_filename.size();
  for(int i=0;i<num;i++) {
    if(m_filename[i]=='.')
    m_filename[i]=',';
    else if(m_filename[i]=='/')
    m_filename[i]='-';
  }
  strcpy(chs_filename1,m_filename.c_str());
  m_filename="\""+m_filename+"\"";
  strcpy(chs_filename2,m_filename.c_str());
}
void Crawl::Make_crawl() {
  string a_url=m_now_url;
  a_url="\""+a_url+"\"";
  strcpy(chs_now_url,a_url.c_str());
  sprintf(chs_crawl,"wget -O %s %s",chs_filename2,chs_now_url);
  system(chs_crawl);

}
void Crawl::Do_url() {
  done_url=m_now_url;
  string::size_type pos=done_url.find_last_of("/");
  if(pos==done_url.npos)
  {
    done_url+="/";
    return;
  }
  else
  {
    done_url=done_url.substr(0,pos);
    done_url=done_url+"/";
  }
}
bool Crawl::Have_done() {
  if(m_ced_urls.count(m_now_url)==1)
  return true;
  return false;
}
bool Crawl::Is_url(string temp)
{
  if((temp.find("info.ruc.edu.cn")!=temp.npos)&&(temp.find("upload")==temp.npos)&&(temp.find("#")==temp.npos)&&(temp.find("@")==temp.npos))
  return true;
  return false;
}
void Crawl::Get_urls()
{

  fstream fin(chs_filename1);
  string line1;
  string line2;
  string line;
  getline(fin,line1);
  while(getline(fin,line2))
  {
    line=line1+line2+"!";
    bool flag=true;
    while(line.find("<a")!=line.npos) {
      string::size_type pos=line.find("<a");
      line=line.substr(pos);
      line.erase(line.begin());
      string temp;
      temp.clear();
      if(line.find("href=\"")==line.npos)
      continue;
      pos=line.find("href=\"");
      line=line.substr(pos);
      line=line.substr(6);
      while(line[0]!='\"') {
        if(line[0]=='!') {
          flag=false;
          break;
        }
        temp=temp+line[0];
        line.erase(line.begin());
      }
      if(flag==false)
      break;
      if((temp.find("http")!=temp.npos)||(temp.find("www")!=temp.npos)) {
        if((Is_url(temp)==true)&&(m_all_urls.count(temp)==0)) {
          m_new_urls.push(temp);
          m_all_urls.insert(temp);
          // cout<<temp<<endl;
        }
      }
      else {
        if(temp[0]=='/')
        line.erase(line.begin());
        temp=done_url+temp;
        if((Is_url(temp)==true)&&(m_all_urls.find(temp)==m_all_urls.end())) {
          m_new_urls.push(temp);
          m_all_urls.insert(temp);
        }
      }
      line1=line2;
      // cout<<temp<<endl;
    }

  }
  fin.close();
}
