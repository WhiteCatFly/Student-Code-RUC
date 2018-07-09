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
	string Word;//单词
	int ID;//单词ID
	int LastAdd;//该单词最后添加的文档
	int WordRate;//单词频率
	vector<Posting> PosList;//倒排列表
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
//吴玉章奖学金
