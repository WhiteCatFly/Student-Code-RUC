#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <math.h>
using namespace std;

class File_pro
{
private:
  string m_file_name;
  vector <string> m_site_list;
  vector <string> m_doc_list;
  int m_number;
public:
  File_pro(string file_name);                                                   //构造函数
  void Get_list();                                                              //得到预读文件列表
  int Get_number();                                                             //返回文件总数
  string Get_doc(int i);                                                        //返回文件名
  // void Show_name() { cout<<m_file_name<<endl;}
};

class Document
{
private:
  string m_file_name;
  int m_list;
  map <string,int> m_wfrequency;
  int m_total;
  static map <string,int> m_dfrequency;
  double m_score;
public:
  Document(string file_name,int list);
  static int Howmany(string st);
  void Doc_pro();
  void Make_Score(double score);
  int Get_list();
  double Make_tf(string st) ;
  double Make_idf(string st);
  double Get_score();
};

class Top
{
private:
  int m_number[100];
  double m_score[100];
  int m_num;
public:
  Top(int num);
  void Compare(Document & doc);
  void Sort();
  void Show(File_pro file);
};
class Query
{
private:
  string m_query;
  int m_total;
  map <string,int> mv_query;
  vector <double> m_tf;
  vector <double> m_idf;
  vector <double> md_tf;
  vector <double> md_idf;
public:
  Query(string query);
  void Make_mv();
  void Make_tf();
  double Make_Score(Document & doc);
  void Make_idf( Document & doc);
  void Make_tf( Document & doc);
  // void Make_idf();
};

map <string,int> Document :: m_dfrequency;
int main()
{
  File_pro file("file_list.txt");
  file.Get_list();
  int file_num=file.Get_number();
  vector <Document> docs;
  for(int i=0;i<file_num;i++)
  {
    string doc_name=file.Get_doc(i);
    Document temp_doc(doc_name,i);
    temp_doc.Doc_pro();
    docs.push_back(temp_doc);
  }


  Query query("蒋洪迅 ");

  Top top(100);

  for(int i=0;i<file_num;i++ )           //debug
  {

    double score=query.Make_Score(docs[i]);
    docs[i].Make_Score(score);
    cout<<i<<"  "<<docs[i].Get_score()<<endl;
    top.Compare(docs[i]);
  }
  top.Sort();
  top.Show(file);
  return 0;
}

int Document::Howmany(string st)
{
  if(m_dfrequency.find(st)==m_dfrequency.end())
  return 0;
  else
  {
    return m_dfrequency[st];

  }
}


File_pro::File_pro(string file_name)
{
  m_file_name=file_name;
}
void File_pro::Get_list()
{
  m_number=0;
  char chs_filename[30];
  strcpy(chs_filename,m_file_name.c_str());
  fstream fin(chs_filename);
  string temp;
  while(getline(fin,temp))
  {
    temp=temp+".body";
    m_doc_list.push_back(temp);
    m_number++;
  }
  fin.close();
}
int File_pro::Get_number()
{
  return m_number;
}
string File_pro::Get_doc(int i)
{
  return m_doc_list[i];
}

