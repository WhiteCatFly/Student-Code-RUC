#ifndef PostingList
#define PostingList
#include<vector>
using namespace std;
class Posting
{
private:
	int DocID;
	int TF;
	vector<int> Pos;
public:
	Posting();
	Posting(int DocID_, int TF_);
	~Posting();
	int GetDocID();
	int GetTF();
	vector<int> GetPos();
	void ChangeDocID(int DocID_);
	void ChangeTF(int TF_);
	void ChangePos(vector<int> Pos);
	void ChangePosting(int DocID_, int TF_, vector<int> Pos_);
};
#endif