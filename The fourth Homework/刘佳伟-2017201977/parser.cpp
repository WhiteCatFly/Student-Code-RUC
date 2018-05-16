#include "parser.h"

using namespace std;

const char *ESL = "ENDOFSINGLELABEL";
const char *SL[] = {"br", "hr", "img", "input", "param", "meta", "link", "!doctype", ESL};
set<string> Parser::LabelKey;

void Parser::Output(const std::string &code, int tabs, ostringstream &ostr)
{
	for(int i = 1; i <= tabs; i++)
		ostr << '\t';
	
	ostr << code << endl;
}

string Parser::BigSmallSame(string s)
{
	for(int i = 0; i < s.size(); i++)
		if(s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 'a' - 'A';
	return s;		
}

Parser::Parser(const char *filename)
{
//	cout << "Come" << endl;
	ifstream fin(filename);
	string buf;

	while(getline(fin, buf))
		SourceCode += buf + "\n";
	
	fin.close();
	
	Process();
	
	string foutname = "TreeStructure_";
	foutname += filename;
	foutname += ".out";
	ofstream fout(foutname.c_str());
	fout << SourceCode;
	fout.close();
}

Parser::Parser(const string &code)
{
	SourceCode = code;
	Process();
	
	ofstream fout("TreeStructure_UserHtmlCode.out");
	fout << SourceCode;
	fout.close();
}


void Parser::Process()
{
	stack<string> StackOfLabel;
	stack<string> StackOfunProcess;
	int depth = 0, unProcess = 0;
	string label;
	bool MyNewLine = false, InLabel = false;
	
	ostringstream osout;
	for(int i = 0; i < SourceCode.size(); i++)
	{
		if(unProcess > 0)
		{
			if(Parser::BigSmallSame(SourceCode.substr(i, StackOfunProcess.top().size())) == StackOfunProcess.top())
			{
				if(SourceCode[i] == '<')
				{
					osout << endl;
					for(int j = 1; j <= depth; j++)
						osout << '\t';
				}
				StackOfunProcess.pop();
				unProcess--;
			}
			osout << SourceCode[i];
		}
		else
		{
			if(SourceCode[i] == '\n' || SourceCode[i] == '\r' || MyNewLine)
			{
				osout << endl;
				for(int j = 1; j <= depth; j++)
					osout << '\t';
				for(; SourceCode[i] == '\n' || SourceCode[i] == '\r' || SourceCode[i] == '\t' || SourceCode[i] == ' '; i++)
					;
				i--;
				MyNewLine = false;
			}	
			else if(SourceCode[i] == '\'' || SourceCode[i] == '"')
			{
				osout << SourceCode[i];
				string chartostring = "";
				chartostring += SourceCode[i];
				StackOfunProcess.push(chartostring);
			//	cout << "*****************" << SourceCode[i] << "******************" << endl;
				unProcess++;
			}
			else if(SourceCode[i] == '<' && SourceCode.size() - i >= 7 && Parser::BigSmallSame(SourceCode.substr(i + 1, 6)) == "script")
			{
				osout << SourceCode[i];
				StackOfunProcess.push("</script>");
				unProcess++;
			}
			else if(SourceCode[i] == '<' && SourceCode.size() - i >= 4 && SourceCode.substr(i + 1, 3) == "!--")
			{
				osout << SourceCode[i];
				StackOfunProcess.push("-->");
				unProcess++;
			}
			else if(SourceCode[i] == '<' && SourceCode[i + 1] == '/' && Parser::BigSmallSame(SourceCode.substr(i + 2, StackOfLabel.top().size())) == StackOfLabel.top())
			{
				osout << endl;
				for(int j = 1; j <= depth; j++)
					osout << '\t';
				osout << SourceCode[i];
				StackOfLabel.pop();
				depth--;
			}
			else if(InLabel && SourceCode[i] == '>')
			{
				osout << SourceCode[i];
				InLabel = false;
				MyNewLine = true;
			}
			else if(SourceCode[i] == '<')
			{
			//	cout << "##########################FIND Label############################" << endl;
				bool IsSL = false;
				for(int j = 0; strcmp(ESL, SL[j]) != 0; j++)
					if(SourceCode.size() - i >= strlen(SL[j]) + 1 && strcmp(SL[j] ,Parser::BigSmallSame(SourceCode.substr(i + 1, strlen(SL[j]))).c_str()) == 0)
					{
				//		cout << "##########################FIND SL############################" << endl;
						IsSL = true;
						break;
					}
				if(IsSL)
					osout << SourceCode[i];
				else
				{
				//	cout << "##########################FIND DL############################" << endl;
					int j = i;
					for(; j < SourceCode.size() && SourceCode[j] != ' ' && SourceCode[j] != '>'; j++)
						;
					StackOfLabel.push(SourceCode.substr(i + 1, j - i - 1));
					depth++;
					osout << SourceCode.substr(i, j - i + 1);
					i = j;
					if(SourceCode[j] == '>')
						MyNewLine = true;
					else
						InLabel = true;
				}
			}
			else
				osout << SourceCode[i];
		}
	}
	SourceCode = osout.str();
}
