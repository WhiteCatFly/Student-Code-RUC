#ifndef WordDictionary
#define WordDictionary
#include<string>
#include<vector>
#include<math.h>
#include"PostingList.h"
using namespace std;
class Dictionary
{
private:
	string Word;//����
	int ID;//����ID
	int LastAdd;//�õ��������ӵ��ĵ�
	int WordRate;//����Ƶ��
	vector<Posting> PosList;//�����б�
	double IDF;
public:
	Dictionary();
	string GetWord();
	int GetID();
	int GetWordRate();
	double GetIdf();
	vector<Posting> GetPosList();
	void Create(string Word_, int ID_,int DocID_, int PosNum_);
	void Add(int DocID_, int PosNum_);
	void GetIDF(int FileNum);
};
#endif
//�����½�ѧ��
