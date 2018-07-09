#include "CWSPOS.h"

using namespace std;

int main()
{
	string str;
	vector<string> cws, pos;
	
	cout << "输入您的句子：" << endl;
	getline(cin, str);
	CWSPOS cwspos(str);
	
	cws = cwspos.GetCWS();
	pos = cwspos.GetPOS();
	
	for(int i = 0; i < cws.size(); i++)
		cout << cws[i] << ' ';
	cout << endl;
	
	for(int i = 0; i < cws.size(); i++)
		cout << cws[i] << pos[i] << ' ';
	cout << endl;
	
	return 0;
}
