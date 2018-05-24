#include"mystring.h"
#include"mygoodstring.h"













MyGoodString::MyGoodString(const char * s){
	len_plus = 0;
	len = strlen(s);
	if(s[0] == '-'){
		positive = false;
		negative = true;
		len_plus = 1;
		len--;
	}
	else{
		positive = true;
		negative = false;
	}
	len_tot = len_plus + len;
	
	str = new char [len + 1];
	strcpy(str , s);
}


MyGoodString::MyGoodString(){
	len_plus = 0;
	len = 0;
	str = 0;
	len_tot = 0;
}


MyGoodString::MyGoodString(const MyGoodString & st){
	len = strlen(st.str);
	len_plus = 0;
	if(st[0] == '-'){
		positive = false;
		negative = true;
		len_plus = 1;
		len--;
	}
	else{
		positive = true;
		negative = false;
	}
	len_tot = len + len_plus;

	str = new char [len + 1];
	strcpy(str , st.str);
}


void MyGoodString::print(MyGoodString & standard){
	char output_mid[1025] = {0};
	char output_front[1025] = {0};
	char output_behind[1025] = {0};
	int point_pos = standard.find('.' , 0 , standard.len_tot - 1);
	int int_pos = standard.find('d' , 0 , standard.len_tot - 1);
	int double_pos = standard.find('l' , 0 , standard.len_tot - 1);
	int plus_pos = standard.find('+' , 0 , standard.len_tot - 1);
	int substract_pos = standard.find('-' , 0 , standard.len_tot - 1);

	int zero_pos;
	if(point_pos != -1){
		zero_pos = standard.find('0' , 0 , point_pos);
		
	}
	else{
		zero_pos = standard.find('0' , 0 , standard.len_tot - 1);
		
	}
	if(standard[zero_pos - 1] >= 48 && standard[zero_pos - 1] <= 57){
			zero_pos = -1;
	}

	if(negative){
		output_mid[0] = '-';

		str ++;
	}
	if(plus_pos != -1){
		if(positive){
			output_mid[0] = '+';

			len_plus = 1;
		}
	}
	
	if(substract_pos != -1){
		right = false;
	}
	else{
		right = true;
	}
	
	if(zero_pos != -1){
		space = false;
	}
	else{
		space = true;
	}

	if(int_pos != -1){
		char mid_num_wid[1025] = {0};
		if(point_pos != -1){
			char mid_num_pre[1025] = {0};

			strncpy(mid_num_pre , standard.str + point_pos + 1  , int_pos - point_pos - 1);
			mid_num_pre[int_pos - point_pos - 1] = '\0';

			int precision_int = atoi(mid_num_pre);
			//抽出精度
			if(precision_int > len  ){
				if(strlen(output_mid) == 1){
					for(int j = 1 ; j <= precision_int - len ; j++ ){
						output_mid[j] = '0';
					}
				}
				else{
					for(int j = 0 ; j <= precision_int - len - 1 ; j++ ){
						output_mid[j] = '0';
					}
				}
				len = precision_int;
				len_tot = len + len_plus;
			}
			//抽出宽度
			

				int time0 = 0;
				for(int i = 1 , j = 0; i <= point_pos ; i++){
					if(standard[i] >= 48 && standard[i] <=57){
						if(standard[i] == '0' && time0 == 0 && zero_pos != -1){
							time0++;
							continue;
						}
						mid_num_wid[j] = standard[i];
						j++;
					}
				}

			
			//根据宽度和精度进行操作
			
			}
			else{
				int time0 = 0;
				for(int i = 1 , j = 0 ; i <= int_pos ; i++){
					if(standard[i] >= 48 && standard[i] <=57){
						if(standard[i] == '0' && time0 == 0 && zero_pos != -1){
							time0++;
							continue;
						}
						mid_num_wid[j] = standard[i];
						j++;

					}
				}
			}
			if(mid_num_wid[0] != '\0'){

				int width_int = atoi(mid_num_wid);

				if(len + strlen(output_mid) < width_int){
					if(right == true){
						if(space == true){
							for(int k = 0 ; k <= width_int - len -len_plus - 1 ; k++){
								output_front[k] = ' ';
							}
						}
						else{
							for(int k = strlen(output_mid) ; k <= width_int - len -len_plus - 1 ; k++){
								output_mid[k] = '0';
							}
						}
					}
					else{

							for(int k = 0 ; k <= width_int - len -len_plus - 1 ; k++){
								output_behind[k] = ' ';
							}

						}
					}
				}
		}
		
		
	
	
	else if(double_pos != -1){
		char pre_num[1025] = {0};
		char wid_num[1025] = {0};
		int precision_double;
		int width_double;
		int pre_pos = this -> find('.' , 0 , len - 1);
		int len_decimal ;
		

		if(pre_pos == -1){
			len_decimal = 0;
		}
		else{
			len_decimal = len - pre_pos - 1;
		}
		
		if(point_pos != -1){
			strncpy(pre_num , standard.str + point_pos + 1  , double_pos - point_pos - 1);

			precision_double = atoi(pre_num);
			if(len_decimal == 0){
				if(precision_double > len_decimal){
					output_behind[0] = '.';
					for(int i = 1 ; i <= precision_double - len_decimal ; i++){
						output_behind[i] = '0';
					}
				}
			}
			else {
				if(precision_double > len_decimal){
					for(int i = 0 ; i <= precision_double - len_decimal - 1 ; i++){
						output_behind[i] = '0';
					}
				}
				else if(precision_double < len_decimal){
					str[pre_pos + precision_double + 1] = '\0';
					if(precision_double == 0){
						str[pre_pos] = '\0';
					}
				}
				
			}
			len_tot += strlen(output_behind);
			int time0 = 0;
			for(int i = 1 , j = 0 ; i <= point_pos ; i++){
				if(standard[i] >= 48 && standard[i] <= 57){
					if(standard [i] == '0' && time0 == 0 && zero_pos != -1){
						time0++;
						continue;
					}
					wid_num[j] = standard[i];
					j++;
				}
			}
		}
		else{
			int time0 = 0;
			for(int i = 1 , j = 0 ; i <= double_pos ; i++){
				if(standard[i] >= 48 && standard[i] <= 57){
					if(standard[i] == '0' && time0 == 0 && zero_pos != -1){
						time0 ++;
						continue;
					}
					wid_num[j] = standard[i];
					j++;
				}
			}
		}
		
		if(wid_num[0] != '\0'){
			width_double = atoi(wid_num);
			                                                                                              
			if(len_tot < width_double){
				if(right == true){
					if(space == true){
						for(int k = 0 ; k <= width_double - len_tot - 1 ; k++){
								output_front[k] = ' ';
						}
					}
					else{
						for(int k = strlen(output_mid) ; k <= width_double - len_tot - 1 ; k++){
							output_mid[k] = '0';
						}
					}
				}
				else{
						for(int k = strlen(output_behind) ; k <= width_double - len - 1 ; k++){
								output_behind[k] = ' ';
						}
					}
				}
			}
		}
	
	cout << output_front << output_mid << str << output_behind << endl;
}


int MyGoodString::find(char flag , int beg_pos  , int end_pos ){
	int count = 0;
	if(beg_pos < 0 || end_pos < 0)
		return -1;
	for(int i = beg_pos ; i <= end_pos ; i++){
		if(str[i] == flag){
			count++;
			return i;
		}
	}
	if(count == 0)
		return -1;
}
