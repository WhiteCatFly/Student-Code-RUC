#ifndef Search_H_
#define Search_H_

#include <iostream>
#include <string>

static const int MAXN = 7000;
static const int MAXS = 100;
static const int MAXL = 150;
static const int MAXW = 60000;

typedef std::pair<int, double> pii;

struct chain
{
	int pos;
	double val;
	chain* next;
};

class SRC
{
private:
	int num_show;
	chain hd, tl, *head, *tail;

public:
	// constructor & destructor
	explicit SRC(int num_show = 20);
	explicit SRC(std::string & str, int num_show = 20);
	explicit SRC(const SRC & obj);
	~SRC();

	// friend functions
	friend std::ostream& operator<<(std::ostream & os, const SRC & obj);

	// other functions
	int FindStrID(std::string & str);
//	std::string Getitle(int id);
//	std::string Geturl(int id);
	void GetAns(int * ans, int & num) const;
	void show();
	void merge(SRC &);
	void add(std::string & str);
	chain * insert(chain * pre, pii pr);
};

#endif // Search_H_