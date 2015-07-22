#include "float.h"
#include "rational.h"
#include "complex.h"
#include "long_int.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include<iostream>
#include<iomanip>
#include<cmath>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;

#define ABS(x) ((x)<0?(-(x)):(x))

Float::Float(double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

}

Number *Float::convert(Number *number2){
	assert(number2->type_ <= type_);
	Float *result = new Float();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->number_ = (double)tmp->numerator_ / (double)tmp->denominator_;
			// printf("%lf", result->number_);
			break;
		}
		case FLOAT:{
			Float *tmp = SCAST_FLOAT(number2);
			result->number_ = tmp->number_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	return result;
}

Number *Float::add(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ + tmp->number_);
	return result;
}

Number *Float::sub(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ - tmp->number_);
	return result;
}

Number *Float::mul(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ * tmp->number_);
	return result;
}

Number *Float::div(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(ABS(tmp->number_)>1e-300 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

Number *Float::real_part(){
	return this;
}

Number *Float::imag_part(){
	Float *result = new Float(0.0);
	return result;
}

Number *Float::numerator(){
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6){
		ostringstream os;
		string a;
		os<<number_;
		a=os.str();
		Rational *tmp = new Rational(a,"1");
		result=SCAST_RATIONAL(tmp->numerator());
		return result;
	}
	else throw 0;
}

Number *Float::denominator(){
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6){
		ostringstream os;
		string a;
		os<<number_;
		a=os.str();
		Rational *tmp = new Rational(a,"1");
		result=SCAST_RATIONAL(tmp->denominator());
		return result;
	}
	else throw 0;
}

Number *Float::max_num(Number *number2){
	Float *result=new Float;
	Float *tmp = SCAST_FLOAT(number2);
	result->number_=number_>tmp->number_? number_:tmp->number_;
	return result;
}

Number *Float::min_num(Number *number2){
	Float *result=new Float;
	Float *tmp = SCAST_FLOAT(number2);
	result->number_=number_<tmp->number_? number_:tmp->number_;
	return result;
}

Number *Float::floor(){
	Float *tmp = new Float;
	Number *result;
	tmp->number_=std::floor(number_);
	result=tmp;
	return result;
}

Number *Float::ceiling(){
	Float *tmp = new Float;
	Number *result;
	tmp->number_=std::ceil(number_);
	result=tmp;
	return result;
}

Number *Float::truncate(){
	Float *tmp = new Float;
	Number *result;
	tmp->number_=trunc(number_);
	result=tmp;
	return result;
}

Number *Float::round(){
	Float *tmp = new Float;
	Number *result;
	tmp->number_=nearbyint(number_);
	result=tmp;
	return result;
}

Number *Float::abs(){
	Float *tmp = new Float;
	Number *result;
	if(number_>=0) tmp->number_=number_;
	else tmp->number_=(-1)*number_;
	result=tmp;
	return result;
}

Number *Float::quotient(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6 && nearbyint(tmp->number_)-tmp->number_<1e-6){
		ostringstream os1, os2;
		string a,b;
		os1<<number_;
		os2<<tmp->number_;
		a=os1.str();
		b=os2.str();
		Rational *tmp1 = new Rational(a,"1");
		Rational *tmp2 = new Rational(b,"1");
		result=SCAST_RATIONAL(tmp1->quotient(tmp2));
		return result;
	}
	else throw 0;
}

Number *Float::remainder(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6 && nearbyint(tmp->number_)-tmp->number_<1e-6){
		ostringstream os1, os2;
		string a,b;
		os1<<number_;
		os2<<tmp->number_;
		a=os1.str();
		b=os2.str();
		Rational *tmp1 = new Rational(a,"1");
		Rational *tmp2 = new Rational(b,"1");
		result=SCAST_RATIONAL(tmp1->remainder(tmp2));
		return result;
	}
	else throw 0;
}

Number *Float::modulo(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6 && nearbyint(tmp->number_)-tmp->number_<1e-6){
		ostringstream os1, os2;
		string a,b;
		os1<<number_;
		os2<<tmp->number_;
		a=os1.str();
		b=os2.str();
		Rational *tmp1 = new Rational(a,"1");
		Rational *tmp2 = new Rational(b,"1");
		result=SCAST_RATIONAL(tmp1->modulo(tmp2));
		return result;
	}
	else throw 0;
}

Number *Float::gcd(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6 && nearbyint(tmp->number_)-tmp->number_<1e-6){
		ostringstream os1, os2;
		string a,b;
		os1<<number_;
		os2<<tmp->number_;
		a=os1.str();
		b=os2.str();
		Rational *tmp1 = new Rational(a,"1");
		Rational *tmp2 = new Rational(b,"1");
		result=SCAST_RATIONAL(tmp1->gcd(tmp2));
		return result;
	}
	else throw 0;
}

