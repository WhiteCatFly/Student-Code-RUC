#include "htmlparser.h"
using namespace std;

static void desdfs(Tag* cur_tag)
{
	for(Tag* p = cur_tag -> son(); p != NULL; p = p -> next()) desdfs(p);
	delete cur_tag;
}

static void cpdfs(Tag* &cur_tag, Tag* &tit_tag, const Tag* htm_tag, const Tag* htm_tit)
{
	if(cur_tag == NULL) cur_tag = new Tag;
	*cur_tag = *htm_tag;
	if(htm_tag == htm_tit) tit_tag = cur_tag;	
	Tag* son, *htm_son;
	for(son = cur_tag -> son(), htm_son = htm_tag -> son(); htm_son != NULL; son = son -> next(), htm_son = htm_son -> next()) cpdfs(son, tit_tag, htm_son, tit_tag);
}

HtmlParser::HtmlParser(const HtmlParser& htm)
{
	_root = cur_tag = NULL;
	cpdfs(_root, tit_tag, htm._root, htm.tit_tag);
	r_mode = htm.r_mode;
	init_url = htm.init_url, text = htm.text;
}

HtmlParser::HtmlParser(string str, string url, int mode)
{
	r_mode = mode;
	init_url = url;
	if(r_mode == 0)
	{
		file = ifstream(str);
		if(!file.is_open())
		{
			cerr << "file can't be opened.\n";
			return;
		}
	}
	else sfile = stringstream(str);
	_root = cur_tag = new Tag;
	_root -> url = url;
	Init();
}

HtmlParser& HtmlParser::operator =(const HtmlParser& htm)
{
	desdfs(_root);
	_root = cur_tag = NULL;
	cpdfs(_root, tit_tag, htm._root, htm.tit_tag);
	r_mode = htm.r_mode;
	init_url = htm.init_url, text = htm.text;
	return *this;
}

HtmlParser::~HtmlParser()
{
	desdfs(_root);
	_root = cur_tag = tit_tag = NULL;
}

inline void HtmlParser::ParseStrs(const string &str, int l, int r) //[l,r)
{
	string temp = str.substr(l, r - l);
	if(regex_match(temp, s_re)) return;  
	cur_tag -> strs.push_back(temp);
}

static inline int GetChsum(const string &s, char ch)
{
	int l = s.length(), sum = 0;
	for(int i = 0;i < l; ++i) if(s[i] == ch) sum++;
	return sum;
}

static inline void PrintTag(Tag* ct)
{
	cerr << "cur_tag: " << ct -> name << endl;
	for(auto i = ct -> attrs.begin(); i != ct -> attrs.end(); ++i) cerr << i -> first << "=" << i -> second << endl;
	cerr << endl;
}

void HtmlParser::ParseEndtag(string str)
{
	//transform(str.begin(), str.end(), str.begin(), ::tolower);
	int t_len = str.length();
	str.erase(t_len - 1, 1).erase(0, 2);
	if(str == cur_tag -> name)
	{
		if(cur_tag -> _fa != NULL)  cur_tag = cur_tag -> _fa;
		else cerr << "error: cur_tag: " << str << endl;
	}
	else
	{
		if(cur_tag -> name != "img" && cur_tag -> name != "meta" && cur_tag -> name != "input" && cur_tag -> name != "link")
		{
			cerr << "error: tag "<< str << " begin&end not suit " << endl;
			PrintTag(cur_tag);
		}
		
		while(cur_tag != _root && str != cur_tag -> name) cur_tag = cur_tag -> _fa;
		if(cur_tag == _root) cerr << "error: tag " << str << " begin not found" << endl;
		else cur_tag = cur_tag -> _fa;
	}
}

void HtmlParser::ParseCmt(string str)
{
	if(str.find("<!--") == string::npos || str.find("-->") == string::npos)
	{
		cerr << "error: comments invalid: " << str << endl;
		return;
	}
	int t_len = str.length();
	str.erase(t_len - 3, 3).erase(0, 4);
	cur_tag -> cmts.push_back(str);
	
}

