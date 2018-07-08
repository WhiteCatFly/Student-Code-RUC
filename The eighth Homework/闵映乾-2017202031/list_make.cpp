#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<utility>
#include<cmath>

using namespace std;


int main(){
	map< string ,vector< pair<string,double> > >list;
	vector< pair<string,double> >::iterator it_word_num;
	map< string ,vector< pair<string,double> > >::iterator it_list;
	
	int document_time = 0;
	ifstream fin("/home/myq/download/file_list.txt");
	if(fin.is_open()){
		string document;
		
		while(getline(fin , document)){
			document_time ++;
			document.erase(0,1);
			string document_body = "/home/myq" + document + ".body";
			string document_title = "/home/myq" + document + ".title";
			ifstream document_fin(document_body.c_str());
			
			if(document_fin.is_open()){
				string content;
				double document_num = 0;
				document_fin >> content;
				
				while(document_fin >> content){
					document_num ++;
					
					if(list.find(content) == list.end()){ 
						vector < pair<string,double> > word_num;
						word_num.push_back(make_pair<string,double>(document,1));
						list[content] = word_num ;
					}
					
					else{
						int count_document = 0;
						
						for(it_word_num = list[content].begin(); it_word_num != list[content].end(); it_word_num ++){
							if(it_word_num->first == document){
								count_document ++;
								it_word_num->second ++;
							}
						}
						
						if(count_document == 0){
							list[content].push_back( make_pair<string,double>(document,1) );
						}
					}
				}
				document_fin.clear();
				document_fin.open(document_title.c_str());
				
				while(document_fin >> content){
					document_num ++;
					
					if(list.find(content) == list.end()){ 
						vector < pair<string,double> > word_num;
						word_num.push_back(make_pair<string,double>(document,1));
						list[content] = word_num ;
					}
					
					else{
						int count_document = 0;
						for(it_word_num = list[content].begin(); it_word_num != list[content].end(); it_word_num ++){
							if(it_word_num->first == document){
								count_document ++;
								it_word_num->second ++;
							}
						}
						
						if(count_document == 0){
							list[content].push_back( make_pair<string,double>(document,1) );
						}
					}
				}
				/*for(it_list = list.begin(); it_list != list.end(); it_list ++){
					for(it_word_num = (it_list->second).begin(); it_word_num != (it_list->second).end(); it_word_num++){
						if(it_word_num->first == document){
							it_word_num->second = 1+log10(it_word_num->second);
						}
					}
				}*/
			}
			document_fin.close();
		}
		cout << document_time << endl;
	}
	fin.close();
	ofstream fout("list.txt");
	for(it_list = list.begin(); it_list != list.end(); it_list ++){
		fout << it_list->first << "    ";
		int add_word = 0;
		for(it_word_num = (it_list->second).begin(); it_word_num != (it_list->second).end(); it_word_num++){
			add_word ++ ;
			//fout << "     " << it_word_num->first << "        " << it_word_num->second << endl;
		}
		for(it_word_num = (it_list->second).begin(); it_word_num != (it_list->second).end(); it_word_num++){
			it_word_num->second = (1+log10(it_word_num->second)) * log10(document_time / add_word);
			fout << "     " << it_word_num->first << "        " << it_word_num->second << endl;
		}
		//fout << "      " << add_word ;
		fout << endl;
	}
	fout.close();	
	return 0;
}
