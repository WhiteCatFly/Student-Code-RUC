#include "crawl_url.h"

class HTML
{
	private:
		URL MyUrl;
		std::string Content, FilePath;
		int HrefPos;
		bool Success;
		int command(std::string order, std::string &para);
	public:
		HTML() {}
		HTML(const URL &url);
		bool ReadFromFile();
		bool DownloadSucceed();
		URL GetNextHref();
};