Document::Document(string file_name,int list)
{
  m_file_name=file_name;
  m_list=list;
}
void Document::Doc_pro()
{
  fstream fin(m_file_name.c_str());
  string temp_line,temp_word;
  m_total=0;
  string::size_type position;
  map <string,int> :: iterator it;
  while(getline(fin,temp_line))
  {
    while(temp_line.find(" ")!=temp_line.npos)
    {
      m_total++;
      position=temp_line.find(" ");
      temp_word=temp_line.substr(0,position);
      it=m_wfrequency.find(temp_word);
      if(it!=m_wfrequency.end())
      {
        it->second++;
      }
      else
      {
        m_wfrequency.insert(std::pair<string,int>(temp_word,1));
      }
      temp_line=temp_line.substr(position+1);
    }
  }
  map <string,int> :: iterator it2;
  for(it=m_wfrequency.begin();it!=m_wfrequency.end();it++)
  {
     //debug
    it2=m_dfrequency.find(it->first);
    if(it2!=m_dfrequency.end())
    it2->second++;
    else
    {
      m_dfrequency.insert(std::pair<string,int>(it->first,1));
    }
  }
}
void Document::Make_Score(double score)
{
  m_score=score;
}
double Document::Make_idf(string st)
{
  int t=Document::Howmany(st);
  double t2=6056.0/(double)t;
  t2=log(t2)/log(10);
  return t2;
}
double Document::Make_tf(string st)
{
  int t1;
  if(m_wfrequency.find(st)!=m_wfrequency.end())
  t1=m_wfrequency[st];
  else
  {

    return 0;
  }
  // double t2=(double)t1/(double)m_total;             //debug
  double t2=(double)t1;
  t2=1+log(t2)/log(10);
  return t2;
}
double Document::Get_score()
{
  return m_score;
}
int Document::Get_list()
{
  return m_list;
}
Query::Query(string query)
{
  m_query=query;

  Make_mv();

  Make_tf();
}
void Query::Make_mv()
{
  string::size_type position;
  string temp;
  m_total=0;
  while(m_query.find(" ")!=m_query.npos)
  {
    m_total++;
    position=m_query.find(" ");
    temp=m_query.substr(0,position);
    if(mv_query.find(temp)!=mv_query.end())
    {
      map <string,int> :: iterator it;
      it=mv_query.find(temp);
      it->second++;
    }
    else
    mv_query.insert(std::pair<string,int>(temp,1));
    m_query=m_query.substr(position+1);
  }
}
void Query::Make_tf()
{
  for(map <string,int> :: iterator it=mv_query.begin();it!=mv_query.end();it++)
  {
    int a;
    double b;
    a=it->second;
    b=(double)a/(double)m_total;
    b=1+log(b)/log(10);
    m_tf.push_back(b);
  }
}

void Query::Make_idf( Document & doc)
{
  string temp;
  md_tf.clear();
  for(map <string,int> :: iterator it=mv_query.begin();it!=mv_query.end();it++)
  {
    temp=it->first;
    md_idf.push_back(doc.Make_idf(temp));
  }
}
void Query::Make_tf( Document & doc)
{
  string temp;
  md_tf.clear();
  for(map <string,int> :: iterator it=mv_query.begin();it!=mv_query.end();it++)
  {
    temp=it->first;
    md_tf.push_back(doc.Make_tf(temp));
  }

}
double Query::Make_Score(Document & doc)
{
  Make_idf(doc);
  Make_tf(doc);
  int n=m_tf.size();

  double score=0,length=0;


  for (int i=0;i<n;i++)
  {

    cout<<"mdtf: "<<md_tf[i]<<"  ";
    score=m_tf[i]*md_tf[i]*md_idf[i]+score;
  }
  cout<<"score: "<<score<<"  ";
  for(int i=0;i<n;i++)
  {
    length=length+md_tf[i]*md_tf[i]*md_idf[i]*md_idf[i];
  }

  length=sqrt(length);
  cout<<"length: "<<length<<endl;
  if(length==0)
  return 0;
  score=score/length;
  return score;
}

Top::Top(int num)
{
  m_num=num;
}
void Top::Compare(Document & doc)
{
  if(doc.Get_score()>m_score[m_num-1])
  {

    {
      m_score[m_num-1]=doc.Get_score();

      m_number[m_num-1]=doc.Get_list();
    }
  }
  Sort();
}
void Top::Sort()
{
  for(int i=m_num-1;i>0;i--)
  {
    if(m_score[i]>m_score[i-1])
    {
      int tempi;
      double tempb;
      tempi=m_number[i];
      m_number[i]=m_number[i-1];
      m_number[i-1]=tempi;
      tempb=m_score[i];
      m_score[i]=m_score[i-1];
      m_score[i-1]=tempb;
    }
  }
}
void Top::Show(File_pro file)
{
  for(int i=0;i<m_num;i++)
  {
    cout<<file.Get_doc(m_number[i])<<" "<<m_score[i]<<endl;
  }
}
