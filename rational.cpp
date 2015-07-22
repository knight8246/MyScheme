#include "rational.h"
#include "float.h"
#include "complex.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<iostream>
using namespace std;

Rational::Rational(string numerator, string denominator) : numerator_(numerator),
	denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}

Rational::~Rational(){

}

void Rational::reduce(){
	assert(denominator_ && "denominator is zero");
	if(denominator_.number_=="1") return;
	if(!numerator_){
		denominator_ = (LongInt)"1";
		return;
	}
	
	string a, b;
	if(numerator_.number_[0]=='-'){
		a=numerator_.number_.substr(1, numerator_.number_.size());
	}
	else a=numerator_.number_;
	if(denominator_.number_[0]=='-'){
		b=denominator_.number_.substr(1, denominator_.number_.size());
	}
	else b=denominator_.number_;
	
	LongInt big, small, tmp;
	big = max(a, b);
	small = min(a, b);
	while(tmp = big % small){
		big = small;
		small = tmp;
	}
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if(denominator_ < LongInt("0")){
		numerator_ = LongInt("0")-numerator_;
		denominator_ = LongInt("0")-denominator_;
	}
}


Number *Rational::convert(Number *number2){
	assert(number2->type_ <= type_);
	Rational *result = new Rational();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->numerator_ = tmp->numerator_;
			result->denominator_ = tmp->denominator_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	result->reduce();
	return result;
}

