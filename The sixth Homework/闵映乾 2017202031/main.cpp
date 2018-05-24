#include"mystring.h"
#include"mygoodstring.h"
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;



int main(){
	char input[1025];
	char command[1025];
	
	while(scanf("%s%s" , input , command) == 2){
	MyGoodString enter(input);
	MyGoodString order(command);
	enter.print(order);
	}
	return 0;
}

