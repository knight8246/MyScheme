#include "complex.h"
#include "float.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <complex>
using namespace std;


Complex::Complex(Number *real, Number *imag):real_(real),
	imag_(imag){
	type_=COMPLEX;
	reduce();
}

Complex::~Complex(){
	
}

void Complex::reduce(){	// ?
	if(imag_->type_==RATIONAL){
		Rational *tmp=SCAST_RATIONAL(imag_);
		tmp->reduce();
	}
	if(real_->type_==RATIONAL){
		Rational *tmp=SCAST_RATIONAL(real_);
		tmp->reduce();
	}
}

Number *Complex::convert(Number *number2){
	assert(number2->type_<=type_);
	Complex *result = new Complex();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->real_ = SCAST_NUMBER(tmp);
			result->imag_ = SCAST_NUMBER(new Rational("0","1"));
			break;
		}
		case FLOAT:{
			Float *tmp = SCAST_FLOAT(number2);
			result->real_ = SCAST_NUMBER(tmp);
			result->imag_ = SCAST_NUMBER(new Float(0.0));
			break;
		}
		case COMPLEX:{
			Complex *tmp = SCAST_COMPLEX(number2);
			result->real_ = tmp->real_;
			result->imag_ = tmp->imag_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	result->reduce();
	return result;
}

Number *Complex::add(Number *number2){
	Complex *result = new Complex();
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *res = new Rational("0","1");
	Number *conv;
	if(res->type_>real_->type_){
		res = res->add(conv=res->convert(real_));
	}
	else{
		res=(conv = real_->convert(res))->add(real_);
	}
	if(res->type_>tmp->real_->type_){
		res = res->add(conv=res->convert(tmp->real_));
	}
	else{
		res=(conv = tmp->real_->convert(res))->add(tmp->real_);
	}
	result->real_=res;
	res=new Rational("0","1");
	if(res->type_>imag_->type_){
		res = res->add(conv=res->convert(imag_));
	}
	else{
		res=(conv = imag_->convert(res))->add(imag_);
	}
	if(res->type_>tmp->imag_->type_){
		res = res->add(conv=res->convert(tmp->imag_));
	}
	else{
		res=(conv = tmp->imag_->convert(res))->add(tmp->imag_);
	}
	result->imag_=res;
	
	return result;
}

Number *Complex::sub(Number *number2){
	Complex *result = new Complex();
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *res = new Rational("0","1");
	Number *conv;
	if(res->type_>real_->type_){
		res = res->add(conv=res->convert(real_));
	}
	else{
		res=(conv = real_->convert(res))->add(real_);
	}
	if(res->type_>tmp->real_->type_){
		res = res->sub(conv=res->convert(tmp->real_));
	}
	else{
		res=(conv = tmp->real_->convert(res))->sub(tmp->real_);
	}
	result->real_=res;
	res=new Rational("0","1");
	if(res->type_>imag_->type_){
		res = res->add(conv=res->convert(imag_));
	}
	else{
		res=(conv = imag_->convert(res))->add(imag_);
	}
	if(res->type_>tmp->imag_->type_){
		res = res->sub(conv=res->convert(tmp->imag_));
	}
	else{
		res=(conv = tmp->imag_->convert(res))->sub(tmp->imag_);
	}
	result->imag_=res;
	
	return result;
}

Number *Complex::mul(Number *number2){
	Complex *result = new Complex();
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *res = new Rational("0","1");
	Number *resu=new Rational("0","1");
	Number *conv;
	
	if(res->type_>real_->type_){
		res = res->add(conv=res->convert(real_));
	}
	else{
		res=(conv = real_->convert(res))->add(real_);
	}
	if(resu->type_>imag_->type_){
		resu = resu->add(conv=resu->convert(imag_));
	}
	else{
		resu=(conv = imag_->convert(resu))->add(imag_);
	}
	
	if(res->type_>tmp->real_->type_){
		res = res->mul(conv=res->convert(tmp->real_));
	}
	else{
		res=(conv = tmp->real_->convert(res))->mul(tmp->real_);
	}
	if(resu->type_>tmp->imag_->type_){
		resu = resu->mul(conv=resu->convert(tmp->imag_));
	}
	else{
		resu=(conv = tmp->imag_->convert(resu))->mul(tmp->imag_);
	}
	
	if(res->type_>resu->type_){
		res = res->sub(conv=res->convert(resu));
	}
	else{
		res=(conv = resu->convert(res))->sub(resu);
	}
	result->real_=res;
	
	res=new Rational("0","1");
	resu=new Rational("0","1");
	if(res->type_>real_->type_){
		res = res->add(conv=res->convert(real_));
	}
	else{
		res=(conv = real_->convert(res))->add(real_);
	}
	if(resu->type_>imag_->type_){
		resu = resu->add(conv=resu->convert(imag_));
	}
	else{
		resu=(conv = imag_->convert(resu))->add(imag_);
	}
	
	if(res->type_>tmp->imag_->type_){
		res = res->mul(conv=res->convert(tmp->imag_));
	}
	else{
		res=(conv = tmp->imag_->convert(res))->mul(tmp->imag_);
	}
	if(resu->type_>tmp->real_->type_){
		resu = resu->mul(conv=resu->convert(tmp->real_));
	}
	else{
		resu=(conv = tmp->real_->convert(resu))->mul(tmp->real_);
	}
	
	if(res->type_>resu->type_){
		res = res->add(conv=res->convert(resu));
	}
	else{
		res=(conv = resu->convert(res))->add(resu);
	}
	result->imag_=res;
	
	return result;
}

