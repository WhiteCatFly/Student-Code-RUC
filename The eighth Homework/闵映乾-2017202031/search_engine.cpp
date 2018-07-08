#include "search_engine.h"



void Rucsearch::search_score()
{
	map < string , int > :: iterator itq ; 
	for ( itq = query.begin() ; itq != query.end() ; itq ++ )
	{
		 map < string , double > :: iterator itd ;
		for ( itd = elect [ itq->first ].begin() ; itd != elect [ itq->first ].end() ; itd++ )
		{
			if ( score.count ( itd->first ) == 0 )
			{
				score.insert ( pair< string , double > ( itd->first , elect [ itq->first ] [ itd->first ] * query [ itq->first ] ) ) ;
				length.insert ( pair<string , double> ( itd->first , elect [ itq->first ] [ itd->first ] * elect [ itq->first ] [ itd->first ] ) ) ;
			}
			else
			{
				score [ itd->first ] += elect [ itq->first ] [ itd->first ] * query [ itq->first ] ;
				length [ itd->first ] += elect [ itq->first ] [ itd->first ] * elect [ itq->first ] [ itd->first ] ;
			}
		} 
	}
	map < string , double > :: iterator its ;
	for ( its = score.begin() ; its != score.end() ; its ++ )
	{
		its->second /=  length [ its->first ]  ;
	}
	return ;
}

void Rucsearch::topk ( int k )
{
	
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


void Rucsearch::input_form(){
	ifstream fin_map("list.txt");
	string word;
	string document;
	double wtd;
	string term ;
	while(fin_map >> word){
		if(word[0]!='/'||word[1]!='d')
		{
			term = word ;
			map<string , double > calculate ;
			elect.insert( pair <string , map <string , double> >(term,calculate ) ) ;
			fin_map >> word  ;
		}
		fin_map >> wtd; 
		elect[term].insert (pair<string , double > ( word , wtd ) ) ;
		
	}

}

void Rucsearch::query_cut(string question){

	void * engine = segmentor_create_segmentor("/home/myq/文档/分词与标注/ltp_data/cws.model");
    if (!engine) {
        return ;
    }
   
    std::vector<std::string> words;
    int len = segmentor_segment(engine, question.c_str(), words);
    for (int i = 0; i < len; ++ i) {
 
        if(query.find(words[i]) == query.end()){
        	query[words[i]] = 1;
        }
        else{
        	query[words[i]] ++;
        }
        
    }

    segmentor_release_segmentor(engine);
    return ;
}

