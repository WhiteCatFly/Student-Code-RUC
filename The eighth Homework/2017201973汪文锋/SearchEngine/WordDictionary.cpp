#include<vector>
#include<string>
#include<math.h>
#include<iostream>
#include"PostingList.h"
#include"WordDictionary.h"
using namespace std;
Dictionary::Dictionary()
{
	Word = "";
	ID = 0;
	LastAdd = 0;
	WordRate = 0;
	PosList.clear();
	IDF = 0.0;
}
string Dictionary::GetWord() { return Word; }
int Dictionary::GetID() { return ID; }
int Dictionary::GetWordRate() { return WordRate; }
vector<Posting> Dictionary::GetPosList() { return PosList; }
double Dictionary::GetIdf() { return IDF; }
void Dictionary::Create(string Word_, int ID_,int DocID_, int PosNum_)
{
	Word = Word_;
	ID=ID_;
	if (DocID_ != LastAdd)
	{WordRate++; LastAdd = DocID_;}
	bool Flag = false;
	for (int i = 0; i<int(PosList.size()); i++)
	{
		if (PosList[i].GetDocID() == DocID_)
		{
			int TF = PosList[i].GetTF();
			vector<int> Pos = PosList[i].GetPos();
			TF++; Pos.push_back(PosNum_);
			PosList[i].ChangeTF(TF);
			PosList[i].ChangePos(Pos);
			Flag = true;
		}
	}
	if (Flag == false)
	{
		PosList.push_back(Posting());
		int Size = PosList.size() - 1;
		vector<int> Pos; Pos.push_back(PosNum_);
		PosList[Size].ChangePosting(DocID_, 1, Pos);
	}
}
void Dictionary::Add(int DocID_, int PosNum_)
{
	if (DocID_ != LastAdd)
	{WordRate++; LastAdd = DocID_;}
	bool Flag = false;
	for (int i = 0; i<int(PosList.size()); i++)
	{
		if (PosList[i].GetDocID() == DocID_)
		{
			int TF = PosList[i].GetTF();
			vector<int> Pos = PosList[i].GetPos();
			TF++; Pos.push_back(PosNum_);
			PosList[i].ChangeTF(TF);
			PosList[i].ChangePos(Pos);
			Flag = true;
		}
	}
	if (Flag == false)
	{
		PosList.push_back(Posting());
		int Size = PosList.size() - 1;
		vector<int> Pos; Pos.push_back(PosNum_);
		PosList[Size].ChangePosting(DocID_, 1, Pos);
	}
}
void Dictionary::GetIDF(int FileNum)
{
    IDF=log(double(FileNum)/double(WordRate+1));
}