Number *Complex::div(Number *number2){
	Complex *result = new Complex();
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *conj = new Complex(tmp->real_);
	Number *res = new Rational("0","1");
	Number *conv;
	if(tmp->imag_->type_==FLOAT){
		Float *yy=new Float(-1);
		conj->imag_=tmp->imag_->mul(yy);
	}
	else{
		Rational *xx=new Rational("-1","1");
		conj->imag_=xx->mul(tmp->imag_);
	}
	
	result=SCAST_COMPLEX(this->mul(conj));
	conj=SCAST_COMPLEX(tmp->mul(conj));
	
	if(res->type_>result->real_->type_){
		res = res->add(conv=res->convert(result->real_));
	}
	else{
		res=(conv = result->real_->convert(res))->add(result->real_);
	}
	if(res->type_>conj->real_->type_){
		res = res->div(conv=res->convert(conj->real_));
	}
	else{
		res=(conv = conj->real_->convert(res))->div(conj->real_);
	}
	result->real_=res;
	res=new Rational("0","1");
	if(res->type_>result->imag_->type_){
		res = res->add(conv=res->convert(result->imag_));
	}
	else{
		res=(conv = result->imag_->convert(res))->add(result->imag_);
	}
	if(res->type_>conj->real_->type_){
		res = res->div(conv=res->convert(conj->real_));
	}
	else{
		res=(conv = conj->real_->convert(res))->div(conj->real_);
	}
	result->imag_=res;
	
	return result;
}

Number *Complex::real_part(){
	return real_;
}

Number *Complex::imag_part(){
	return imag_;
}

Number *Complex::numerator(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->numerator();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->numerator();
	}
	
	return result;
}

Number *Complex::denominator(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->denominator();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->denominator();
	}
	
	return result;
}

Number *Complex::floor(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->floor();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->floor();
	}
	
	return result;
}

Number *Complex::ceiling(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->ceiling();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->ceiling();
	}
	
	return result;
}

Number *Complex::max_num(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->max_num(tmp->real_);
	return result;
}

Number *Complex::min_num(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->min_num(tmp->real_);
	return result;
}

Number *Complex::truncate(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->truncate();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->truncate();
	}
	
	return result;
}

Number *Complex::round(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->round();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->round();
	}
	
	return result;
}

Number *Complex::abs(){
	Number *result;
	if(imag_->type_!=RATIONAL) throw 0;
	Rational *tmp=SCAST_RATIONAL(imag_);
	if(tmp->numerator_.number_!="0") throw 0;
	if(real_->type_==RATIONAL){
		result = new Rational;
		result=real_->abs();
	}
	if(real_->type_==FLOAT){
		result = new Float;
		result=real_->abs();
	}
	
	return result;
}

Number *Complex::quotient(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->quotient(tmp->real_);
	return result;
}

Number *Complex::remainder(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->remainder(tmp->real_);
	return result;
}

Number *Complex::modulo(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->modulo(tmp->real_);
	return result;
}

Number *Complex::gcd(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->gcd(tmp->real_);
	return result;
}

Number *Complex::lcm(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *result = new Rational;
	if(tmp->imag_->type_!=RATIONAL || imag_->type_!=RATIONAL) throw 0;
	Rational *tmp1=SCAST_RATIONAL(tmp->imag_);
	Rational *tmp2=SCAST_RATIONAL(imag_);
	if(tmp1->numerator_.number_!="0" || tmp2->numerator_.number_!="0") throw 0;
	result=real_->lcm(tmp->real_);
	return result;
}

