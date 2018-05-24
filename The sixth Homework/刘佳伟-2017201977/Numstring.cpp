#include "Numstring.h"

using namespace std;

char Numstring::Type(const char *form)
{
	for(int i = 0; form[i] != '\0'; i++)
	{
		if(form[i] == 'd')
			return 'd';
		else if(form[i] == 'f')
			return 'f';
	}
	
	return ' ';
}

bool Numstring::Plus(const char *form)
{
	for(int i = 0; form[i] != '\0'; i++)
		if(form[i] == '+')
			return true;
	return false;
}

bool Numstring::Minus(const char *form)
{
	for(int i = 0; form[i] != '\0'; i++)
		if(form[i] == '-')
			return true;
	return false;
}

bool Numstring::Space(const char *form)
{
	for(int i = 0; form[i] != '\0'; i++)
		if(form[i] == ' ')
			return true;
	return false;
}

int Numstring::Accuracy(const char *form)
{
	int i = 0, result = 0;
	for(; form[i] != '\0'; i++)
		if(form[i] == '.')
			break;
	
	if(form[i] == '\0')
		return 6;
	
	int j = i + 1;
	for(; form[j] >= '0' && form[j] <= '9'; j++)
		result = result * 10 + form[j] - '0';
		
	if(j == i + 1)
		return 6;
	return result;
}

int Numstring::IntAccuracy(const char *form)
{
	int i = 0, result = 0;
	for(; form[i] != '\0'; i++)
		if(form[i] == '.')
			break;
	
	if(form[i] == '\0')
		return -1;
	
	int j = i + 1;
	for(; form[j] >= '0' && form[j] <= '9'; j++)
		result = result * 10 + form[j] - '0';
		
	if(j == i + 1)
		return -1;
	return result;
}

int Numstring::Width(const char *form)
{
	int i = 0, result = 0;
	for(; form[i] != '\0'; i++)
		if((form[i] >= '0' && form[i] <= '9') || form[i] == '.')
			break;
	
	if(form[i] == '\0' || form[i] == '.')
		return result;
	
	for(int j = i; form[j] >= '0' && form[j] <= '9'; j++)
		result = result * 10 + form[j] - '0';
	
	return result;
}

Numstring::Numstring()
{
	str = new char;
	*str = '\0';
	len = 0;
	floatdigit = 0;
	
	cout << "数据内部信息：" << str << endl << len << ' ' << floatdigit << endl << endl;
}

Numstring::Numstring(const char *num)
{
	len = strlen(num);
	str = new char[len + 1];
	strcpy(str, num);
	
	int i = 0;
	for(; i < len; i++)
		if(num[i] == '.')
		{
			i++;
			break;
		}
		
	floatdigit = len - i;

	cout << "数据内部信息：" << str << endl << len << ' ' << floatdigit << endl << endl;
}

