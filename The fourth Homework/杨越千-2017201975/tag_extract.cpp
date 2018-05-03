#include "htmlparser.h"
using namespace std;

inline bool IsLink(const string& str) {return regex_match(str, link_re); }
inline bool IsImage(const string& str) {return regex_match(str, image_re); }
inline bool IsSound(const string& str) {return regex_match(str, sound_re); }
inline bool IsWord(const string& str) {return regex_match(str, word_re); }

static void Creat(string str, const string& path, const string& url)
{
	string u_str = str;
	smatch endstr;
	string s0("");
	static char cmd[cmd_maxlen];
	
	reverse(str.begin(), str.end());
	regex_search(str, endstr, end_re);
	for(int i = 0;i < (int)endstr.size(); ++i)
	{
		memset(cmd, 0, sizeof(cmd));
		s0 = endstr[i]; //end with / (not reversed)
		reverse(s0.begin(), s0.end());
		//if(s0.back() == '"' || s0.back() == '\'') s0.erase(s0.length() - 1, 1);
		if(u_str.find("http") == string::npos) u_str = url + "/" + u_str;
		sprintf(cmd, "wget -q -O '%s' '%s' -T 10 -t 2", (path + s0).c_str(), u_str.c_str());
		system(cmd);
	}
}

static int dfs(Tag* ct, int mode, ofstream& ofile, const string& url)
{
	int link_sum = 0;
	if(ct -> attrs.count("href")) //only 'href'
	{
		if(IsLink(ct -> attrs["href"]))
		{
			link_sum++;
			if(ct -> attrs["href"].find("http") == string::npos) ofile << url + '/' + ct -> attrs["href"] << endl;
			else ofile << ct -> attrs["href"] << endl;				
		}
	}	
	for(Tag* p = ct -> son();p != NULL;p = p -> next())
		link_sum += dfs(p, mode, ofile, url);
	return link_sum;
}

static int dfs(Tag* ct, int mode, const string& path, const string& url)
{
	int link_sum = 0;
	bool anc = 0;
	for(auto i = ct -> strs.begin(); i != ct -> strs.end(); ++i)
	{
		if(mode == Tag::_IMAGE) anc = IsImage(*i);
		else if(mode == Tag::_SOUND) anc = IsSound(*i);
		else anc = IsWord(*i);
		if(anc)
		{
			link_sum++;
			Creat(*i, path, url);
		}		
	}
	for(auto i = ct -> attrs.begin(); i != ct -> attrs.end(); ++i)
	{
		if(mode == Tag::_IMAGE) anc = IsImage(i -> second);
		else if(mode == Tag::_SOUND) anc = IsSound(i -> second);
		else anc = IsWord(i -> second);
		if(anc)
		{
			link_sum++;
			Creat(i -> second, path, url);
		}		
	}
	
	for(Tag* p = ct -> son(); p != NULL; p = p -> next())
		link_sum += dfs(p, mode, path, url);
	return link_sum;
}

static void OpenPath(string &path, const string &file = "")
{
	static char cmd[cmd_maxlen];
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "mkdir -p %s", path.c_str());
	system(cmd);
}

int Tag::links(string path, const string& file)
{
	OpenPath(path, file);	
	if(path.back() != '/') path += '/';
	path += file;
	ofstream ofile(path);	
	if(!ofile.is_open())
	{
		cerr << "error: in links() path "<< path << " not valid." << endl;
		return 0;
	}

	int num = dfs(this, Tag::_LINK, ofile, this -> url);
	return num;
}

int Tag::images(const string& path)
{
	static char cmd[cmd_maxlen];
	memset(cmd, 0, sizeof(cmd));	
	sprintf(cmd, "mkdir -p %s", path.c_str());
	system(cmd);	
	int num = dfs(this, Tag::_IMAGE, path, url);
	return num;
}

int Tag::sounds(const string& path)
{
	static char cmd[cmd_maxlen];
	memset(cmd, 0, sizeof(cmd));	
	sprintf(cmd, "mkdir -p %s", path.c_str());
	system(cmd);	
	int num = dfs(this, Tag::_SOUND, path, url);
	return num;
}

int Tag::words(const string& path)
{
	static char cmd[cmd_maxlen];
	memset(cmd, 0, sizeof(cmd));	
	sprintf(cmd, "mkdir -p %s", path.c_str());
	system(cmd);		
	int num = dfs(this, Tag::_WORD, path, url);
	return num;
}
