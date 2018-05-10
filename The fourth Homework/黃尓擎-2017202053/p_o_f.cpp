#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <cstring>

using namespace std;

class Parser {
private:
  string m_filename;
  string m_title;
  string m_body;
  string m_now_url;
  string done_url;
  vector <string> m_urls;
  vector <string> titles;
  vector <string> body;
  void Transfer_filename();
  bool Is_url(string);
  void Do_url();
public:
  Parser(){};
  Parser(string filename);
  void Get_title();
  void Get_body();
  void Get_urls();
  void Show_body();
  void Show_title();
  void Show_urls();
};

Parser::Parser(string filename) {
  m_filename=filename;
}

void Parser::Transfer_filename() {
  m_now_url=m_filename;
  int num=m_filename.size();
  for(int i=0;i<num;i++) {
    if(m_now_url[i]==',')
    m_now_url[i]='.';
    else if(m_now_url[i]=='-')
    m_now_url[i]='/';
  }
}

bool Parser::Is_url(string temp)
{
  if((temp.find("info.ruc.edu.cn")!=temp.npos)&&(temp.find("upload")==temp.npos)&&(temp.find("#")==temp.npos)&&(temp.find("@")==temp.npos)) {}
  else {return false;}
  for(unsigned int i=0;i<m_urls.size();i++) {
    if(m_urls[i]==temp)
    return false;
  }
  return true;

}
void Parser::Do_url() {
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
void Parser::Get_urls() {
  char chs_filename1[120];
  strcpy(chs_filename1,m_filename.c_str());
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
        if(Is_url(temp)==true) {
          m_urls.push_back(temp);
        }
      }
      else {
        if(temp[0]=='/')
        line.erase(line.begin());
        temp=done_url+temp;
        if(Is_url(temp)==true) {
          m_urls.push_back(temp);
        }
      }
      line1=line2;
    }

  }
  fin.close();
}

void Parser::Show_urls() {
  for(unsigned int i=0;i<m_urls.size();i++) {
    cout<<m_urls[i]<<endl;
  }
}
void Parser::Get_title() {
  string line;
  string front;
  string back;
  string hi="h1";
  char chs_filename1[120];
  strcpy(chs_filename1,m_filename.c_str());
  fstream fin(chs_filename1);
  while(getline(fin,line)) {
    if(line.find("<title")==line.npos)
    continue;
    string::size_type pos=line.find("<title");
    line.substr(pos);
    pos=line.find(">");
    line.substr(pos);
    string::size_type pos2=line.find("<");
    m_title=line.substr(pos+1,pos2-pos);
    break;
  }
  while(getline(fin,line))
  {
    if(line.find(hi)==line.npos)
    continue;
    front="<"+hi+">";
    back="</"+hi+">";
    string::size_type pos1=line.find(front);
    string::size_type pos2=line.find(back);
    line=line.substr(pos1+4,pos2);
    titles.push_back(line);
    hi[1]=hi[1]+1;
  }
  fin.close();
}

void Parser::Show_title() {
  cout<<"title :"<<m_title<<endl;
  for(unsigned int i=0;i<titles.size();i++) {
    cout<<"h"<<i+1<<": "<<titles[i]<<endl;
  }
}
void Parser::Get_body() {
  string line1;
  string line2;
  string line;
  string sentence;
  char chs_filename1[120];
  strcpy(chs_filename1,m_filename.c_str());
  fstream fin(chs_filename1);
  if(!fin.good()) {
    cout<<"error"<<endl;
    return;
  }
  getline(fin,line1);
  while(getline(fin,line2)) {
    line=line1+line2;
    if(line.find("<p>")==line.npos)
    continue;
    if(line.find("</p>")==line.npos)
    continue;
    string::size_type pos1=line.find("<p>");
    string::size_type pos2=line.find("</p>");
    sentence=line.substr(pos1+3,pos2-pos1-3);
    body.push_back(sentence);
    line1=line.substr(pos2+3);
  }
  fin.close();
  cout<<body.size()<<endl;
}

void Parser::Show_body()
{

  for(unsigned int i=0;i<body.size();i++)
  {
    cout<<body[i]<<endl;
  }
}
int main()
{
  string filename="info,ruc,edu,cn-overview_dean.php";
  Parser a_parser=Parser(filename);
  a_parser.Get_title();
  a_parser.Show_title();
  // a_parser.Get_body();
  // a_parser.Show_body();

  return 0;
}