Number *Complex::expt(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Float *result1=new Float();
	Float *result2=new Float();
	double x, y, p, q;
	if(real_->type_==RATIONAL) x=(double)SCAST_RATIONAL(real_)->numerator_/(double)SCAST_RATIONAL(real_)->denominator_;
	if(real_->type_==FLOAT) x=SCAST_FLOAT(real_)->number_;
	if(imag_->type_==RATIONAL) y=(double)SCAST_RATIONAL(imag_)->numerator_/(double)SCAST_RATIONAL(imag_)->denominator_;
	if(imag_->type_==FLOAT) x=SCAST_FLOAT(imag_)->number_;
	if(tmp->real_->type_==RATIONAL) p=(double)SCAST_RATIONAL(tmp->real_)->numerator_/(double)SCAST_RATIONAL(tmp->real_)->denominator_;
	if(tmp->real_->type_==FLOAT) p=SCAST_FLOAT(tmp->real_)->number_;
	if(tmp->imag_->type_==RATIONAL) q=(double)SCAST_RATIONAL(tmp->imag_)->numerator_/(double)SCAST_RATIONAL(tmp->imag_)->denominator_;
	if(tmp->imag_->type_==FLOAT) q=SCAST_FLOAT(tmp->imag_)->number_;
	complex<double> tmp1(x,y),tmp2(p,q),tmp3;
	tmp3=std::pow(tmp1,tmp2);
	result1->number_=std::real(tmp3);
	result2->number_=std::imag(tmp3);
	return new Complex(result1, result2);
}

Number *Complex::sqrt(){
	Float *result1=new Float();
	Float *result2=new Float();
	double x, y;
	if(real_->type_==RATIONAL) x=(double)SCAST_RATIONAL(real_)->numerator_/(double)SCAST_RATIONAL(real_)->denominator_;
	if(real_->type_==FLOAT) x=SCAST_FLOAT(real_)->number_;
	if(imag_->type_==RATIONAL) y=(double)SCAST_RATIONAL(imag_)->numerator_/(double)SCAST_RATIONAL(imag_)->denominator_;
	if(imag_->type_==FLOAT) x=SCAST_FLOAT(imag_)->number_;
	complex<double> tmp1(x,y),tmp2;
	tmp2=std::sqrt(tmp1);
	result1->number_=std::real(tmp2);
	result2->number_=std::imag(tmp2);
	return new Complex(result1, result2);
}

Number *Complex::inexact(){
	Float *result1=new Float();
	Float *result2=new Float();
	double x, y;
	if(real_->type_==RATIONAL) x=(double)SCAST_RATIONAL(real_)->numerator_/(double)SCAST_RATIONAL(real_)->denominator_;
	if(real_->type_==FLOAT) x=SCAST_FLOAT(real_)->number_;
	if(imag_->type_==RATIONAL) y=(double)SCAST_RATIONAL(imag_)->numerator_/(double)SCAST_RATIONAL(imag_)->denominator_;
	if(imag_->type_==FLOAT) y=SCAST_FLOAT(imag_)->number_;
	result1->number_=x;
	result2->number_=y;
	return new Complex(result1, result2);
}

Number *Complex::exact(){
	Rational *result1=new Rational();
	Rational *result2=new Rational();
	if(real_->type_==RATIONAL) result1=SCAST_RATIONAL(real_);
	if(real_->type_==FLOAT) result1=SCAST_RATIONAL(SCAST_FLOAT(real_)->exact());
	if(imag_->type_==RATIONAL) result2=SCAST_RATIONAL(imag_);
	if(imag_->type_==FLOAT) result2=SCAST_RATIONAL(SCAST_FLOAT(imag_)->exact());
	return new Complex(result1, result2);
}

