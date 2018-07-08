#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include<cstring>
#include<vector>
#include<math.h>
#include "include/thulac.h"

using namespace std;

class search_engine
{
	private :

	int N ;

	map < string , map < string , double > > form ;
	map < string , double > score ;
	map < string , double > length ;

	void makeform();
	void calculate_Wtd();
	void calculate_score();

	public :
	map < string , int > query ;
	void print(const vector<pair<string, string> > & res);
	void topk ( int k ) ;
	void input_query();
	
};



void search_engine::makeform()
{
	N = 0 ;
	ifstream fin ( "file_list.txt" ) ; 
	char url_c [ 1000 ] ;
	while( fin.getline ( url_c , 1000 ) ) {
	N ++ ;
	string url_s = url_c ;
	int len = strlen ( url_c ) ;
	url_c[ len ] = '.' ;
	url_c[ len + 1 ] = 'b' ;
	url_c[ len + 2 ] = 'o' ;
	url_c[ len + 3 ] = 'd' ;
	url_c[ len + 4 ] = 'y' ;
	url_c[ len + 5 ] = '\0' ;
	ifstream fbody ( url_c ) ;

	string term ;
	
	while( fbody>>term )
	{
		if( form.count(term) == 0 )
		{
			map < string , double > t1 ;
			t1.insert ( pair<string,double> ( url_s , 1 ) ) ;
			form.insert ( pair<string,map<string,double> > ( term , t1 ) ) ;
		}
		else 
		{
			if ( form [ term ].count ( url_s ) == 0 )
			{
				form [ term ].insert( pair <string,double> ( url_s , 1 ) ) ;
			}
			else
			{
				form [ term ] [ url_s ] ++ ;
			}
		}
	}
	
	fbody.close();
	
	url_c [ len ] = '.' ;
	url_c [ len + 1 ] = 't' ;
	url_c [ len + 2 ] = 'i' ;
	url_c [ len + 3 ] = 't' ;
	url_c [ len + 4 ] = 'l' ;
	url_c [ len + 5 ] = 'e' ;
	url_c [ len + 6 ] = '\0' ; 

	ifstream ftitle ( url_c ) ;

	while( ftitle>>term )
	{
		if( form.count( term ) == 0 )
		{
			map < string , double > t1 ;
			t1.insert ( pair<string,double> ( url_s , 10 ) ) ;
			form.insert( pair<string,map<string,double> > ( term , t1 ) ) ;
		}
		else 
		{
			if ( form [ term ].count( url_s ) == 0 )
			{
				form [ term ].insert( pair < string , double > ( url_s , 1 ) ) ;
			}
			else
			{
				form [ term ] [ url_s ] += 10 ;
			}
		}
	}
	
	ftitle.close();

	//////////////////////test

	}
	return ;
}


void search_engine::calculate_Wtd()
{
	map < string , map < string , double > >::iterator iter ;
	for (iter = form.begin() ; iter != form.end() ; iter ++ )
	{
		map < string , double > :: iterator it ;
		for (it= iter->second.begin() ; it != iter->second.end() ; it ++ )
		{
			it->second = ( 1 + log10 ( it->second ) ) * ( 1 + log10 ( double ( N ) ) - log10 ( double ( iter->second.size() ) ) ) ;
		}
	}
	return ;
}


void search_engine::print(const vector<pair<string, string> > & res) {
	for(auto i = res.begin(); i != res.end(); i++) {
		query.insert ( pair<string,int>(i->first , 1 )) ;
	}
}
void search_engine::input_query()
{
	//char iquery [1000];
	//cin.getline ( iquery , 1000 ) ;

	THULAC lac;
	lac.init();

	string s;
	THULAC_result res;
	cin >> s;
	lac.cut(s, res);
	print(res);
	
}



void search_engine::calculate_score()
{
	map < string , int > :: iterator itq ; 
	for ( itq = query.begin() ; itq != query.end() ; itq ++ )
	{
		 map < string , double > :: iterator itd ;
		for ( itd = form [ itq->first ].begin() ; itd != form [ itq->first ].end() ; itd++ )
		{
			if ( score.count ( itd->first ) == 0 )
			{
				score.insert ( pair< string , double > ( itd->first , form [ itq->first ] [ itd->first ] * query [ itq->first ] ) ) ;
				length.insert ( pair<string,double> ( itd->first , form [ itq->first ] [ itd->first ] * form [ itq->first ] [ itd->first ] ) ) ;
			}
			else
			{
				score [ itd->first ] += form [ itq->first ] [ itd->first ] * query [ itq->first ] ;
				length [ itd->first ] += form [ itq->first ] [ itd->first ] * form [ itq->first ] [ itd->first ] ;
			}
		} 
	}
	map < string , double > :: iterator its ;
	for ( its = score.begin() ; its != score.end() ; its ++ )
	{
		its->second /= sqrt ( length [ its->first ] ) ;
	}
	return ;
}

void search_engine::topk ( int k )
{
	makeform();
	calculate_Wtd();
	
	//query.insert ( pair<string,int> ( "陆续" , 1 )) ;
	//query.insert ( pair<string,int> ( "夏令营" , 1 )) ;
	calculate_score() ;
	string answer [ k ] ;
	map < string , double > :: iterator its ;
	for ( its = score.begin() ; its != score.end() ; its ++ )
	{
		for ( int i = 0 ; i < k ; i ++ )
		{
			if ( answer [ i ].empty ( )  ) {answer [ i ] = its->first ;break;}
			else
			if ( its->second > score[ answer[i] ] )
			{
				for ( int j = k-1 ; j > i ; j --)
				{
					answer [ j ] = answer [ j - 1 ] ;
				}
				answer [ i ] = its->first ; 
				break;
			}
		} 
	} 
	for ( int  i = 0 ; i < k ; i ++ )
	{
		cout << answer [ i ] << endl ;
	} 
	return ;
} 

int main()
{
	
	search_engine test ;
	test.input_query() ;
	test.topk(20) ;
	
	/*map<string,map<string,double> >::iterator iter ;
	for (iter = form.begin() ; iter != form.end() ; iter ++)
	{
		map<string , double > :: iterator it ;
		for (it= iter->second.begin();it!=iter->second.end();it++)
		{
			cout<<iter->first<<' '<<it->first<<' '<<it->second<<endl;
		}
	}*/
	return 0 ;
}

