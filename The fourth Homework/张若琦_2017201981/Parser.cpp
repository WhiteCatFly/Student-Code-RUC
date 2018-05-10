#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include "Parser.h"

string Parser :: itos(const int n) const
{
	static std :: stringstream sttr;
	sttr << n;
	string ret;
	sttr >> ret;

	sttr.clear();
	sttr.str(""); // empty the buffer
	return ret;
}

void Parser :: parse_picture(const string & file_name) const
{
	int cnt = 0;

	regex pattern("<img src=\"(\\/?)(.+?)\"(.*?)>");
	sregex_iterator iter(htmlfile_.begin(), htmlfile_.end(), pattern);
	sregex_iterator end;

	for (; iter != end; iter ++)
	{
		output_picture(url_ + iter -> str(2), file_name + itos(cnt ++));
	}
}

bool Parser :: is_white_character(const char ch) const
{
	return ch == '\n' || ch == ' ' || ch == '\t';
}

void Parser :: del_white_character(string & file) const
{
	int n = file.length();
	for (int i = 0; i < n; )
	{
		if (is_white_character(file[i]) && 
			is_white_character(file[i + 1]))
		{ 
			file.erase(i, 1);
			n --;
		}
		else
			i ++;
	}
}

/*
regex_replace return value type:   basic_string<charT> 

<!----> <script> <ruby>

abbr|acronym -> title
area -> alt
input -> name value

can't find base label in info.ruc.edu.cn/*
*/

