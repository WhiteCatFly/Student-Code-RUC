#include <iostream>
#include "parser.h"
#include "standardize.h"

Parser::Parser(const string& url = "http://info.ruc.edu.cn")
{
	url_ = url;
	string pre = "wget -O tmp_url.html ";
	string order = pre + url_;
	system(order.c_str());
	get_html("tmp_url.html");
}
Parser::Parser(const char* filename)
{
//std::cout<<"Ss"<<std::endl;
	get_html(filename);	
}


void Parser::get_title() const
{
	stringstream sout;
	string tag = "title=";
	int posnow = 0;
//	while(html.find(tag, posnow+1) != string ::npos)
//	{
//		posnow = html.find(tag,posnow+1);
//		string temp = html.substr(html.find(">", posnow)+1, html.find("<", posnow+1) - html.find(">", posnow)-1);
//		sout << temp << std::endl;
//	}
	while(html.find(tag, posnow+1) != string::npos)
	{
		posnow = html.find(tag, posnow+1);
		string temp = html.substr(html.find("\"", posnow)+1, html.find("\"", html.find("\"", posnow) + 1) - html.find("\"", posnow)-1);
		sout << temp << std::endl;	
	}
	display(sout,"title.txt");	
}
void Parser:: get_url() const
{
	stringstream sout; 
	string tag = "href=";
	int posnow = 0;
	while(html.find(tag, posnow+1) != string::npos)
	{
		posnow = html.find(tag, posnow+1);
		string temp = html.substr(html.find("\"", posnow)+1, html.find("\"", html.find("\"", posnow) + 1) - html.find("\"", posnow)-1);
		sout << temp << std::endl;	
	}
	display(sout,"url.txt");
}
void Parser:: get_text() const
{
	stringstream sout;
	int posnow = 0 ;
	while ( html.find( ">" , posnow + 1 ) != string::npos )
	{
		posnow = html.find( ">" , posnow + 1 ) ;
		if ( html.find ( "<" , posnow ) == string::npos ) break ;
		if( html [ posnow + 1 ] == '<' ) continue ;
		string temp = html.substr ( posnow + 1 , html.find ( "<" , posnow ) - posnow  - 1 ) ;
		string tag = html.substr ( html.find ( "<" , posnow ) + 2 , 5 ) ;
 		if ( tag != "scrip")
		sout <<temp << std::endl; 
	}
	display(sout,"text.txt");
}
void Parser:: get_tag(const string& tag) const
{
	stringstream sout;
	int posnow = 0 ;
	int end ;
	int length = tag.length() ;
	string first ;
	string second ;
	while ( html.find ( "<" + tag , posnow + 1 ) != string::npos )
	{
		posnow = html.find ( "<" + tag , posnow + 1 ) ;
		end = html.find ( ">" ,posnow) ;	
		first = html.substr ( posnow + length + 1 , end - posnow -length - 1 )  ;
		second = html.substr ( end + 1 , html.find ( "<" , posnow + 1 ) - end - 1) ;
		sout << first << ":" << std::endl << "  " <<second << std::endl;
	}
	display(sout,"customized.txt"); 
}
