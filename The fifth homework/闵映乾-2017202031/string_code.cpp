#include <iostream>
#include <cstring>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;


class String{
	private:
		char * str;
		int len;
		static int num_strings;
		static const int CINLIM = 80;
	public:
		String(const char * in_char);
		String();
		String(const String & in_string);
		~String();
		int length() const {return len;}
		const char * show() const {return str;}
		String & operator=(const String & let_str);
		String & operator=(const char * let_char);
		char & operator[](int num) {return str[num];}
		static const int show_lim()  {return CINLIM;}
		static int show_num_strings() {return num_strings;}
		const char & operator[](int number) const {return str[number];}
		friend istream & operator<<(istream & is , String & input_string);
		friend ostream & operator>>(ostream & os , const String & output_string);
		friend bool operator<(const String  & cmp_str1 , const String & cmp_str2);
		friend bool operator>(const String & cmp_str3 , const String & cmp_str4);
		friend bool operator==(const String & cmp_str5 , const String & cmp_str6);
	
};

int String::num_strings = 0;
String::String(const char * in_char){
	num_strings ++;
	len = std::strlen(in_char);
	str = new char [len + 1];
	std::strcpy(str , in_char);
}

String::String(){
	len = 0;
	num_strings++;
	str = new char [1];
	str[0] = '\0';
}

String::String(const String & in_string){
	num_strings++;
	len = in_string.length();
	str = new char [len + 1];
	strcpy(str , in_string.show());
}

String::~String(){
	num_strings--;
	delete [] str;
}

String & String::operator=(const String & let_str){
	delete [] str;
	len = let_str.length();
	str = new char [len+1];
	std::strcpy(str , let_str.show());
	return *this;
}

String & String::operator=(const char * let_char){
	delete [] str;
	len = std::strlen(let_char);
	str = new char [len + 1];
	std::strcpy(str , let_char);
	return *this;
}

istream & operator>>(istream & is , String & input_string){
	char temp[String::show_lim()];
	is.get(temp , String::show_lim());
	if(is)
		input_string = temp;
	while (is && is.get() != '\n')
		continue;
	return is;
}

ostream & operator<<(ostream & os , const String & output_string){
	os << output_string.show();
	return os;
}

bool operator < (const String & cmp_str1 , const String & cmp_str2){
	return (std::strcmp(cmp_str1.show() , cmp_str2.show()) < 0);
}

bool operator > (const String & cmp_str3 , const String & cmp_str4){
	return cmp_str3 < cmp_str4;
}

bool operator == (const String & cmp_str5 , const String & cmp_str6){
	return (std::strcmp(cmp_str5.show() , cmp_str6.show()) == 0);
}






void callme1(String & in);
void callme2(String input);



int main(){
	using std::endl;
	{
		cout << "Starting an inner block.\n";
		String headline1("Celery Stalks at Midnight");
		String headline2("Lettuce Prey");
		String sports("Spinach Leaves Bowl for Dollars");
		cout << "headline1: " << headline1 << endl;
		cout << "headline2: " << headline2 << endl;
		cout << "sports: " << sports << endl;
		callme1(headline1);
		cout << "headline1: " << headline1 << endl;
		callme2(headline2);
		cout << "headline2: " << headline2 << endl;
		cout << "Initialize one object to another:\n";
		String sailor = sports;
		cout << "sailor: " << sailor << endl;
		cout << "Assign one object to another:\n";
		String knot;
		knot = headline1;
		cout << "knot: " << knot << endl;
		cout << "Exiting the block.\n" ;
	}
	cout << "End of main()\n";
	
	return 0;
}
void callme1(String & in){
	cout << "String passed by reference:\n";
	cout << "    \""<< in << "\"\n";
}
void callme2(String input){
	cout << "String passed by value:\n";
	cout << "    \"" << input << "\"\n";
}


































