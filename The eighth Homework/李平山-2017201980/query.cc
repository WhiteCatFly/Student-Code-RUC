#include "query.h"

void Query::print(const vector<pair<string, string> > & res) {
	for(auto i = res.begin(); i != res.end(); i++) {
		query.insert ( pair<string,int>(i->first , 1 )) ;
	}
}
void Query::init()
{
	//query.insert ( pair<string,int>("夏令营" , 1 )) ;
	//query.insert(pair<string,int>("院长",1));
	THULAC lac;
	lac.init();

	string s;
	THULAC_result res;
	cin >> s;
	lac.cut(s, res);
	print(res);
}
void Query::cal_score()
{
	map < string , int > :: iterator itq ; 
	for ( itq = query.begin() ; itq != query.end() ; itq ++ )
	{
		 map < string , double > :: iterator itd ;
		for ( itd = chart [ itq->first ].begin() ; itd != chart [ itq->first ].end();itd++  )
		{
			if ( score.count(itd->first)==0)
			{
				score.insert(pair<string,double>(itd->first,chart[itq->first][itd->first]*query[itq->first]));
				length.insert(pair<string,double>(itd->first,chart[itq->first][itd->first]*chart[itq->first][itd->first]));
			}
			else
			{
				score[itd->first]+=chart[itq->first][itd->first]*query[itq->first];
				length[itd->first]+=chart[itq->first][itd->first]*chart[itq->first][itd->first];
			}
		} 
	}
	map < string , double > :: iterator its ;
	for ( its = score.begin() ; its != score.end() ; its ++ )
	{
		its->second/=length[its->first];
	}
	return ;
}
bool cmp(const pair<string,double> &p1,const pair<string,double> &p2)
{
	return p1.second > p2.second;
}
void Query::sort_k()
{
   vector< pair<string,double> > arr;
   for (map<string,double> :: iterator it = score.begin(); it != score.end(); it++)
   {
   	//cout<<it->first<<'\t'<<it->second<<endl;
   	arr.push_back(make_pair(it->first,it->second));
   }
   sort(arr.begin(),arr.end(),cmp);
   int i = 0;
   for (vector<pair<string,double> >::iterator it=arr.begin(); it!=arr.end(); ++it)
   {
		i++;
   		cout<<it->first<<'\t'<<endl;//<<it->second<<endl;
   		if(i>=k) break;
   }	
}

