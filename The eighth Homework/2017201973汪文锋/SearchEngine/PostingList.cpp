#include<vector>
#include"PostingList.h"
using namespace std;
Posting::Posting()
{
	DocID = 0;
	TF = 0;
	Pos.clear();
}
Posting::Posting(int DocID_, int TF_)
{
	DocID = DocID_;
	TF = TF_;
	Pos.clear();
}
Posting::~Posting()
{
	DocID = 0;
	TF = 0;
	Pos.clear();
}
int Posting::GetDocID() { return DocID; }
int Posting::GetTF() { return TF; }
vector<int> Posting::GetPos() { return Pos; }
void Posting::ChangeDocID(int DocID_) { DocID = DocID_; }
void Posting::ChangeTF(int TF_) { TF = TF_; }
void Posting::ChangePos(vector<int> Pos_) { Pos.swap(Pos_); }
void Posting::ChangePosting(int DocID_, int TF_, vector<int> Pos_) { DocID = DocID_; TF = TF_; Pos.swap(Pos_); }