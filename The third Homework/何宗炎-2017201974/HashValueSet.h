#ifndef HashValueSet_Hzy_H_
#define HashValueSet_Hzy_H_
#include "Hzydef.h"
#include <bits/stdc++.h>
class HashValueSet {
private:
    LL Value1, Value2 ;
    
public:
    HashValueSet(LL v1, LL v2) : Value1(v1), Value2(v2) {}
    ~HashValueSet() {}
    
    bool operator < (const HashValueSet p) const {
	if(Value1 == p.Value1) return Value2 < p.Value2;
	else return Value1 < p.Value1;
    }
};

#else
#endif
