#ifndef DOWNLOAD_H_INCLUDED
#define DOWNLOAD_H_INCLUDED

#include <string>
 
class order{
	private:
		static int file_number;
		const static int option_len = 3;
		std::string m_limit_name;
		double m_per_time;
		int m_number;
		double m_sleep_time;
	public:
		order() {}
		order(const int number,const char ** value);
		void download(const std::string &web_page) const;
		void work(const std::string &temp, const int kind);
		std::string get_limit_name() const {return m_limit_name;}
		~order() {}
};

inline static void wrong_put();
inline static double stringtof();
inline static int strington();

//int order::file_number = 0;
const std::string option[4] = {"-L=", "-T=", "-N=", "-S="};
//const int order::option_len;
#endif