void Parser :: parse_text(const string & file_name) const
{
	stringstream ostr;

	string file = htmlfile_;
	for (int pos = 0; (pos = file.find("<script", pos)) != string :: npos; ) // script
	{
		int pos_ed = file.find("</script>", pos);
		file.erase(pos, pos_ed - pos + 9);
	}
	for (int pos = 0; (pos = file.find("<ruby>", pos)) != string :: npos; ) // ruby
	{
		int pos_ed = file.find("</ruby>", pos);
		file.erase(pos, pos_ed - pos + 7);
	}

	regex patt_ann("<!--(.|\\n)*?-->"); // <!---->
	file = regex_replace(file, patt_ann, "");

	regex pattern("(<(!doctype|!DOCTYPE|a|A|/a|/A|abbr|ABBR|/abbr|/ABBR|acronym|ACRONYM|/acronym|/ACRONYM|address|ADDRESS|/address|/ADDRESS|applet|APPLET|/applet|/APPLET|area|AREA|/area|/AREA|article|ARTICLE|/article|/ARTICLE|aside|ASIDE|/aside|/ASIDE|audio|AUDIO|/audio|/AUDIO|b|B|/b|/B|base|BASE|/base|/BASE|basefont|BASEFONT|/basefont|/BASEFONT|bdi|BDI|/bdi|/BDI|bdo|BDO|/bdo|/BDO|big|BIG|/big|/BIG|blockquote|BLOCKQUOTE|/blockquote|/BLOCKQUOTE|body|BODY|/body|/BODY|br|BR|/br|/BR|button|BUTTON|/button|/BUTTON|canvas|CANVAS|/canvas|/CANVAS|caption|CAPTION|/caption|/CAPTION|center|CENTER|/center|/CENTER|cite|CITE|/cite|/CITE|code|CODE|/code|/CODE|col|COL|/col|/COL|colgroup|COLGROUP|/colgroup|/COLGROUP|command|COMMAND|/command|/COMMAND|datalist|DATALIST|/datalist|/DATALIST|dd|DD|/dd|/DD|del|DEL|/del|/DEL|details|DETAILS|/details|/DETAILS|dfn|DFN|/dfn|/DFN|dialog|DIALOG|/dialog|/DIALOG|dir|DIR|/dir|/DIR|div|DIV|/div|/DIV|dl|DL|/dl|/DL|dt|DT|/dt|/DT|em|EM|/em|/EM|embed|EMBED|/embed|/EMBED|fieldset|FIELDSET|/fieldset|/FIELDSET|figcaption|FIGCAPTION|/figcaption|/FIGCAPTION|figure|FIGURE|/figure|/FIGURE|font|FONT|/font|/FONT|footer|FOOTER|/footer|/FOOTER|form|FORM|/form|/FORM|frame|FRAME|/frame|/FRAME|frameset|FRAMESET|/frameset|/FRAMESET|h1|H1|/h1|/H1|h2|H2|/h2|/H2|h3|H3|/h3|/H3|h4|H4|/h4|/H4|h5|H5|/h5|/H5|h6|H6|/h6|/H6|head|HEAD|/head|/HEAD|header|HEADER|/header|/HEADER|hr|HR|/hr|/HR|html|HTML|/html|/HTML|i|I|/i|/I|iframe|IFRAME|/iframe|/IFRAME|img|IMG|/img|/IMG|input|INPUT|/input|/INPUT|ins|INS|/ins|/INS|kbd|KBD|/kbd|/KBD|keygen|KEYGEN|/keygen|/KEYGEN|label|LABEL|/label|/LABEL|legend|LEGEND|/legend|/LEGEND|li|LI|/li|/LI|link|LINK|/link|/LINK|main|MAIN|/main|/MAIN|map|MAP|/map|/MAP|mark|MARK|/mark|/MARK|menu|MENU|/menu|/MENU|menuitem|MENUITEM|/menuitem|/MENUITEM|meta|META|/meta|/META|meter|METER|/meter|/METER|nav|NAV|/nav|/NAV|noframes|NOFRAMES|/noframes|/NOFRAMES|noscript|NOSCRIPT|/noscript|/NOSCRIPT|object|OBJECT|/object|/OBJECT|ol|OL|/ol|/OL|optgroup|OPTGROUP|/optgroup|/OPTGROUP|option|OPTION|/option|/OPTION|output|OUTPUT|/output|/OUTPUT|p|P|/p|/P|param|PARAM|/param|/PARAM|pre|PRE|/pre|/PRE|progress|PROGRESS|/progress|/PROGRESS|q|Q|/q|/Q|rp|RP|/rp|/RP|rt|RT|/rt|/RT|s|S|/s|/S|samp|SAMP|/samp|/SAMP|section|SECTION|/section|/SECTION|select|SELECT|/select|/SELECT|small|SMALL|/small|/SMALL|source|SOURCE|/source|/SOURCE|span|SPAN|/span|/SPAN|strike|STRIKE|/strike|/STRIKE|strong|STRONG|/strong|/STRONG|style|STYLE|/style|/STYLE|sub|SUB|/sub|/SUB|summary|SUMMARY|/summary|/SUMMARY|sup|SUP|/sup|/SUP|table|TABLE|/table|/TABLE|tbody|TBODY|/tbody|/TBODY|td|TD|/td|/TD|textarea|TEXTAREA|/textarea|/TEXTAREA|tfoot|TFOOT|/tfoot|/TFOOT|th|TH|/th|/TH|thead|THEAD|/thead|/THEAD|time|TIME|/time|/TIME|title|TITLE|/title|/TITLE|tr|TR|/tr|/TR|track|TRACK|/track|/TRACK|tt|TT|/tt|/TT|u|U|/u|/U|ul|UL|/ul|/UL|var|VAR|/var|/VAR|video|VIDEO|/video|/VIDEO|wbr|WBR|/wbr|/WBR|o:p|O:P|/o:p|/O:P)( (.|\\n)*?)?( /)?>)");
	file = regex_replace(file, pattern, "");

	del_white_character(file);

	write_file(file, file_name);
}

void Parser :: parse_title(const string & file_name) const
{
	stringstream ostr;

	//regex pattern("<(p)> *(.+?) *<\\/(p)>");
	regex pattern("<(title)> *(.+?) *<\\/(title)>");
	sregex_iterator iter(htmlfile_.begin(), htmlfile_.end(), pattern);
	sregex_iterator end;

	for (; iter != end; iter ++)
	{
		ostr << iter -> str(2) << endl;
	}

	write_file(ostr, file_name);
}

void Parser :: parse_url(const string & file_name, const string & pattern_str) const
{
	stringstream ostr;

	regex pattern(pattern_str.c_str());
	sregex_iterator iter(htmlfile_.begin(), htmlfile_.end(), pattern);
	sregex_iterator end;

	for (; iter != end; iter ++)
	{
		const string url = (iter -> str(1));
		if (url.substr(0, 4) != "http" && (url.substr(0, url_.size() - 1) != url_.substr(0, url_.size() - 1)))
			ostr << url_;
		ostr << url << endl;
	}

	write_file(ostr, file_name);
}