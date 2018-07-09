#include "main.h"

using namespace std;

bool cmp(pair<int, double> &a, pair<int, double> &b)
{
	return a.second > b.second;
}

int main()
{
	initialize();
	string query;
	
	cin >> query;
	QueryProcess qp(query);
	vector<pair<int, double> > result;
	vector<double> w;
	
	for(int i = 0; i < qp.getKey().size(); i++)
	{
		TfiDf td(qp.getKey()[i], 0);
		w.push_back(td.getResultQue(query));
	//	cerr << w[i] << endl;
	}
	
	if(qp.getPagefile().size() > 0)
	{
		pair<int, double> r;
		for(int i = 0; i < qp.getPagefile().size(); i++)
		{
			r = make_pair(i, 0.0);
			result.push_back(r);
			for(int j = 0; j < qp.getKey().size(); j++)
			{
				TfiDf td(qp.getKey()[j], qp.getPagefile()[i]);
				result[i].second += w[j] * td.getResult();
			}
		}
		
		sort(result.begin(), result.end(), cmp);
		
		
		/*for(int i = 0; i < result.size(); i++)
			cout << Keys::filename[qp.getPagefile()[result[i].first]] << ' ' << result[i].second << endl;*/
		
		cout << "共找到 " << result.size() << " 条结果，下面显示前" << ((result.size() > 10) ? 10 : result.size()) << "条，并将所有相关网页的地址保存为result.out文件。" << endl;
		for(int i = 0; i < min(10, (int)result.size()); i++)
			SearchKey(cout, qp.getPagefile()[result[i].first], qp.getKey());
			
		ofstream fout("result.out");
		for(int i = 0; i < result.size(); i++)
			fout << Keys::filename[qp.getPagefile()[result[i].first]] << endl;
		fout.close();
	}
	else
	{
		cout << "\033[31m\033[1m根据相关法律法规，部分搜索结果未予显示。\033[0m" << endl;
		ofstream fout("result.out");
		fout << "根据相关法律法规，部分搜索结果未予显示。" << endl;
		fout.close();
	}
	
	return 0;
}