Complex *Complex::from_string(char *expression){
	int ex_len = strlen(expression), separate_pos;
	Number *res, *resu;
	char *sub_ex;
	bool flag_p=0, flag_m=0, imag_1=0, real_t=0, imag_t=0;
	Float *tmp;
	for(int i=0; i<ex_len; ++i){
		if(expression[i]=='i'){
			if(i!=ex_len-1) return NULL;
			if(expression[i-1]=='+' || expression[i-1]=='-') imag_1=1;
		}
	}
	for(int i=0; i<ex_len; ++i){
		if(expression[i]=='+' && expression[i-1]!='e'){
			flag_p=1;
			separate_pos = i;
		}
	}
	if(!flag_p){
		for(int i=1; i<ex_len; ++i){
			if(expression[i]=='-' && expression[i-1]!='e'){
				flag_m=1;
				separate_pos = i;
			}
		}
	}
	if(!flag_p && !flag_m) return NULL;
	
	if(flag_p){
		sub_ex = new char [separate_pos+2];
		sub_ex = strncpy(sub_ex, expression, separate_pos);
		sub_ex[separate_pos]='\0';
		res=Rational::from_string(sub_ex);
		if(!res){
			res=Float::from_string(sub_ex);
			real_t=1;
		}
		if(res==NULL) return NULL;
		delete [] sub_ex;
		sub_ex = new char [ex_len-separate_pos];
		sub_ex = strncpy(sub_ex, expression+separate_pos+1, ex_len-separate_pos-2);
		if(imag_1){
			sub_ex[0]='1';
			sub_ex[1]='\0';
		}
		else sub_ex[ex_len-separate_pos-2]='\0';
		resu=Rational::from_string(sub_ex);
		if(!resu){
			resu=Float::from_string(sub_ex);
			imag_t=1;
		}
		if(resu==NULL) return NULL;
		delete [] sub_ex;
		
		if(real_t && !imag_t){
			resu=res->convert(resu);
			return new Complex(res, resu);
		}
		else if(imag_t && !real_t){
			res=resu->convert(res);
			return new Complex(res, resu);
		}
		return new Complex(res, resu);
	}
	if(!flag_p){
		sub_ex = new char [separate_pos+2];
		sub_ex = strncpy(sub_ex, expression, separate_pos);
		sub_ex[separate_pos]='\0';
		res=Rational::from_string(sub_ex);
		if(!res){
			res=Float::from_string(sub_ex);
			real_t=1;
		}
		if(res==NULL) return NULL;
		delete [] sub_ex;
		sub_ex = new char [ex_len-separate_pos+1];
		sub_ex = strncpy(sub_ex, expression+separate_pos, ex_len-separate_pos-1);
		if(imag_1){
			sub_ex[1]='1';
			sub_ex[2]='\0';
		}
		else sub_ex[ex_len-separate_pos-1]='\0';
		resu=Rational::from_string(sub_ex);
		if(!resu){
			resu=Float::from_string(sub_ex);
			imag_t=1;
		}
		if(resu==NULL) return NULL;
		delete [] sub_ex;
		
		if(real_t && !imag_t){
			resu=res->convert(resu);
			return new Complex(res, resu);
		}
		else if(imag_t && !real_t){
			res=resu->convert(res);
			return new Complex(res, resu);
		}
		return new Complex(res, resu);
	}
}

