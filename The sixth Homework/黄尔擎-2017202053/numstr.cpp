#include <iostream>
#include <cstring>
using namespace std;
class String {
private:
  char * str;
  int len;
  static int num_strings;
  //static const int CINLIM = 80;
public:
  String(const char * s);
  String();
  String(const String & st);
  ~String();
  int lenth () const {return len; }

  String & operator = (const String &);
  String & operator = (const char * s);
  char & operator [] (int i);
  const char & operator [] (int i) const;

  friend bool operator < (const String & st, const String & st2);
  friend bool operator > (const String & st, const String & st2);
  friend bool operator == (const String & st, const String & st2);
 friend ostream & operator << (ostream & os, const String  st);
  friend istream & operator >> (istream & is, String & st);
  static int HowMany();
};

int String::num_strings=0;

int String::HowMany()
{
  return num_strings;
}

String::String(const char * s)
{
  len=std::strlen(s);
  str = new char[len+1];
  std::strcpy(str,s);
  num_strings++;
}

String::String()
{
  len=4;
  str = new char[1];
  str[0] = '\0';
  num_strings++;
}

String::String(const String & st)
{
  num_strings++;
  len = st.len;
  str = new char[len+1];
  std::strcpy(str,st.str);
}

String::~String()
{
  --num_strings;
  delete [] str;
}

String & String::operator=(const String & st)
{
  if(this==&st)
    return *this;
  delete [] str;
  len=st.len;
  str = new char[len+1];
  std::strcpy(str,st.str);
  return *this;
}

String & String::operator=(const char * s)
{
  delete [] str;
  len =std::strlen(s);
  str = new char[len+1];
  std::strcpy(str,s);
  return *this;
}

char & String::operator[](int i)
{
  return str[i];
}

const char &String::operator[](int i) const
{
  return str[i];
}

bool operator<(const String &st1, const String &st2)
{
  return (std::strcmp(st1.str,st2.str)<0);
}

bool operator>(const String &st1, const String &st2)
{
  return st2<st1;
}

bool operator==(const String &st1, const String &st2)
{
  return (std::strcmp(st1.str,st2.str)==0);
}

ostream & operator<<(ostream & os, const String st)
{
  os<<st.str;
  return os;
}

istream & operator>>(istream & is, String & st)
{
  char temp[80];
  is.get(temp,80);
  if(is)
    st=temp;
    while( is && is.get()!='\n')
      continue;
    return is;
}


class NumString : public String
{
private:
  bool m_plus;
  bool m_width0;
  int m_width;
  int m_precision;
  int m_dot;
  int be_dot;
  int af_dot;
public:
  NumString();
  NumString(const char *,bool m_plus,int m_width,bool m_width0,int m_precision);
  void Find_dot();
  friend ostream & operator << (ostream & os, NumString  ns);
  int myget(int i);
  bool bmyget(int i);
};

NumString::NumString()
{
  cout << "hello world"<<endl;
}


NumString::NumString(const char * s,bool plus=false,int width=0,bool width0=false,int precision=-1) : String(s)
{
  m_plus=plus;
  m_width=width;
  m_width0=width0;
  m_precision=precision;
}

void NumString::Find_dot()
{
  int len=this->lenth();
  for(int i=0;(*this)[i]!='.'&&i<len;i++)
  {
    be_dot=i+1;
  }
  m_dot=be_dot;
  af_dot=len-m_dot-1;
}

int NumString::myget(int i)
{
  if(i==1) return m_width;
  if(i==2) return m_precision;
  if(i==3) return m_dot;
  if(i==4) return be_dot;
  if(i==5) return af_dot;
  return 0;
}

bool NumString::bmyget(int i)
{
  if(i==1) return m_plus;
  if(i==2) return m_width0;
  return false;
}
ostream & operator << (ostream & os, NumString ns)
{
  int be,af,len,width,zero;
  bool plus,width0;
  if(ns.myget(5)>ns.myget(2))
  af=ns.myget(2);
  else
  af=ns.myget(5);
  be=ns.myget(4);
  len=be+1+af;
  width=ns.myget(1);
  plus=ns.bmyget(1);
  width0=ns.bmyget(2);
  if(width>0){
    zero=width-len;
    if((plus==true)&&(ns[0]!='-'))
    {
      cout<<"+";
    }
    for(int i=0;i<len;i++)
    {
      cout<<ns[i];
    }
    if((width0==true)&&(zero)>0)
    {
      for(int i=zero;i>0;i--)
      cout<<"0";
    }
  }
  else if(width<0)
  {
    int key=0;
    if((plus=true)&&(ns[0]!='-'))
    key=1;
    zero=width-len-key;
    if(width0==true)

    {
      for(int i=zero;i>0;i--)
      cout<<"0";
    }
    if(width0==false)
    {
      for(int i=zero;i>0;i++)
      cout<<" ";
    }
    if(key==1)
    cout<<"+";
    for(int i=0;i<len;i++)
    cout<<ns[i];
  }
  //cout<<"hello world"<<endl;
  return os;
}

int main()
{
  NumString nst=NumString("-3.14159",true,10,true,6);
  cout<<nst;
  return 0;
}