Number *Rational::add( Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::sub(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::mul(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::div(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->denominator_;
	result->denominator_ = denominator_ * tmp->numerator_;
	result->reduce();
	return result;
}

Number *Rational::real_part(){
	return this;
}

Number *Rational::imag_part(){
	Rational *result=new Rational("0","1");
	return result;
}

Number *Rational::numerator(){
	LongInt result;
	result = numerator_;
	return new Rational(result.number_,"1");
}

Number *Rational::denominator(){
	LongInt result;
	result = denominator_;
	return new Rational(result.number_,"1");
}

Number *Rational::max_num(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	Rational *result1 = new Rational();
	Rational *result2 = new Rational();
	result1->numerator_ = numerator_ * tmp->denominator_;
	result1->denominator_ = denominator_ * tmp->denominator_;
	result2->numerator_ = denominator_ * tmp->numerator_;
	result2->denominator_ = denominator_ * tmp->denominator_;
	result->denominator_ = result1->denominator_;
	result->numerator_ = max(result1->numerator_,result2->numerator_);
	result->reduce();
	return result;
}

Number *Rational::min_num(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	Rational *result1 = new Rational();
	Rational *result2 = new Rational();
	result1->numerator_ = numerator_ * tmp->denominator_;
	result1->denominator_ = denominator_ * tmp->denominator_;
	result2->numerator_ = denominator_ * tmp->numerator_;
	result2->denominator_ = denominator_ * tmp->denominator_;
	result->denominator_ = result1->denominator_;
	result->numerator_ = min(result1->numerator_,result2->numerator_);
	result->reduce();
	return result;
}

Number *Rational::floor(){
	LongInt result;
	if(denominator_.number_=="1"){
		result=numerator_;
		return new Rational(result.number_,"1");
	}
	if(numerator_.number_[0]!='-'){
		result=numerator_/denominator_;
		return new Rational(result.number_,"1");
	}
	result=numerator_/denominator_+(LongInt)"-1";
	return new Rational(result.number_,"1");
}

Number *Rational::ceiling(){
	LongInt result;
	if(denominator_.number_=="1"){
		result=numerator_;
		return new Rational(result.number_,"1");
	}
	if(numerator_.number_[0]!='-'){
		result=numerator_/denominator_+(LongInt)"1";
		return new Rational(result.number_,"1");
	}
	result=numerator_/denominator_;
	return new Rational(result.number_,"1");
}

Number *Rational::truncate(){
	LongInt result;
	if(denominator_.number_=="1"){
		result=numerator_;
		return new Rational(result.number_,"1");
	}
	result=numerator_/denominator_;
	return new Rational(result.number_,"1");
}

Number *Rational::round(){
	LongInt result;
	if(denominator_.number_=="1"){
		result=numerator_;
		return new Rational(result.number_,"1");
	}
	if(denominator_.number_=="2"){
		result=(numerator_+(LongInt)"1")/denominator_;
		return new Rational(result.number_,"1");
	}
	result=numerator_/denominator_;
	return new Rational(result.number_,"1");
}

Number *Rational::abs(){
	LongInt result;
	if(numerator_.number_[0]!='-') result=numerator_;
	else result=numerator_*(LongInt)"-1";
	return new Rational(result.number_,denominator_.number_);
}

Number *Rational::quotient(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(tmp->numerator_.number_=="0") throw 0;
	if(denominator_.number_!="1" || tmp->denominator_.number_!="1") throw 0;
	LongInt result;
	result=numerator_/tmp->numerator_;
	return new Rational(result.number_,"1");
}

Number *Rational::remainder(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(tmp->numerator_.number_=="0") throw 0;
	if(denominator_.number_!="1" || tmp->denominator_.number_!="1") throw 0;
	LongInt result;
	result=numerator_%tmp->numerator_;
	return new Rational(result.number_,"1");
}

Number *Rational::modulo(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(tmp->numerator_.number_=="0") throw 0;
	if(denominator_.number_!="1" || tmp->denominator_.number_!="1") throw 0;
	LongInt result;
	result=numerator_%tmp->numerator_;
	if(result.number_=="0") return new Rational("0","1");
	if((tmp->numerator_.number_[0]=='-' && result.number_[0]=='-') || (tmp->numerator_.number_[0]!='-' && result.number_[0]!='-'))
		return new Rational(result.number_,"1");
	result = result+tmp->numerator_;
	return new Rational(result.number_,"1");
}

Number *Rational::gcd(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(tmp->numerator_.number_=="0" || numerator_.number_=="0") return new Rational("0","1");
	if(denominator_.number_!="1" || tmp->denominator_.number_!="1") throw 0;
	LongInt result, tmp1, tmp2;
	result=numerator_;
	tmp1=tmp->numerator_;
	while(tmp1.number_!="0"){
		tmp2=result%tmp1;
		result=tmp1;
		tmp1=tmp2;
	}
	if(result.number_[0]=='-') result=(LongInt)"-1"*result;
	return new Rational(result.number_,"1");
}

Number *Rational::lcm(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(tmp->numerator_.number_=="0" || numerator_.number_=="0") return new Rational("0","1");
	if(denominator_.number_!="1" || tmp->denominator_.number_!="1") throw 0;
	LongInt result;
	result=SCAST_RATIONAL(this->gcd(tmp))->numerator_;
	result=numerator_*tmp->numerator_/result;
	if(result.number_[0]=='-') result=(LongInt)"-1"*result;
	return new Rational(result.number_,"1");
}

Number *Rational::expt(Number *number2){
	if(numerator_.number_[0]=='-'){
		Rational *tmp = SCAST_RATIONAL(number2);
		Rational *tmp1 = new Rational("0","1");
		Rational *tmp2 = new Rational("0","1");
		Complex *tmp3 = new Complex(this,tmp1);
		Complex *tmp4 = new Complex(tmp,tmp2);
		Number *result = new Complex();
		result=tmp3->expt(tmp4);
		return result;
	}
	else {
		Rational *tmp = SCAST_RATIONAL(number2);
		Float *tmp1 = new Float();
		Float *tmp2 = new Float();
		Number *result = new Float();
		tmp1->number_=(double)numerator_/(double)denominator_;
		tmp2->number_=(double)tmp->numerator_/(double)tmp->denominator_;
		result=tmp1->expt(tmp2);
		return result;
	}
}

Number *Rational::sqrt(){
	if(numerator_.number_[0]=='-'){
		Rational *tmp2 = new Rational("0","1");
		Complex *tmp = new Complex(this, tmp2);
		Number *result = new Complex();
		result=tmp->sqrt();
		return result;
	}
	else {
		Float *tmp = new Float();
		Number *result = new Float();
		tmp->number_=(double)numerator_/(double)denominator_;
		result=tmp->sqrt();
		return result;
	}
}

Number *Rational::inexact(){
	Float *tmp = new Float();
	Number *result = new Float();
	tmp->number_=(double)numerator_/(double)denominator_;
	result=tmp;
	return result;
}

Number *Rational::exact(){
	return this;
}

void Rational::print(){
	numerator_.print();
	if(denominator_ != (LongInt)"1"){
		printf("/");
		denominator_.print();
	}
	printf("\n");
}

Rational *Rational::from_string(char *expression){
	char* end_pointerr;
    char *separate_pos = strchr(expression, '/');
    char *non_zero;
	string numerator="", denominator="";
	bool judge=0;
	if(expression=="0" || expression=="-0") return new Rational("0","1");
	if(expression[0]=='-'){		
		numerator+='-';
		if(separate_pos){
			for(char *i=expression+1; i<separate_pos; ++i){
				if(*i!='0'){
					judge=1;
					non_zero=i;
					break;
				}
			}
			if(!judge){
				return new Rational("0","1");
			}
	    	for(char *i=non_zero; i<=separate_pos; ++i){
	    		if(*i>='0' && *i<='9') numerator+=*i;
	    		else {
	    			end_pointerr=i;
	    			break;
				}
			}
			if(end_pointerr==expression+1 || end_pointerr!= separate_pos) return NULL;
			
			end_pointerr=expression+strlen(expression);
			judge=0;
			for(char *i=separate_pos+1; i<expression+strlen(expression); ++i){
				if(*i!='0'){
					non_zero=i;
					break;
				}
			}
			for(char *i=non_zero; i<expression+strlen(expression); ++i){
				if(*i>='0' && *i<='9') denominator+=*i;
				else{
					end_pointerr=i;
					break;
				}
			}
			if(end_pointerr==separate_pos+1 || end_pointerr!=expression+strlen(expression)) return NULL;
			return new Rational(numerator,denominator);
		}
		else{
			for(char *i=expression+1; i<expression+strlen(expression); ++i){
				if(*i!='0'){
					judge=1;
					non_zero=i;
					break;
				}
			}
			if(!judge){
				return new Rational("0","1");
			}
			end_pointerr=expression+strlen(expression);
			for(char *i=non_zero; i<expression+strlen(expression); ++i){
				if(*i>='0' && *i<='9') numerator+=*i;
				else{
					end_pointerr=i;
					break;
				}
			}
			if(end_pointerr==expression+1 || end_pointerr!=expression+strlen(expression)) return NULL;
			return new Rational(numerator, "1");
		}
	}
    if(separate_pos){
    	for(char *i=expression; i<separate_pos; ++i){
			if(*i!='0'){
				judge=1;
				non_zero=i;
				break;
			}
		}
		if(!judge){
			return new Rational("0","1");
		}
    	for(char *i=non_zero; i<=separate_pos; ++i){
    		if(*i>='0' && *i<='9') numerator+=*i;
    		else {
    			end_pointerr=i;
    			break;
			}
		}
		if(end_pointerr==expression || end_pointerr!= separate_pos) return NULL;
		
		end_pointerr=expression+strlen(expression);
		for(char *i=separate_pos+1; i<expression+strlen(expression); ++i){
			if(*i!='0'){
				non_zero=i;
				break;
			}
		}
		for(char *i=non_zero; i<expression+strlen(expression); ++i){
			if(*i>='0' && *i<='9') denominator+=*i;
			else{
				end_pointerr=i;
				break;
			}
		}
		if(end_pointerr==separate_pos+1 || end_pointerr!=expression+strlen(expression)) return NULL;
		return new Rational(numerator,denominator);
	}
	else{
		for(char *i=expression; i<expression+strlen(expression); ++i){
			if(*i!='0'){
				judge=1;
				non_zero=i;
				break;
			}
		}
		if(!judge){
			return new Rational("0","1");
		}
		end_pointerr=expression+strlen(expression);
		for(char *i=non_zero; i<expression+strlen(expression); ++i){
			if(*i>='0' && *i<='9') numerator+=*i;
			else{
				end_pointerr=i;
				break;
			}
		}
		if(end_pointerr==expression || end_pointerr!=expression+strlen(expression)) return NULL;
		return new Rational(numerator, "1");
	}
	
}

// int main(){
// 	Rational *a = new Rational("-18","18");
// 	// Rational *b = new Rational(4,5);
// 	cout<<a->numerator_.number_<<a->denominator_.number_<<endl;
// 	// (a->div(b))->print();
// }
