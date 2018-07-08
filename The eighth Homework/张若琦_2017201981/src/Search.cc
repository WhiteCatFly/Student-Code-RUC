#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "Search.h"

using std::string;

extern string Urls[MAXN];
extern string dictionary[MAXW];
extern std::vector<std::pair<int, double>> list[MAXW];

extern int totalwords;
extern int totalfiles;


inline int min(int a, int b)
{
	return a < b ? a : b;
}

SRC::SRC(int num)
{
	num_show = min(num, MAXS);
	head = &hd;
	tail = &tl;
	(head -> next = tail) -> next = NULL;

	head -> pos = -1;
	tail -> pos = MAXN;
}

SRC::SRC(string & str, int num)
{
	num_show = min(num, MAXS);
	head = &hd;
	tail = &tl;
	(head -> next = tail) -> next = NULL;

	head -> pos = -1;
	tail -> pos = MAXN;

	int id = FindStrID(str);
	int n = list[id].size();
//	std::cout << id << ' ' << n << std::endl;

	if (id >= 0 && id < totalwords)
	{
		chain * now = head, * tmp;
		for (int i = 0; i < n; i ++)
		{
			tmp = now;
			now = new chain;
			now -> pos = list[id][i].first;
			now -> val = list[id][i].second;
			tmp -> next = now;
//			std::cout<<i << ' ' << now->pos<<' '<<now->val<<std::endl;
		}
		now -> next = tail;
	}

}

SRC::~SRC()
{
	chain * tmp;
	for (chain * now = head -> next; now != tail; now = tmp)
	{
		tmp = now -> next;
		delete now;
	}
}

SRC::SRC(const SRC & obj)
{
	num_show = obj.num_show;
	head = &hd;
	tail = &tl;
	(head -> next = tail) -> next = NULL;

	head -> pos = -1;
	tail -> pos = MAXN;

	chain * now = head;
	for (chain * ptr = obj.head -> next; ptr != obj.tail; ptr = ptr -> next)
	{
		chain * tmp = new chain;
		tmp -> pos = ptr -> pos;
		tmp -> val = ptr -> val;
		now -> next = tmp;
		now = now -> next;
	}
	now -> next = tail;
}

int SRC::FindStrID(string & str)
{
	if (str < dictionary[0])
		return -1;
	if (str > dictionary[totalwords - 1])
		return totalwords;
	int l = 0, r = totalwords;
	while (l < r - 1)
	{
		int mid = (l + r) >> 1;
		if (dictionary[mid] == str)
			return mid;
		if (dictionary[mid] < str)
			l = mid;
		else
			r = mid;
	}
	return dictionary[l] == str ? l : -1;
}

chain * SRC::insert(chain * pre, pii pr)
{
	chain * now = new chain;
	now -> next = pre -> next;
	pre -> next = now;
	now -> pos = pr.first;
	now -> val = pr.second;
	return now;
}

string Getitle(int id)
{
	string path = "./data" + Urls[id] + ".title";
	std::ifstream infile(path.c_str());
	
	string ret, tmp;
	while (infile >> tmp)
		ret += tmp;
	infile.close();
	return ret;
}

string Geturl(int id)
{
	string tmp = Urls[id];
	return tmp.erase(0, 10);
}

bool cmp(const pii & a, const pii & b)
{
	return a.second > b.second;
}

void SRC::GetAns(int * ans, int & num) const
{
	int cnt = 0;
	pii tmp[MAXN];
	chain * now = head -> next;
	while (now != tail)
	{
		tmp[cnt ++] = pii(now -> pos, now -> val);
		now = now -> next;
	}
	sort(tmp, tmp + cnt, cmp);
	num = min(num, cnt);
	for (int i = 0;i < num;i ++)
		ans[i] = tmp[i].first;
}

std::ostream& operator<<(std::ostream & os, const SRC & obj)
{
	int ans[MAXN];
	int num = obj.num_show;
	obj.GetAns(ans, num);
	for (int i = 0; i < num; i ++)
	{
		os << std::setw(4) << ans[i] << ' ' << Getitle(ans[i]) << '\n'
		   << "     " << Geturl(ans[i]) << std::endl;
	}
}

void SRC::show()
{
	std::cout << *this;
}

void SRC::merge(SRC & obj)
{
	chain * ptr = obj.head -> next, * now = head;
	while (ptr != obj.tail)
	{
		while (now -> next -> pos <= ptr -> pos)
		{
			now = now -> next;
		}
		if (now -> pos == ptr -> pos)
		{
			now -> val += ptr -> val;
		}
		else
		{
			now = insert(now, pii(ptr -> pos, ptr -> val));
		}

		ptr = ptr -> next;
	}
}

void SRC::add(string & str)
{
	int id = FindStrID(str);
	SRC tmp(str, num_show);
	merge(tmp);
}