Number *Float::lcm(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Rational *result = new Rational();
	if(nearbyint(number_)-number_<1e-6 && nearbyint(tmp->number_)-tmp->number_<1e-6){
		ostringstream os1, os2;
		string a,b;
		os1<<number_;
		os2<<tmp->number_;
		a=os1.str();
		b=os2.str();
		Rational *tmp1 = new Rational(a,"1");
		Rational *tmp2 = new Rational(b,"1");
		result=SCAST_RATIONAL(tmp1->lcm(tmp2));
		return result;
	}
	else throw 0;
}

Number *Float::expt(Number *number2){
	if(number_<0){
		Float *tmp = SCAST_FLOAT(number2);
		Float *tmp1 = new Float(0.0);
		Float *tmp2 = new Float(0.0);
		Complex *tmp3 = new Complex(this,tmp1);
		Complex *tmp4 = new Complex(tmp,tmp2);
		Number *result = new Complex();
		result=tmp3->expt(tmp4);
		return result;
	}
	else{
		Float *result=new Float;
		Float *tmp = SCAST_FLOAT(number2);
		result->number_=pow(number_,tmp->number_);
		return result;
	}
}

Number *Float::sqrt(){
	if(number_<0){
		Float *tmp1 = new Float(0.0);
		Complex *tmp = new Complex(this, tmp1);
		Number *result = new Complex();
		result=tmp->sqrt();
		return result;
	}
	else{
		Float *tmp = new Float;
		Number *result;
		tmp->number_=std::sqrt(number_);
		result=tmp;
		return result;
	}
}

Number *Float::inexact(){
	return this;
}

/*Number *Float::exact(){
	double tmp1=number_, tmp2=0;
	int tmp3;
	string tmp="", num="", den="1";
	
	ostringstream os;
	tmp2=std::floor(tmp1);
	tmp1-=tmp2;
	os<<tmp2;
	tmp=os.str();
	
	for(int i=0; i<10; ++i){
		tmp1*=10;
		tmp3=std::floor(tmp1);
		tmp1-=tmp3;
		num+=tmp3+'0';
		den+='0';
	}
	
	Rational *tmp4=new Rational(tmp,"1");
	Rational *result=new Rational(num,den);
	result=SCAST_RATIONAL(result->add(tmp4));
	result->reduce();
	
	return result;
}*/

/*Number *Float::exact(){
	double tmp1=number_, tmp2=0, tmp3=0, tmp5=1;
	string tmp="", num="", den="1";
	
	stringstream ss;
	tmp2=std::floor(tmp1);
	tmp1-=tmp2;
	ss<<tmp2;
	ss>>tmp;
	ss.clear();
	
	while(1){
		tmp3=nearbyint(tmp1);
		if(tmp1==tmp3){
			break;
		}
		tmp1*=2;
		tmp5*=2;
	}
	cout<<tmp1<<endl;
	
	ss<<tmp3;
	ss>>num;
	ss.clear();
	ss<<tmp5;
	ss>>den;
	ss.clear();
	Rational *tmp4=new Rational(tmp,"1");
	Rational *result=new Rational(num,den);
	result=SCAST_RATIONAL(result->add(tmp4));
	result->reduce();
	
	return result;
}*/

Number* Float::exact(){
    if (fabs(nearbyint(number_)-number_)<1e-300){
        stringstream ss1;
        ss1<<fixed<<setprecision(5)<<number_;
        string s1;
        ss1>>s1;
        int dot_pos_1 = s1.find(".");
        string num1_s = s1.substr(0,dot_pos_1);
        return new Rational(num1_s,"1");
    }
    double *px = &number_;
    long long int* py=reinterpret_cast<long long int*>(px);
    long long int y=*py;
    long long int p=1;
    bool v[100]={0};
    for (int i=1;i<=64;++i) { v[i] = y&p; y>>=1; }
    int tmp=0;
    for (int i=63;i>=53;--i) { tmp<<=1; tmp+=v[i]; }
    tmp-=1022;
    for (int i=1;i<=11;++i) { v[52+i] = tmp&p; tmp>>=1; }
    long long int i_num=0;
    for (int i=63;i>=1;--i) { i_num<<=1; i_num+=v[i]; }
    string s_num="";
    while (i_num!=0)
    {
        s_num+=(char)(i_num%10+'0');
        i_num/=10;
    }
    std::reverse(s_num.begin(),s_num.end());
    return new Rational(s_num,"4503599627370496");
}

void Float::print(){
	if(number_<1e6 && number_>1e-6)
		cout<<fixed<<setprecision(30)<<number_<<endl;
	else cout<<setprecision(30)<<number_<<endl;
}

Float *Float::from_string(char *expression){
    char *end_pointer;
    double val = strtod(expression, &end_pointer);
    if (end_pointer == expression || end_pointer != expression + strlen(expression))
	    return NULL;
    return new Float(val);
}


// int main(){
// 	Float *a = new Float(1.2);
// 	Float *b = new Float(1.3);
// 	(a->add(b))->print();
// }
