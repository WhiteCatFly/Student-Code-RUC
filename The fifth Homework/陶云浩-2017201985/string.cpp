#include<iostream>
#include<cstring> 
using namespace std;
class String 
{
	private :
		
		char *str;
		int len ;
		static int num ;
	public :
		
		String (const char *s)
		{
			len = strlen ( s ) ;
			str = new char [len+1] ;
			strcpy ( str , s );
			num++;
		}
		
		String ( const String &input_str )
		{
			len = input_str.len ;
			str = new char [len+1];
			strcpy ( str , input_str.str ) ;
			num++;
		}
		
		String ()
		{
			len = 0 ;
			str = new char [1] ;
			str [ 0 ] = '\0' ;
			num++ ;
		}
		
		~String ()
		{
			delete [] str ;
			num--;
		}
		
		String& operator=(const String &st)
		{
			if ( this == &st )
			return *this ;
			delete [] str ;
			len = st.len ;
			str = new char [len+1] ;
			strcpy (str , st.str);
			return *this ;
		}
		
		String & operator = ( const char *s )
		{
			delete [] str;
			len = strlen(s);
			str = new char [len+1] ;
			strcpy (str , s ) ;
			return *this ;
		}
		
		char & operator[]( int i ) 
		{
			return str [ i ] ;
 		}
 		
 		const char & operator [] (const int i) const 
 		{
 			return str [i] ;
		}
		 
		friend bool operator <(const String &st1 , const String &st2 );	
		friend bool operator >(const String &st1 , const String &st2 );
		friend bool operator ==(const String &st1 , const String &st2 );
		friend ostream& operator <<(ostream &os ,const String & st);
		friend istream& operator >> (istream &is , String &st) ;	
		
		int sum()
		{
			return num ;
		}

};
	
bool operator <(const String  &st1 ,const String &st2 )
{
	return (strcmp(st1.str , st2.str)<0);
}

bool operator >(const String &st1 , const String &st2 )
{
	return st2<st1 ;
}

bool operator ==(const String &st1 , const String &st2 )
{
	return (strcmp(st1.str ,st2.str)==0);
}

ostream& operator <<(ostream &os ,const String & st)
{
	os<<st.str ;
	return os ;
}

istream& operator >>(istream &is , String & st)
{
	char temp [10000] ;
	is.get(temp , 10000);
	st = temp ;
	while(is&&is.get()!='\n')
	continue;
	return is ;
}
int String::num = 0;
int main()
{
	
	String a("abc");
	cout<<a;
	return 0;
}
