#include <string>
#include <iostream>
#include <regex>
#include "Disposecmd.h"
#include "Reporterr.h"
#include "Parser.h"

int main(int argc, char * argv[]) // agrc !
{
	const string picture = "picture", text = "text", url = "url", url_save = "url-save", title = "title";
	const string src = "--src=file";
	string picture_filename, text_filename("text.txt"), title_filename("title.txt"), url_filename("urls.txt");
	string url_format("<a href=\"((http(s)?://)?(.)+?)\"(.)+?>");

	/* help*/
	string help1 = "--help", help2 = "-h";
	if (*(argv + 1) == help1 || *(argv + 1) == help2)
		help_user();
	/* *** */

	/* *** various of constructors ??? like this ??? *** */

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
			int opt_len = strlen(ptr);
			if (opt_len > 1 || i == argc - 4 || i < argc - 4 && **(argv + 1) == '-') 
			// (short options combination | *) -> no arguments
			{
				for (int j = 0; j < opt_len; ptr ++, j ++)
					switch (*ptr)
					{
						case 't':
							html.parse_title(title_filename);
							break;
						case 'w':
							html.parse_text(text_filename);
							break;
						case 'p':
							html.parse_picture(picture_filename);
							break;
						case 's':
							html.parse_url(url_filename, url_format);
							break;
						default :
							Report_option_err(*ptr);
					}
			}
			else // with arguments
			{
				++ argv;
				++ i;
				switch (*ptr)
				{
					case 't':
						title_filename = *argv;
						html.parse_title(title_filename);
						break;
					case 'w':
						text_filename = *argv;
						html.parse_text(text_filename);
						break;
					case 'p':
						picture_filename = *argv;
						html.parse_picture(picture_filename);
						break;
					case 's':
						url_filename = *argv;
						html.parse_url(url_filename, url_format);
						break;
					case 'u':
						url_format = Dispose_regex(*argv);
						break;
					default :
						Report_err();
				}
			}
		}
		else // --
		{
			ptr ++;
			int pos = find_equalsign(ptr);
			if (pos != DEFAULT && *(ptr + pos + 1) == 0)
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
					url_format = Dispose_regex(ptr + pos + 1);
				else
					Report_err();
			}
			else if (ptr == url_save)
			{
				if (pos != DEFAULT)
					url_filename = (ptr + pos + 1);
				html.parse_url(url_filename, url_format);
			}
			else
				Report_option_err(ptr);
		}
	}
	
	return 0;
}