Mystring Numstring::Print(const char *form)
{
	char *result = new char[len + 1], *new_str;
	strcpy(result, str);
	int result_len = len;
	
	if(Type(form) == 'f')
	{
		if(Accuracy(form) > floatdigit)
		{
			if(floatdigit > 0)
			{
				new_str = new char[result_len + Accuracy(form) - floatdigit + 1];
				strcpy(new_str, result);
				for(int i = result_len; i < result_len + Accuracy(form) - floatdigit; i++)
					new_str[i] = '0';
				new_str[result_len + Accuracy(form) - floatdigit] = '\0';
				
				result_len += Accuracy(form) - floatdigit;
				delete []result;
				result = new char[result_len + 1];
				strcpy(result, new_str);
				delete []new_str;
			}
			else
			{
				new_str = new char[result_len + Accuracy(form) - floatdigit + 2];
				strcpy(new_str, result);
				new_str[result_len] = '.';
				for(int i = result_len + 1; i < result_len + Accuracy(form) - floatdigit; i++)
					new_str[i] = '0';
				new_str[result_len + Accuracy(form) - floatdigit + 1] = '\0';
				
				result_len += Accuracy(form) - floatdigit + 1;
				delete []result;
				result = new char[result_len + 1];
				strcpy(result, new_str);
				delete []new_str;	
			}
		}
		else if(Accuracy(form) < floatdigit)
		{
			if(result[len - floatdigit + Accuracy(form)] <= '4')
			{
				if(Accuracy(form) > 0)
				{
					new_str = new char[result_len + 1];
					strcpy(new_str, result);
					new_str[result_len - floatdigit + Accuracy(form)] = '\0';
					
					result_len -= floatdigit - Accuracy(form);
					delete []result;
					result = new char[result_len + 1];
					strcpy(result, new_str);
					delete []new_str;
				}
				else
				{
					new_str = new char[result_len + 1];
					strcpy(new_str, result);
					new_str[result_len - floatdigit + Accuracy(form) - 1] = '\0';
					
					result_len -= floatdigit - Accuracy(form) + 1;
					delete []result;
					result = new char[result_len + 1];
					strcpy(result, new_str);
					delete []new_str;
				}
			}
			else
			{
				int jw = 0;
				for(int i = len - floatdigit + Accuracy(form) - 1; i >= 0; i--)
					if(result[i] >= '0' && result[i] <= '9')
					{
						if(result[i] == '9')
						{
							jw = 1;
							result[i] = '0';
						}
						else
						{
							jw = 0;
							result[i]++;
							break;
						}
					}
				
				if(jw == 0)
				{
					if(Accuracy(form) > 0)
					{
						new_str = new char[result_len + 1];
						strcpy(new_str, result);
						new_str[result_len - floatdigit + Accuracy(form)] = '\0';
						
						result_len -= floatdigit - Accuracy(form);
						delete []result;
						result = new char[result_len + 1];
						strcpy(result, new_str);
						delete []new_str;
					}
					else
					{
						new_str = new char[result_len + 1];
						strcpy(new_str, result);
						new_str[result_len - floatdigit + Accuracy(form) - 1] = '\0';
						
						result_len -= floatdigit - Accuracy(form) + 1;
						delete []result;
						result = new char[result_len + 1];
						strcpy(result, new_str);
						delete []new_str;
					}
				}
				else
				{
					if(Accuracy(form) > 0)
					{
						new_str = new char[result_len + 2];
						if(result[0] >= '0' && result[0] <= '9')
						{
							new_str[0] = '1';
							strcpy(new_str + 1, result);
							new_str[result_len - floatdigit + Accuracy(form) + 1] = '\0';
						}
						else
						{
							new_str[0] = result[0];
							new_str[1] = '1';
							strcpy(new_str + 2, result + 1);
							new_str[result_len - floatdigit + Accuracy(form) + 1] = '\0';
						}
						
						result_len -= floatdigit - Accuracy(form) - 1;
						delete []result;
						result = new char[result_len + 1];
						strcpy(result, new_str);
						delete []new_str;
					}
					else
					{
						new_str = new char[result_len + 2];
						if(result[0] >= '0' && result[0] <= '9')
						{
							new_str[0] = '1';
							strcpy(new_str + 1, result);
							new_str[result_len - floatdigit + Accuracy(form)] = '\0';
						}
						else
						{
							new_str[0] = result[0];
							new_str[1] = '1';
							strcpy(new_str + 2, result + 1);
							new_str[result_len - floatdigit + Accuracy(form)] = '\0';
						}

						result_len -= floatdigit - Accuracy(form);
						delete []result;
						result = new char[result_len + 1];
						strcpy(result, new_str);
						delete []new_str;
					}
				}	
			}	
		}	
	}
	else if(Type(form) == 'd')
	{
		if(result_len == 1 && result[0] == '0')
		{
			if(IntAccuracy(form) == 0)
			{
				result_len = 0;
				result = new char;
				*result = '\0';
			}
			else if(IntAccuracy(form) > 0)
			{
				result_len = IntAccuracy(form);
				result = new char[result_len + 1];
				for(int i = 0; i < result_len; i++)
					result[i] = '0';
				result[result_len] = '\0';
			}
		}
		else if(result[0] >= '0' && result[0] <= '9' && IntAccuracy(form) > result_len)
		{
			new_str = new char[IntAccuracy(form) + 1];
			for(int i = 0; i < IntAccuracy(form) - result_len; i++)
				new_str[i] = '0';
			strcpy(new_str + IntAccuracy(form) - result_len, result);
			
			result_len = IntAccuracy(form);
			delete []result;
			result = new char[result_len + 1];
			strcpy(result, new_str);
			delete []new_str;
		}
		else if(result[0] == '-' && IntAccuracy(form) > result_len - 1)
		{
			new_str = new char[IntAccuracy(form) + 2];
			new_str[0] = '-';
			for(int i = 1; i <= IntAccuracy(form) - result_len + 1; i++)
				new_str[i] = '0';
			strcpy(new_str + IntAccuracy(form) - result_len + 2, result + 1);
			
			result_len = IntAccuracy(form) + 1;
			delete []result;
			result = new char[result_len + 1];
			strcpy(result, new_str);
			delete []new_str;
		}
	}
	
	if(Plus(form))
	{
		if(str[0] != '-')
		{
			char *new_str = new char[result_len + 2];
			new_str[0] = '+';
			strcpy(new_str + 1, result);
			
			result_len++;
			delete []result;
			result = new char[result_len + 1];
			strcpy(result, new_str);
			delete []new_str;
		}
	}
	else if(Space(form))
	{
		if(str[0] != '-')
		{
			char *new_str = new char[result_len + 2];
			new_str[0] = ' ';
			strcpy(new_str + 1, result);
			
			result_len++;
			delete []result;
			result = new char[result_len + 1];
			strcpy(result, new_str);
			delete []new_str;
		}
	}
	
	if(result_len < Width(form))
	{
		int space_num = Width(form) - result_len;
		if(Minus(form))
		{
			char *new_str = new char[result_len + space_num + 1];
			strcpy(new_str, result);
			for(int i = result_len; i < result_len + space_num; i++)
				new_str[i] = ' ';
			new_str[result_len + space_num] = '\0';
			
			result_len += space_num;
			delete []result;
			result = new char[result_len + 1];
			strcpy(result, new_str);
			delete []new_str;
		}
		else
		{
			char *new_str = new char[result_len + space_num + 1];
			for(int i = 0; i < space_num; i++)
				new_str[i] = ' ';
			strcpy(new_str + space_num, result);
			
			result_len += space_num;
			delete []result;
			result = new char[result_len + 1];
			strcpy(result, new_str);
			delete []new_str;
		}
	}
	
	return Mystring(result);
}

/*
-999.99
-1000.0
*/
