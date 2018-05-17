#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<sstream>

using namespace std;

class HTMLParser
{

private:

string html ;

int Max_line_length  ; 

void open_web_page(string target_url)
{
	string prefix = "wget -O current_page.txt ";
	string order = prefix + target_url;
	const char* command = order.data();
	system(command);
	return ;
}

void get_html ()
{
	html = "" ;
	char current_str[Max_line_length];
	string str;
	ifstream fin;
	fin.open("current_page.txt"); 
	stringstream ss;
	while ( fin.getline(current_str,Max_line_length) )
	{
		ss.clear();
		ss<<current_str;
		string temp;
		while(1)
		{	
			temp="";
			ss>>temp;
			html+=temp ;
			if(ss.fail ()) break;
		}	
	}
	
	return ;
}

void get_html (ifstream & temp_fin)
{
	html = "" ;
	char current_str[Max_line_length];
	string str;
	stringstream ss;
	while ( temp_fin.getline(current_str,Max_line_length) )
	{
		ss.clear();
		ss<<current_str;
		string temp;
		while(1)
		{	
			temp="";
			ss>>temp;
			html+=temp ;
			if(ss.fail ()) break;
		}	
	}
	
	return ;
}


public:

string source ;

HTMLParser() 
{
	Max_line_length = 100000 ;
	cin >> source ;
	open_web_page ( source ) ;
	get_html () ;
}

HTMLParser(string input_s)
{
	source = input_s ;
	Max_line_length = 100000 ; 
	open_web_page ( source ) ;
	get_html();
}

HTMLParser(ifstream &temp_f)
{
	Max_line_length = 100000 ;
	get_html(temp_f);
}


int get_title()
{
	int mark = 0 ;
	int number = 0 ; 
	while( html.find( "<title" , mark + 1 ) != string::npos )
	{
		mark = html.find( "<title" , mark + 1 ) ;
		string temp = html.substr ( html.find ( ">" , mark ) + 1 , html.find( "<" , mark + 1 )  - html.find ( ">" , mark ) - 1 );
		cout << temp << endl ;
		number ++ ;
	}
	mark = 0 ;
	while ( html.find ( "title=" , mark + 1 ) != string::npos )
	{
		mark = html.find ( "title=" , mark + 1) ;
		string temp = html.substr ( html.find("\"" , mark )+1, html.find ( "\"" , html.find("\"" , mark ) + 1 ) - html.find("\"" , mark ) - 1 );
		cout << temp << endl ;
		number++ ;
	} 
	return number ;
}

int get_text()
{
	int mark = 0 ;
	int number = 0 ;
	while ( html.find( ">" , mark + 1 ) != string::npos )
	{
		mark = html.find( ">" , mark + 1 ) ;
		if ( html.find ( "<" , mark ) == string::npos ) break ;
		if( html [ mark + 1 ] == '<' ) continue ;
		string temp = html.substr ( mark + 1 , html.find ( "<" , mark ) - mark  - 1 ) ;
		string judge = html.substr ( html.find ( "<" , mark ) + 2 , 5 ) ;
 		if ( judge != "scrip" && judge != "title")
		cout << temp << endl ; 
		number ++ ;
	}
	return number ;
}

int get_link()
{
	int mark = 0 ;
	int number = 0 ;
	while ( html.find ( "href=" , mark + 1 ) != string::npos )
	{
		mark = html.find ( "href=" , mark + 1) ;
		string temp = html.substr ( html.find("\"" , mark )+1, html.find ( "\"" , html.find("\"" , mark ) + 1 ) - html.find("\"" , mark ) - 1 );
		cout << temp << endl ;
		number++ ;
	} 
	return number ;
}

int get_tag(string target_tag )
{
	int mark = 0 ;
	int number = 0 ;
	int end ;
	int length = target_tag.length() ;
	string attribute ;
	string word ;
	while ( html.find ( "<" + target_tag , mark + 1 ) != string::npos )
	{
		mark = html.find ( "<" + target_tag , mark + 1 ) ;
		number ++ ;
		end = html.find ( ">" , mark ) ;
		if ( html[end-1] == '/')
		{
			word = "" ;
			if( html[mark+length+1] == '/' )
			attribute = "" ;
			else
			attribute = html.substr ( mark + length + 1 , end - mark -length - 2 )  ;
		}
		else
		{
			if( html[mark+length+1] == '>' )
			attribute = "" ;
			else
			attribute = html.substr ( mark + length + 1 , end - mark -length - 1 )  ;
			if( html[ end + 1 ] == '<')
			word = "" ;
			else 
			word = html.substr ( end + 1 , html.find ( "<" , mark + 1 ) - end - 1) ;
		}
		if ( attribute == "" )
		cout << "attribute:EMPTY "<<endl;
		else 
		cout << "attribute:" << attribute<< endl;
		if ( word == "" )
		cout << "word:EMPTY" <<endl;
		else
		cout << "word:" << word << endl ;
		cout<<endl ;
	}
	return number ;
}


;};

int main()
{
	HTMLParser test  ( "info.ruc.edu.cn" );
	cout << test.get_text() << endl ;
	return 0;
}