void Complex::print(){
	if(real_->type_==RATIONAL && imag_->type_==RATIONAL){
		Rational *tmp_r=SCAST_RATIONAL(real_);
		Rational *tmp_i=SCAST_RATIONAL(imag_);
		if(tmp_r->numerator_.number_=="0" && tmp_i->numerator_.number_=="0"){
			cout<<0<<endl;
			return;
		}
		if(tmp_r->numerator_.number_!="0" && tmp_i->numerator_.number_=="0"){
			tmp_r->print();
			return;
		}
		if(tmp_r->numerator_.number_=="0" && tmp_i->numerator_.number_!="0"){
			if(tmp_i->numerator_.number_=="1" && tmp_i->denominator_.number_=="1"){
				cout<<"i"<<endl;
				return;
			}
			if(tmp_i->numerator_.number_=="-1" && tmp_i->denominator_.number_=="1"){
				cout<<"-i"<<endl;
				return;
			}
			tmp_i->numerator_.print();
			if(tmp_i->denominator_ != (LongInt)"1"){
				printf("/");
				tmp_i->denominator_.print();
			}
			printf("i\n");
			return;
		}
		tmp_r->numerator_.print();
		if(tmp_r->denominator_ != (LongInt)"1"){
			printf("/");
			tmp_r->denominator_.print();
		}
		if(tmp_i->numerator_.number_[0]!='-') cout<<"+";
		if(tmp_i->numerator_.number_=="1" && tmp_i->denominator_.number_=="1"){
			cout<<"i"<<endl;
			return;
		}
		if(tmp_i->numerator_.number_=="-1" && tmp_i->denominator_.number_=="1"){
			cout<<"-i"<<endl;
			return;
		}
		tmp_i->numerator_.print();
		if(tmp_i->denominator_ != (LongInt)"1"){
			printf("/");
			tmp_i->denominator_.print();
		}
		printf("i\n");
		return;
	}
	if(real_->type_==FLOAT && imag_->type_==RATIONAL){
		Float *tmp_r = SCAST_FLOAT(real_);
		Rational *tmp_i = SCAST_RATIONAL(imag_);
		if(tmp_r->number_==0.0 && tmp_i->numerator_.number_=="0"){
			cout<<0<<endl;
			return;
		}
		if(tmp_r->number_!=0.0 && tmp_i->numerator_.number_=="0"){
			tmp_r->print();
			return;
		}
		if(tmp_r->number_==0.0 && tmp_i->numerator_.number_!="0"){
			if(tmp_i->numerator_.number_=="1" && tmp_i->denominator_.number_=="1"){
				cout<<"i"<<endl;
				return;
			}
			if(tmp_i->numerator_.number_=="-1" && tmp_i->denominator_.number_=="1"){
				cout<<"-i"<<endl;
				return;
			}
			tmp_i->numerator_.print();
			if(tmp_i->denominator_ != (LongInt)"1"){
				printf("/");
				tmp_i->denominator_.print();
			}
			printf("i\n");
			return;
		}
		if(tmp_r->number_ <1e6 && tmp_r->number_>1e-6)
			cout<<fixed<<setprecision(20)<<tmp_r->number_;
		else cout<<setprecision(20)<<tmp_r->number_;
		if(tmp_i->numerator_.number_[0]!='-') cout<<"+";
		if(tmp_i->numerator_.number_=="1" && tmp_i->denominator_.number_=="1"){
			cout<<"i"<<endl;
			return;
		}
		if(tmp_i->numerator_.number_=="-1" && tmp_i->denominator_.number_=="1"){
			cout<<"-i"<<endl;
			return;
		}
		tmp_i->numerator_.print();
		if(tmp_i->denominator_ != (LongInt)"1"){
			printf("/");
			tmp_i->denominator_.print();
		}
		printf("i\n");
		return;
	}
	if(real_->type_==RATIONAL && imag_->type_==FLOAT){
		Rational *tmp_r = SCAST_RATIONAL(real_);
		Float *tmp_i = SCAST_FLOAT(imag_);
		if(tmp_r->numerator_.number_=="0" && tmp_i->number_==0.0){
			cout<<0<<endl;
			return;
		}
		if(tmp_r->numerator_.number_!="0" && tmp_i->number_==0.0){
			tmp_r->print();
			return;
		}
		if(tmp_r->numerator_.number_=="0" && tmp_i->number_!=0.0){
			if(tmp_i->number_ <1e6 && tmp_i->number_>1e-6)
				cout<<fixed<<setprecision(20)<<tmp_i->number_<<"i"<<endl;
			else cout<<setprecision(20)<<tmp_i->number_;
			return;
		}
		tmp_r->numerator_.print();
		if(tmp_r->denominator_ != (LongInt)"1"){
			printf("/");
			tmp_r->denominator_.print();
		}
		if(tmp_i->number_>0) cout<<"+";
		if(tmp_i->number_ <1e6 && tmp_i->number_>1e-6)
			cout<<fixed<<setprecision(20)<<tmp_i->number_<<"i"<<endl;
		else cout<<setprecision(20)<<tmp_i->number_;
		return;
	}
	if(real_->type_==FLOAT && imag_->type_==FLOAT){
		Float *tmp_r = SCAST_FLOAT(real_);
		Float *tmp_i = SCAST_FLOAT(imag_);
		if(tmp_r->number_==0.0 && tmp_i->number_==0.0){
			cout<<0<<endl;
			return;
		}
		if(tmp_r->number_!=0.0 && tmp_i->number_==0.0){
			tmp_r->print();
			return;
		}
		if(tmp_r->number_==0.0 && tmp_i->number_!=0.0){
			if(tmp_i->number_<1e6 && tmp_i->number_>1e-6)
				cout<<fixed<<setprecision(20)<<tmp_i->number_<<"i"<<endl;
			else cout<<setprecision(20)<<tmp_i->number_<<"i"<<endl;
			return;
		}
		if(tmp_r->number_<1e6 && tmp_r->number_>1e-6)
			cout<<fixed<<setprecision(20)<<tmp_r->number_;
		else cout<<setprecision(20)<<tmp_r->number_;
		if(tmp_i->number_>0) cout<<"+";
		if(tmp_i->number_<1e6 && tmp_i->number_>1e-6)
			cout<<fixed<<setprecision(20)<<tmp_i->number_<<"i"<<endl;
		else cout<<setprecision(20)<<tmp_i->number_<<"i"<<endl;
		return;
	}
}
