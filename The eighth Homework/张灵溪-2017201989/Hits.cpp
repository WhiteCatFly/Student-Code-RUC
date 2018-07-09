#include <iostream>
#include <vector>
#include <utility>
#include "Hits.h"
#include "document.h"

using namespace std;

void Hits::insert(pair<int, double> doc){
	if(res.size() < rank){
		res.push_back(doc);
		if(res.size() == rank){
			for(size_t i=0;i<rank;i++){
				for(size_t j=i;j<rank;j++)
					if(res[j].second>res[i].second){
						pair<int, double> temp;
						temp=res[j];
						res[j]=res[i];
						res[i]=temp;
					}
			}
		}
		return;
	}
	for(size_t i = 0; i < rank; i++){
		if(doc.second > res[i].second){
			res.insert(res.begin() + i, doc);
			break;
		}
	}
}

void Hits::print(){
	for(size_t i = 0; i < rank && i < res.size(); i++)
		cout<<store[res[i].first].Title()<<store[res[i].first].Url()<<endl;
}
