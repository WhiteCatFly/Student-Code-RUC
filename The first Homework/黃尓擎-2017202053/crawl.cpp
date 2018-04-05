
#include<iostream>
#include<ctype.h>
#include<string>
#include<queue>
#include<set>
#include<fstream>
#include <bits/stdc++.h>

using namespace std;
set <string> got_urls;
string Trans(string now_url) //transfer now_url to filename
{
  int num=now_url.size();
  for(int i=0;i<num;i++)
  {
    if(now_url[i]=='.')
    now_url[i]=',';
    if(now_url[i]=='/')
    now_url[i]='-';
  }
  return now_url;
}
void Pre_url(string & now_url) //discard chars after the last /
{
  string::size_type pos=now_url.find_last_of("/");
  if(pos==now_url.npos)
  {
    now_url+="/";
    return;
  }

  now_url=now_url.substr(0,pos);
  now_url=now_url+"/";
}
void Get_urls(string & now_line,queue<string> & now_urls,string now_url)
{
  static int state=1;
  static string temp;
  if(now_line.empty())
  {
    cout<<"empty "<<state<<endl;
    return;
  }

  if(state==1)
  {
    string::size_type pos=now_line.find("<a");
    if(pos==now_line.npos)
    return;
    now_line=now_line.substr(pos);
    state=2;
    // cout<<"1done";
  }
  if(state==2)
  {
    string::size_type pos=now_line.find("href=");
    if(pos==now_line.npos)
    {
      state=3;//3 href not found
      return;
    }         //3 href not found
    now_line=now_line.substr(pos);
    if(now_line[5]=='\'')
    {
      state=1;
      return ;
    }
    if(now_line[5]!='"')
    {
      state=6;// no first
      return;
    }
    while(now_line[0]!='"')
    {
      now_line.erase(now_line.begin());
    };
    now_line.erase(now_line.begin());
    for(;;)
    {
      if(now_line.empty())
      {
        state=4;//4 no end
        return;
      }
      if(now_line[0]=='"')
      {
        state=5;//5 done
        break;
      }
      temp+=now_line[0];
      now_line.erase(now_line.begin());
    }
  }
  if(state==3)
  {
    string::size_type pos=now_line.find("href=");
    if(pos==now_line.npos)
    {
      state=3;//3 href not found
      return;
    }
    now_line=now_line.substr(pos);
    if(now_line[5]!='"')
    {
      state=6;// no first
      return;
    }
    //cout<<endl<<"state:"<<state<<endl;
    while(now_line[0]!='"')
    {
      now_line.erase(now_line.begin());
    };
    now_line.erase(now_line.begin());
    for(;;)
    {
      if(now_line.empty())
      {
        state=4;//4 no end
        return;
      }
      if(now_line[0]=='"')
      {
        state=5;//5 done
        break;
      }
      temp+=now_line[0];
      now_line.erase(now_line.begin());
    }
  }
  if(state==6)
  {
    while(now_line[0]!='"')
    {
      now_line.erase(now_line.begin());
    };
    now_line.erase(now_line.begin());
    for(;;)
    {
      if(now_line.empty())
      {
        state=4;//4 no end
        return;
      }
      if(now_line[0]=='"')
      {
        state=5;//5 done
        break;
      }
      temp+=now_line[0];
      now_line.erase(now_line.begin());
    }
  }
  if(state==4)
  {
    while(now_line[0]==' ')
    {
      now_line.erase(now_line.begin());
    };
    while(now_line[0]!='"')
    {

      temp+=now_line[0];
      now_line.erase(now_line.begin());
      if(now_line.empty())
      return;
    };
    state=5;
  }
  if(state==5)
  {
    if(temp.find("http")!=temp.npos)
    {
      if(temp.find("info.ruc.edu.cn")!=temp.npos)
        {
          if(temp.find("#")==temp.npos)
          {
            if(got_urls.find(temp)==got_urls.end())
            {
              now_urls.push(temp);
              got_urls.insert(temp);
            }
          }
        }
    }
    else
    {

      if(temp[0]=='/')
      {
        temp.erase(temp.begin());
      }
      temp=now_url+temp;
      if((temp.find("#")==temp.npos)&&(temp.find("@")==temp.npos))
      {
        if(got_urls.find(temp)==got_urls.end())
        {
          now_urls.push(temp);
          got_urls.insert(temp);
        }
      }
    }
    temp.clear();
    state=1;
  }
}
int main()
{
  queue<string> now_urls;
  set<string> ced_urls;
  char crawling_url[128];
  char steadchs[128];
  int num=1;
  int error=0;
  char file1[128];
  char file2[128];
  set <string> errors;
  string now_line;
  system("wget -O info,ruc,edu,cn info.ruc.edu.cn");
  string now_url="info.ruc.edu.cn/";
  ifstream fin("info,ruc,edu,cn");
  Pre_url(now_url);
  while(getline(fin,now_line))
  {
    Get_urls(now_line,now_urls,now_url);
    Get_urls(now_line,now_urls,now_url);
    Get_urls(now_line,now_urls,now_url);
    Get_urls(now_line,now_urls,now_url);
  };
  fin.close();
  ced_urls.insert("info.ruc.edu.cn");
  ced_urls.insert("http://info.ruc.edu.cn");
  ced_urls.insert("info.ruc.edu.cn/");
  ced_urls.insert("http://info.ruc.edu.cn/");
  while (!now_urls.empty()) {
    cout<<"size: "<<now_urls.size()<<endl;
    now_url=now_urls.front();
    now_urls.pop();
    if(ced_urls.find(now_url)!=ced_urls.end())
    continue;
    cout<<endl<<"now_url: "<<now_url<<endl<<num<<endl;
    ced_urls.insert(now_url);
    string the_temp=now_url;
    the_temp="\""+the_temp+"\"";
    strcpy(steadchs,the_temp.c_str());
    string filename=Trans(now_url);
    strcpy(file1,filename.c_str());
    filename="\""+filename+"\"";
    strcpy(file2,filename.c_str());
    sprintf(crawling_url,"wget -O %s %s ",file2,steadchs);
    system(crawling_url);
    ifstream fin(file1);
    if(!fin.good())
    {
      error++;
      errors.insert(the_temp);
      continue;
    }
    Pre_url(now_url);
    while(getline(fin,now_line))
    {
      Get_urls(now_line,now_urls,now_url);
      Get_urls(now_line,now_urls,now_url);
      Get_urls(now_line,now_urls,now_url);
      Get_urls(now_line,now_urls,now_url);
    };
    fin.close();
    num++;


  }
  while(!now_urls.empty())
  {
    cout<<now_urls.front()<<endl;
    now_urls.pop();
  }
  cout<<"error: "<<error<<endl;
  for(set<string>::iterator it=errors.begin() ;it!=errors.end();it++)
 {
     cout<<*it<<endl;
 }
  return 0;
}
