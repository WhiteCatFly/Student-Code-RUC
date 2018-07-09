#include"PostingList.h"
#include"WordDictionary.h"
#include"SearchEngine.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstring>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <queue>
map<string,int> Hash;
map<string,int> Hash2;
vector<Dictionary> Book;
const double K=3.0;//Title Add
const int N=12500;
struct DocType
{
    string DocName;
    int DocLen;
    int DocID;
    int DocFrom;
    string DocWhere;
}DocBook[N+5];
struct Searching
{
    double num;
    int DocID;
}ans[N+5];
int save[N+5][200];
queue<int> ans2[N+5];
struct WebType
{
    string WebTitle;
    string WebAddress;
}WebBook[N+5];
int BookID=0,FileID=0,PosID=0,TypeID=0;
string Begin="/home/dia/download/";
bool cmp(Searching a,Searching b){return a.num>b.num;}
void SearchEngine::ReadByDoc(const char *ReadIn)
{
	ifstream input;
	PosID=0;FileID++;
	//if(FileID>50)return;
	//cout<<ReadIn<<endl;
	input.open(ReadIn);
	char Reader[500];
	cout<<"Pre Reading:"<<FileID<<"/"<<12112<<endl;
	string Title="";
	while (input>>Reader)
	{
		string Seader=Reader;
		Title+=Seader;
		PosID++;
		if(Hash[Seader]==0)
		{
            Dictionary newD;
            newD.Create(Seader,++BookID,FileID,PosID);
            Book.push_back(newD);
            Hash[Seader]=BookID;
		}
		else
            Book[Hash[Seader]-1].Add(FileID,PosID);
	}
	string SeadIn=string(ReadIn);
	if(int(SeadIn.find(".title"))!=-1)
	{
        int Len=SeadIn.length()-6;
        SeadIn=SeadIn.substr(0,Len);
        DocBook[FileID].DocFrom=0;
    }
    else
    {
     int Len=SeadIn.length()-5;
     SeadIn=SeadIn.substr(0,Len);
     DocBook[FileID].DocFrom=1;
    }
    if(Hash2[SeadIn]==0)
        Hash2[SeadIn]=++TypeID;
    if(DocBook[FileID].DocFrom==0)
    {
        int NowID=Hash2[SeadIn];
        WebBook[NowID].WebTitle=Title;
        string DelString=SeadIn;
        DelString.erase(0,Begin.length());
        WebBook[NowID].WebAddress="http://"+DelString;
        //cout<<NowID<<":"<< WebBook[NowID].WebTitle<<endl<<WebBook[NowID].WebAddress<<endl;
    }
    DocBook[FileID].DocID= Hash2[SeadIn];
	DocBook[FileID].DocName=SeadIn;
	DocBook[FileID].DocLen=PosID;
	DocBook[FileID].DocWhere=string(ReadIn);
}
void SearchEngine::ReadByFiles(const char * catalog)
{
    struct stat statdir;
    DIR *dir=opendir(catalog);
    struct dirent *p;
    while((p=readdir(dir))!=NULL)
    {
        if(p->d_name[0]!='.')
        {
            char files[500];
            strcpy(files,catalog);
            strcat(files,"/");
            strcat(files,p->d_name);
            stat(files,&statdir);
            if(S_ISDIR(statdir.st_mode))
               ReadByFiles(files);
            else
                ReadByDoc(files);
        }
    }
    closedir(dir);
}
void SearchEngine::CalcIDF()
{
    int len=Book.size();
    for(int i=0;i<len;i++)
        Book[i].GetIDF(FileID);
}
void SearchEngine::FindOneWord(string Words)
{
    int len=Book.size();
    for(int i=0;i<N;i++)
        ans[i].num=-214748.0;
    for(int i=0;i<len;i++)
    {
        if(Words==Book[i].GetWord())
        {
            vector<Posting>  Pos=Book[i].GetPosList();
            int PosLen=Pos.size();
            for(int j=0;j<PosLen;j++)
            {
                int DocID=Pos[j].GetDocID();
                int TF_INT=Pos[j].GetTF();
                double TF=double(TF_INT)/double(DocBook[DocID].DocLen);
                if(DocBook[DocID].DocFrom==0)
                {
                    if(ans[DocBook[DocID].DocID].num==-214748.0)ans[DocBook[DocID].DocID].num=0;
                    ans[DocBook[DocID].DocID].num+=(TF*Book[i].GetIdf())*K*1000.0;
                    ans[DocBook[DocID].DocID].DocID=DocBook[DocID].DocID;
                }
                if(DocBook[DocID].DocFrom==1)
                {
                    if(ans[DocBook[DocID].DocID].num==-214748.0)ans[DocBook[DocID].DocID].num=0;
                    ans[DocBook[DocID].DocID].num+=TF*Book[i].GetIdf()*1000.0;
                    ans[DocBook[DocID].DocID].DocID=DocBook[DocID].DocID;
                }
            }
        }
    }
    sort(ans,ans+N-5,cmp);
    for(int i=0;i<10;i++)
        cout<<ans[i].DocID<<":"<<WebBook[ans[i].DocID].WebTitle<<endl<<WebBook[ans[i].DocID].WebAddress<<endl<<endl;
}
void SearchEngine::FindMultiWord(vector<string> Words)
{
    int WordLen=Words.size();
    for(int i=0;i<N;i++)
        ans[i].num=-214748.0;
    for(int i=0;i<N;i++)
      for(int j=0;j<500;j++)
        save[i][j]=0;
    for(int p=0;p<WordLen;p++)
    {
        int len=Book.size();
        for(int i=0;i<len;i++)
        {
            if(Words[p]==Book[i].GetWord())
            {
                vector<Posting>  Pos=Book[i].GetPosList();
                int PosLen=Pos.size();
                for(int j=0;j<PosLen;j++)
                {
                    int DocID=Pos[j].GetDocID();
                    int TF_INT=Pos[j].GetTF();
                    vector<int> Pos2=Pos[j].GetPos();
                    int Pos2Len=Pos2.size();
                    //cout<<Pos2Len<<endl;
                    if(p==0)
                    {
                        save[DocID][0]=Pos2Len;
                        for(int q=0;q<Pos2Len;q++)
                            save[DocID][q+1]=Pos2[q];
                    }
                    else
                    {
                        int tt=0;
                        while(ans2[DocID].empty()==0)
                        {
                            int NPos=ans2[DocID].front();
                            ans2[DocID].pop();
                            for(int q=0;q<Pos2Len;q++)
                                if(NPos+1==Pos2[q])
                                    save[DocID][++tt]=NPos+1;
                            save[DocID][0]=tt;
                        }
                    }
                    double TF=double(TF_INT)/double(DocBook[DocID].DocLen);
                    if(DocBook[DocID].DocFrom==0)
                    {
                        if(ans[DocBook[DocID].DocID].num==-214748.0)ans[DocBook[DocID].DocID].num=0;
                        ans[DocBook[DocID].DocID].num+=(TF*Book[i].GetIdf())*K*1000.0;
                        ans[DocBook[DocID].DocID].DocID=DocBook[DocID].DocID;
                    }
                    if(DocBook[DocID].DocFrom==1)
                    {
                        if(ans[DocBook[DocID].DocID].num==-214748.0)ans[DocBook[DocID].DocID].num=0;
                        ans[DocBook[DocID].DocID].num+=TF*Book[i].GetIdf()*1000.0;
                        ans[DocBook[DocID].DocID].DocID=DocBook[DocID].DocID;
                    }
                }
            }
        }
        for(int i=0;i<N;i++)
        {
            while(ans2[i].empty()==0)ans2[i].pop();
            for(int j=0;j<save[i][0];j++)
                ans2[i].push(save[i][j]);
        }
    }
    for(int i=0;i<N;i++)
    {
        double tt=2.7;
        while(ans2[i].empty()==0){ans2[i].pop();tt+=2.7;}
        ans[DocBook[i].DocID].num=ans[DocBook[i].DocID].num*log(tt);
    }
    sort(ans,ans+N-5,cmp);
    for(int i=0;i<10;i++)
        cout<<ans[i].DocID<<":"<<WebBook[ans[i].DocID].WebTitle<<endl<<WebBook[ans[i].DocID].WebAddress<<endl<<endl;
}
void SearchEngine::ReadAndSearch()
{
    string ReadIn;
    cout<<"Search? :";
    cin>>ReadIn;
    vector<string> Begin;
    while(ReadIn!="Q")
    {
        ofstream Output("/home/dia/Linux_BIGW/SearchEngine/Input");
        Output<<ReadIn<<endl;
        system("./thulac -seg_only -input /home/dia/Linux_BIGW/SearchEngine/Input -output /home/dia/Linux_BIGW/SearchEngine/Output");
        ifstream Input("/home/dia/Linux_BIGW/SearchEngine/Output");
        string ls;
        while (Input>>ls)
        {
            if(ls[0]!=char(0)&&ls.length()>0)
              Begin.push_back(ls);
        }
        cout<<ls<<endl;
        FindOneWord(ls);
        cout<<"---------"<<endl;
        FindMultiWord(Begin);
        vector<string>().swap(Begin);
        cout<<"Search? :";
        cin>>ReadIn;
    }
}
void SearchEngine::Check()
{
    for(int i=0;i<50;i++)
    {
        cout<<Book[i].GetIdf()<<endl;
    }
}
