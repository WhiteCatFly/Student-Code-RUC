#include"regstr.h"

Regstr::Regstr(const String& s,const String& mode)
{
	const double eps = 1e-6;
	char ts[2048];
	
	double wid_pre = 0;
	sscanf(mode.getstr(),"%*c%lf",&wid_pre);
	if ( (wid_pre - 0) < eps ) {
		rstr_ = new char[s.getlen()+1];
		strcpy(rstr_,s.getstr());
	}
	else {
		char temp[1048];
		sprintf(temp,"%g",wid_pre);
		int int_,dec_;
		sscanf(temp,"%d.%d",&int_,&dec_);
		if (mode[mode.getlen()-1] == 'd') {
			if (s.getlen() < dec_) {
				sprintf(temp,"%%0%ds",dec_);	
				sprintf(ts,temp,s.getstr());
			}
			if (max(dec_,s.getlen()) < abs(int_)) {
				sprintf(temp,"%%%ds",int_);
				char ts1[2048];
				sprintf(ts1,temp,ts);
				strcpy(ts,ts1);
			}
		}
		
		if (mode[mode.getlen()-1] == 'f') {
			int intlen = 0 , declen = 0;
			intlen = s.find('.');
			declen = s.getlen() - intlen - 1;
			if (declen < dec_) {
				sprintf(temp,"%%0%dd",dec_-declen);
				char zeros[1048];
				sprintf(zeros,temp,0);
				strcpy(ts,s.getstr());
				strcat(ts,zeros);
			}
			if (declen > dec_) {
				strncpy(ts,s.getstr(),intlen+dec_+1);
				if (s[intlen+dec_+1] >= 5) {
					for (int i = intlen + dec_; i >= 0;i--) {
						if (ts[i] == '.') continue;
						if (ts[i] + 1 <= '9') {
							ts[i]++; 
							break;
						}
						else {
							if (i != 0)
								ts[i] = '0';
							else {
								ts[i] = '0';
								char ts1[2048] = "1";
								strcat(ts1,ts);
								strcpy(ts,ts1);
							}
						}
					 	
				} // a trouble
			}
			if (strlen(ts) < abs(int_)) {
				sprintf(temp,"%%%ds",int_);
				char ts1[2048];
				sprintf(ts1,temp,ts);
				strcpy(ts,ts1);
			}
		}
		}		
		}
	rstr_ = new char[strlen(ts)+1];
	strcpy(rstr_,ts);		
	
}