static inline void DelQuota(string& str)
{
	if(str[0] == '\'' || str[0] == '"') str.erase(0, 1);
	if(str.back() == '/') str.erase(str.length() - 1, 1);
	if(str.back() == '\'' || str.back() == '"') str.erase(str.length() - 1, 1);	
}

void HtmlParser::ParseTag(string str)
{
	//transform(str.begin(), str.end(), str.begin(), ::tolower);
	Tag* son_tag = new Tag;
	son_tag -> _fa = cur_tag;
	son_tag -> _nxt = cur_tag -> _son;
	if(cur_tag -> _son != NULL) cur_tag -> _son -> _pre = son_tag;
	cur_tag -> _son = son_tag;
	cur_tag = son_tag;
	cur_tag -> url = init_url;

	Tag* ct = cur_tag;	
	int num = 0, att_anc = 0, qu_sum = 0, equ_pos = 0;
    smatch att;
	string att_str, lef_str, rig_str, temp;
	att_anc = 0, qu_sum = 0;
	while(regex_search(str, att, str_re))
	{
		for(int j = 0;j < (int)att.size(); ++j)
		{
			att_str = att[j]; num++;
			if(num == 1)
			{
				ct -> name = att[j];
				if(ct -> name == "title") tit_tag = ct;
			}
			else
			{
				if(!att_anc)
				{
					lef_str = att[j];
					if(att_str == "=") att_anc = 1;
					else if(att_str.find("=", 0) != string::npos)
					{
						equ_pos = att_str.find("=", 0);
						lef_str = att_str.substr(0, equ_pos);
						rig_str = att_str.substr(equ_pos + 1, att[j].length() - 1 - equ_pos);
						qu_sum += GetChsum(att[j], '"') + GetChsum(att[j], '\''); //double & single total
						att_anc = 1;
						if(qu_sum % 2 == 0)
						{
							DelQuota(rig_str);
							ct -> attrs[lef_str] = rig_str;
							qu_sum = 0;
							lef_str.clear(), rig_str.clear();
							att_anc = 0;							
						}
					}
				}
				else
				{
					qu_sum += GetChsum(att[j], '"') + GetChsum(att[j], '\''); //double & single total
					rig_str += str.substr(0, att.position(j) + att_str.length());
					if(qu_sum % 2 == 0)
					{
						DelQuota(rig_str);
						ct -> attrs[lef_str] = rig_str;
						qu_sum = 0;
						lef_str.clear(), rig_str.clear();
						att_anc = 0;
					}	
				}
				
			}
			
		}
		if((int)att.size() > 0) temp = att[att.size() - 1];		
		str = att.suffix().str();
	}		
	if(att_anc || qu_sum) cerr << "error: not proper in the tag <" << ct -> name << ">" << endl;
	
	if(temp[temp.length() - 1] == '/') cur_tag = cur_tag -> _fa; 
	
}

void HtmlParser::Init()
{
	smatch sm;
	string temp(""), str(""), sm_str("");
	text.clear();
	int last;
	while((!r_mode && !file.eof()) || (r_mode && !sfile.eof()))
	{
		if(r_mode == 0) getline(file, temp);
		else getline(sfile, temp);
		last = -1;
		for(int i = 0; i < (int)temp.length(); ++i)
		{
			if(temp[i] == '\r')
			{
				if(last >= 0) text += temp.substr(last, i - last);
				last = -1;
			}
			else if(last < 0) last = i; //erase \r
		}
		if(last >= 0) text += temp.substr(last);
	}	

	str = text;
	int num = 0;
   	while(regex_search(str, sm, tag_re))
   	{
   		for(int i = 0;i < (int)sm.size(); ++i)
   		{
			num++;
   			sm_str = sm[i];
   			ParseStrs(str, 0, sm.position(i));
				
	   		if(sm_str.find("!DOCTYPE") != string::npos) continue;
	   		else if(sm_str[1] == '/') ParseEndtag(sm_str);
   			else if(sm_str[1] == '!') ParseCmt(sm_str);
   			else if(sm_str.find("<br") != string::npos) continue;
   			else ParseTag(sm_str);
   		}
   		str = sm.suffix().str();
			
	}
	if(str != "") ParseStrs(str, 0, str.length());
	
	if(r_mode == 0) file.close();else sfile.str("");
}

