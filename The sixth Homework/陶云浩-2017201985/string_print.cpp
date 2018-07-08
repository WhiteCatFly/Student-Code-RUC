#include<iostream>
#include<cstring> 
#include<stdio.h>
#include<stdlib.h>

using namespace std;

class String 
{
	protected :
		
		char *str;
		int len ;
		static int num ;
		
	public :
		
		String ( const char *s)
		{
			len = strlen ( s ) ;
			str = new char [len+1] ;
			strcpy ( str , s );
			num ++ ;
		}
		
		String ( const String &input_str )
		{
			len = input_str.len ;
			str = new char [len+1];
			strcpy ( str , input_str.str ) ;
			num ++ ;
		}
		
		String ()
		{
			len = 0 ;
			str = new char [1] ;
			str [ 0 ] = '\0' ;
			num ++ ;
		}
		
		~String ()
		{
			num -- ;
			delete [] str ;
		}
		
		virtual String& operator=(const String &st)
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
		
		int sum ()
		{
			return num;
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

int String::num = 0 ;

class String_print : public String 
{
	public:
		String_print (const char *s)
		{
			len = strlen ( s ) ;
			str = new char [len+1] ;
			strcpy ( str , s );
			num ++ ;
		}
		
		String_print ( const String_print &input_str )
		{
			len = input_str.len ;
			str = new char [len+1];
			strcpy ( str , input_str.str ) ;
			num ++ ;
		}
		
		String_print ()
		{
			len = 0 ;
			str = new char [1] ;
			str [ 0 ] = '\0' ;
			num ++ ;
		}
		
		~String_print ()
		{
			num -- ;
			delete [] str ;
		}
		
		String print ( char * format )
		{
			
			int f_len = strlen ( format ) ; 
			char * integer = new char [ 1025 ] ; 
			char * decimal = new char [ 1025 ] ;
			int sign = 0 ;
			int i = 0 ;
			
			if( str [ 0 ] == '-') 
			{
				sign = -1 ;
				i ++ ;
			}
			
			if( str [ 0 ] == '+' )
			{
				sign = 1 ;
				i ++ ;
			}
			
			////////////////分别保存整数和小数部分
			
			int if_point = 0 ;                     
			int mark_integer = 0 ;
			int mark_decimal = 0 ;
			
			for ( ; i < len ; i ++)
			{
				if ( str [ i ] == '.' )
				{
					if_point = 1 ;
					continue ;
				}
				
				if ( if_point == 0 )	
				{
					integer [ mark_integer ] = str [ i ] ;
					mark_integer ++ ; 
				}
				else
				{
					decimal [ mark_decimal ] = str [ i ] ;
					mark_decimal ++ ;
				}
			}
			
			if ( if_point == 0 )
			{
				decimal [ 0 ] = '\0' ;
			}
			
			int i_len = mark_integer ;
			int d_len = mark_decimal ;
			
			///////////////////处理小数部分
			
			int precision  ;                      
			int mark_t = -1 ;
			char temp [ 1025 ] ;
			
			for ( i = 0 ; i < f_len ; i ++ )
			{
				if ( format [ i ] == '.' )
				{
					
					mark_t = 0 ; 
					for ( int j = i + 1  ; j < f_len ; j ++ )
					{
						if ( format [ j ] >= 48 && format [ j ] <= 57 )
						{
							temp [ mark_t ] = format [ j ] ;
							mark_t ++ ;
						}
						else
						break ;
					}
				}
			}
			
			if ( mark_t == -1)
			{
				precision = 6 ;	
			}		
			
			if ( mark_t == 0 )
			{
				precision = 0 ;
			}
			
			if( mark_t != -1 && mark_t != 0)
			{
				temp [ mark_t ] = '\0' ;
				precision = atoi ( temp ) ;
			}
				
			if ( d_len <= precision )
			{
				for ( i = d_len ; i < precision ; i ++ )
				{
					decimal [ i ] = '0' ;
				}
				decimal [ precision ] = '\0' ;
				d_len = precision ;
			}
			
			int carry = 0 ;
			
			if ( d_len > precision ) 
			{
				if ( decimal [ precision ] < '5' )
				{
					decimal [ precision ] = '\0';
					d_len = precision ;
				}
				else
				{
					i = precision - 1 ;
					while ( i >= 0 )
					{
						decimal [ i ] ++ ;	
						
						if ( decimal [ i ] <= '9' )
						break ;
						
						decimal [ i ] = '0';
						i-- ;
						
						if ( i < 0 )
						{
							carry = 1 ;
							break ;
						}
					}
					decimal [ precision ] = '\0' ;
					d_len = precision ;
				}
			}	
			
	    //////////////处理进位 
	    	if ( carry == 1)
	    	{
	    		for ( i = i_len - 1 ; i >= 0 ; i-- )
	    		{
	    			integer [ i ] ++ ;
	    			if ( integer [ i ] > '9' )
	    			integer [ i ] = '0' ;
	    			else
	    			break ;
	    			
	    			if ( i == 0  )
	    			{
	    				for ( int j = i_len ; j >= 1 ; j -- )
	    				integer [ j ] = integer [ j - 1 ] ;
	    				integer [ 0 ] = '1' ;
	    				i_len ++ ;
	    				integer [ i_len ] = '\0' ;
	    				break ;
					}
				}
			}		
		
		////////////////截取flag和width
		char flags [ 10 ] ;
		int flags_len = 0 ;

		for ( i = 1 ; i < f_len ; i ++ )
		{
			if ( ( format [ i ] <= 48 || format [ i ] > 57 ) && format [ i ] != '.' )
			{
				flags [ flags_len ] = format [ i ] ;
				flags_len ++ ;
			}
			else
			{
				flags [ flags_len ] = '\0' ;
				break ;
			}
		}
		
		char width [ 10 ] ;
		int width_len = 0 ;
		
		for ( ; i <= f_len ; i ++ )
		{
			if ( format [ i ] >= 48 && format [ i ] <= 57 )
			{
				width [ width_len ] = format [ i ] ;
				width_len ++ ;
			}
			else
			break ; 
		}
		
		width [ width_len ] = '\0' ;
		int width_num ; 
		
		if ( width_len > 0 )
		{
			width_num = atoi ( width ) ;
		}
		else
		{
			width_num = 0 ;
		}
		///////////////处理符号位 
		for ( i = 0 ; i < flags_len ; i ++ )
		{
			if ( flags [ i ] == '+' )
			{
				if ( sign == 0 )
				sign = 1 ;
				break ; 
			}
		}
		
		for ( i = 0 ; i < flags_len ; i ++ )
		{
			if( flags [ i ] == ' ' ) 
			{
				if ( sign == 0 )
				sign = 2 ;
				break ;
			}
		}
		
		if ( sign != 0 )
		{
			for ( i = i_len ; i >= 1 ; i -- )
			{
				integer [ i ] = integer [ i - 1 ] ;
			}
			
			i_len ++ ;
			if ( sign == -1 ) integer [ 0 ] = '-' ;
			if ( sign == 1 ) integer [ 0 ] = '+' ;
			if ( sign == 2 ) integer [ 0 ] = ' ' ;
			integer [ i_len ] = '\0' ;
		}
		
		//////////////输出整数 
		if ( format [ f_len - 1 ] == 'd')
		{
			if ( width_num == 0 || width_num <= i_len ) 
			{
				String tempstr ( integer ) ;
				return tempstr ;
			}
			
			for ( i = 0 ; i < flags_len ; i ++ )
			{
				if ( flags [ i ] == '-' )
				{
					for ( i = i_len ; i < width_num ; i ++ )
					{
						integer [ i ] = ' ' ;
					}
					integer [ width_num ] = '\0' ;
					String tempstr ( integer ) ;
					return tempstr ;
				}
			}
			
			char if_0 = ' ' ;
			for ( i = 0 ; i < flags_len ; i ++ )
			{
				if ( flags [ i ] == '0' )
				{
					if_0 = '0' ;
				}
			}
			
			for ( i = width_num - 1 ; i >= width_num - i_len ; i -- )
			{
				integer [ i ] = integer [ i - width_num + i_len ] ;
			}
			
			for ( i = width_num - i_len - 1 ; i >= 0 ; i -- )
			{
				integer [ i ] = if_0 ;
			}
			
			String tempstr ( integer ) ;
			return tempstr ;
			
		} 
		
		//////////////////输出小数 
		
		if ( format [ f_len - 1 ] == 'f' )
		{
			if ( i_len + d_len + 1 < width_num )
			{
				int ifminus = 0 ;
				for ( i = 0 ; i < flags_len ; i ++ )
				{
					if ( flags [ i ] == '-')
					{
						int j ;
						for ( j = d_len ; j <= width_num - i_len - d_len  ; j ++ )
						{
							decimal [ j ] = ' ' ;
						}
						decimal [ j ] = '\0' ;
						ifminus = 1 ;
					}
				}
				if ( ifminus != 1 )
				
				{
				
					char if_0 = ' ' ;
					for ( i = 0 ; i < flags_len ; i ++ )
					{
						if ( flags [ i ] == '0' )
						{
							if_0 = '0' ;
						}
					}
					
					integer [ width_num - d_len - 1 ] = '\0' ;
					i_len = strlen ( integer ) ; 
					for ( i = width_num - d_len - 2 ;  i >= width_num - d_len - 1 - i_len ; i -- )
					{
						integer [ i ] = integer [ i - width_num + d_len + 1 + i_len ] ;
					}
					
					for ( ; i >= 0 ; i -- )
					{
						integer [ i ] = if_0 ;
					}
				
				}
					
			}
			
			char temps [ 1024 ] ;
			for ( i = 0 ; i < strlen ( integer ) ; i++)
			{
				temps [ i ] = integer [ i ] ;
			}
			
			temps [ i ] = '.' ; 
			i ++ ;
			
			for ( int j = 0 ; j < strlen ( decimal ) ; i ++ , j ++ )
			{
				temps [ i ] = decimal [ j ] ;
			}
			
			temps [ i ] = '\0' ;
			
			String tempstr ( temps ) ;
			return tempstr ;
		}
		
	}
}
;


int main()
{	
	char input [ 1025 ] ;
	cin >> input ;  
	String_print a ( input ) ;
	char format_ [ 1025 ] ;
	cin >> format_ ;
	cout << a.print ( format_ );
	return 0;
}
