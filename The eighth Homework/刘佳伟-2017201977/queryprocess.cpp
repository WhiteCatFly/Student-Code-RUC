#include "queryprocess.h"

using namespace std;

QueryProcess::QueryProcess(const string &str)
{
	void * engine = segmentor_create_segmentor("ltp_data_v3.4.0/cws.model");
	vector<string> query_to_key;
	
	segmentor_segment(engine, str, query_to_key);
	segmentor_release_segmentor(engine);
	
	unordered_map<int, int> merge;
	
	for(int i = 0; i < query_to_key.size(); i++)
	{
		if(Keys::keys.find(query_to_key[i]) != Keys::keys.end() && Keys::forbidden.find(query_to_key[i]) == Keys::forbidden.end())
		{
			key.push_back(query_to_key[i]);
		//	cout << "Find " << query_to_key[i] << Keys::keys[query_to_key[i]].size() << endl;
			for(int j = 0; j < Keys::keys[query_to_key[i]].size(); j++)
				merge[Keys::keys[query_to_key[i]][j]] = 1;
		}
	}
	
	for(unordered_map<int, int>::iterator iter = merge.begin(); iter != merge.end(); iter++)
		pagefile.push_back(iter->first);
	
	//cout << pagefile.size() << endl;
}

vector<string> & QueryProcess::getKey()
{
	return key;
}

vector<int> & QueryProcess::getPagefile()
{
	return pagefile;
}
