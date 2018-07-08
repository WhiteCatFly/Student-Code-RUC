#include <iostream>
#include <fstream>

#include "THULAC/include/thulac.h"

using namespace std;

void print(const THULAC_result & result, bool seg_only, char separator)
{
	for (int i = 0; i < result.size() - 1; i ++)
	{
		if(i != 0) cout << " ";
		if(seg_only)
			cout << result[i].first;
		else
			cout << result[i].first << separator << result[i].second;
	}
	cout << endl;
}

int main()
{
	char model_path_[] = "THULAC/models/";
	char * model_path_char = model_path_;
	char * user_specified_dict_name = NULL;
	int seg_only = 1;
	int useT2S = 0;
	int useFilter = 0;

	char separator = '_';

	THULAC lac;
	lac.init(model_path_char, user_specified_dict_name, seg_only, useT2S, useFilter);

	auto cin_rdbuf = cin.rdbuf();
	auto cout_rdbuf = cout.rdbuf();

	ifstream infile("test.txt");
	cin.rdbuf(infile.rdbuf());
	ofstream outfile("res.txt");
	cout.rdbuf(outfile.rdbuf());

	string raw;
	THULAC_result result;
	while(getline(cin, raw))
	{
		lac.cut(raw, result);
		print(result, seg_only, separator);
	}

	infile.close();
	outfile.close();

	cin.rdbuf(cin_rdbuf);
	cout.rdbuf(cout_rdbuf);

	return 0;
}
