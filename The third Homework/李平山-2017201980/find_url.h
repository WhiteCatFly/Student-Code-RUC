#ifndef FIND_URL_H
#define FIND_URL_H
#include <string.h>
#include <set>
#include <queue>

using std::string;

//inline string add(const string&,string&);
//void read(string&);
class request{
	private:
		int sleep_time;
	public:
		std::queue<string> Q;
		std::set<string> visited;
		request(int time = 10000) {
			sleep_time = time;
			while(!Q.empty())  
				Q.pop();
			visited.clear();
			}
		~request() {}
		
		void read(string&);
		inline string add(const string&,string&);
		inline void openfile(std::ifstream&,const string&);

};
#endif
