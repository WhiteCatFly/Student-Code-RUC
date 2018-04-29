#include <string>
#include <iostream>
#include <regex>
#include "Disposecmd.h"
#include "Reporterr.h"
#include "Parser.h"

int main(int argc,char * argv[]) // agrc !
{
	const string picture = "picture",text = "text",url = "url",title = "title",ALL = "ALL";
	const string src = "--src=file";
	string picture_filename,text_filename("text.txt"),title_filename("title.txt"),url_filename("urls.txt");
	string url_format("<a href=\"((http(s)?://)?(.)+?)\"(.)+?>");

	/* *** various of constructors ??? like this ??? */

	bool file_tag = (*++ argv == src);
	// Parser html(file_tag ? (*++ argv) : ((string)(*++ argv))); // type-forced transforming
	Parser html;
	if (file_tag)
		html = Parser(*++ argv);
	else
		html = Parser((string)(*++ argv));
	/* *** */

	char * ptr = NULL;
	for (int i = 0;i < argc - 3;i ++)
	{
		++ argv;
		if (*(ptr = *argv) != '-')
		{
			Report_option_err(ptr);
			break;
		}
		ptr ++;
		if (*ptr != '-') // -
		{
			/* wa keng.jpg*/
		}
		else // --
		{
			ptr ++;
			int pos = find_equalsign(ptr);
			if (pos != DEFAULT && *(ptr + pos + 1) == ' ')
			{
				Report_err();
				exit(1);
			}

			if (pos != DEFAULT)
				*(ptr + pos) = 0;

			if (ptr == picture)
			{
				if (pos != DEFAULT)
					picture_filename = (ptr + pos + 1);
				html.parse_picture(picture_filename);
			}
			else if (ptr == text)
			{
				if (pos != DEFAULT)
					text_filename = (ptr + pos + 1);
				html.parse_text(text_filename);
			}
			else if (ptr == title)
			{
				if (pos != DEFAULT)
					title_filename = (ptr + pos + 1);
				html.parse_title(title_filename);
			}
			else if (ptr == url)
			{
				if (pos != DEFAULT)
				{
					int pos_comma = find_comma(ptr + pos + 1);

					if (pos_comma == DEFAULT) // URL
					{
						url_format = /*ptr + pos + 1;*/Dispose_regex(ptr + pos + 1);
					}
					else // URL(ALL),filename
					{
						*(ptr + pos + 1 + pos_comma) = 0;
						if (*(ptr + pos + 1 + pos_comma + 1) == ' ')
						{
							Report_err();
							exit(1);
						}
						
						if ((ptr + pos + 1) != ALL)
							url_format = /*ptr + pos + 1;*/Dispose_regex(ptr + pos + 1);
						url_filename = (ptr + pos + 1 + pos_comma + 1);
					}
				}
				html.parse_url(url_filename,url_format);
			}
			else
				Report_option_err(ptr);
		}
	}
	
	return 0;
}