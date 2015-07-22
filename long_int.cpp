#include "long_int.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int compare(string str1,string str2)
{
    if(str1.length()>str2.length()) return 1;
    else if(str1.length()<str2.length())  return -1;
    else return str1.compare(str2);
}

string long_add(string str1,string str2)
{
    string str;

    int len1=str1.length();
    int len2=str2.length();
    
    if(len1<len2)
    {
        for(int i=1;i<=len2-len1;i++)
           str1="0"+str1;
    }
    else
    {
        for(int i=1;i<=len1-len2;i++)
           str2="0"+str2;
    }
    len1=str1.length();
    int cf=0;
    int temp;
    for(int i=len1-1;i>=0;i--)
    {
        temp=str1[i]-'0'+str2[i]-'0'+cf;
        cf=temp/10;
        temp%=10;
        str=char(temp+'0')+str;
    }
    if(cf!=0)  str=char(cf+'0')+str;
    return str;
}

string long_sub(string str1,string str2)
{
    string str;
    if(str1==str2) return "0";
    int tmp=str1.length()-str2.length();
    int cf=0;
    for(int i=str2.length()-1;i>=0;i--)
    {
        if(str1[tmp+i]<str2[i]+cf)
        {
            str=char(str1[tmp+i]-str2[i]-cf+'0'+10)+str;
            cf=1;
        }
        else
        {
            str=char(str1[tmp+i]-str2[i]-cf+'0')+str;
            cf=0;
        }
    }
    for(int i=tmp-1;i>=0;i--)
    {
        if(str1[i]-cf>='0')
        {
            str=char(str1[i]-cf)+str;
            cf=0;
        }
        else
        {
            str=char(str1[i]-cf+10)+str;
            cf=1;
        }
    }
    str.erase(0,str.find_first_not_of('0'));
    return str;
}

string long_mul(string str1,string str2)
{
    string str;
    if(str1=="0" || str2=="0") return "0";
    int len1=str1.length();
    int len2=str2.length();
    string tempstr;
    for(int i=len2-1;i>=0;i--)
    {
        tempstr="";
        int temp=str2[i]-'0';
        int t=0;
        int cf=0;
        if(temp!=0)
        {
            for(int j=1;j<=len2-1-i;j++)
              tempstr+="0";
            for(int j=len1-1;j>=0;j--)
            {
                t=(temp*(str1[j]-'0')+cf)%10;
                cf=(temp*(str1[j]-'0')+cf)/10;
                tempstr=char(t+'0')+tempstr;
            }
            if(cf!=0) tempstr=char(cf+'0')+tempstr;
        }
        str=long_add(str,tempstr);
    }
    str.erase(0,str.find_first_not_of('0'));
    return str;
}

string long_div(string str1,string str2)
{
	string quotient="";
	string residue="";
    quotient=residue="";
    if(str1=="0")
    {
        quotient=residue="0";
        return quotient;
    }
    int res=compare(str1,str2);
    if(res<0)
    {
        quotient="0";
        residue=str1;
        return quotient;
    }
    else if(res==0)
    {
        quotient="1";
        residue="0";
        return quotient;
    }
    else
    {
        int len1=str1.length();
        int len2=str2.length();
        string tempstr;
        tempstr.append(str1,0,len2-1);
        for(int i=len2-1;i<len1;i++)
        {
            tempstr=tempstr+str1[i];
            tempstr.erase(0,tempstr.find_first_not_of('0'));
            if(tempstr.empty())
              tempstr="0";
            for(char ch='9';ch>='0';ch--)
            {
                string str,tmp;
                str=str+ch;
                tmp=long_mul(str2,str);
                if(compare(tmp,tempstr)<=0)
                {
                    quotient=quotient+ch;
                    tempstr=long_sub(tempstr,tmp);
                    break;
                }
            }
        }
        residue=tempstr;
    }
    quotient.erase(0,quotient.find_first_not_of('0'));
    if(quotient.empty()) quotient="0";
    if(residue.empty()) residue="0";
    return quotient;
}

LongInt::LongInt(string number) : number_(number){

}

LongInt::LongInt(const LongInt &long_int2) : number_(long_int2.number_){

}

LongInt::~LongInt(){

}

LongInt::operator bool(){
	if(number_=="0") return false;
	else return true;
}

LongInt::operator double(){
	double result_, tmp=0;
	bool flag=1;
	if(number_[0]=='-') flag=0;
	if(flag){
		tmp=(number_[0]-'0');
		for(int i=1; i<number_.size(); ++i){
			tmp*=10;
			tmp+=(number_[i]-'0');
		}
		result_=tmp;
		return result_;
	}
	else{
		tmp=(number_[1]-'0');
		for(int i=2; i<number_.size(); ++i){
			tmp*=10;
			tmp+=(number_[i]-'0');
		}
		result_=-1*tmp;
		return result_;
	}
}


bool LongInt::operator!=(const LongInt &long_int2) const{
	return number_ != long_int2.number_;
}

bool LongInt::operator<(const LongInt &long_int2) const{
	if(number_[0]=='-' && long_int2.number_[0]!='-') return true;
	if(number_[0]!='-' && long_int2.number_[0]=='-') return false;
	if(number_[0]!='-'){
		if(number_.size()<long_int2.number_.size()) return true;
		if(number_.size()>long_int2.number_.size()) return false;
		for(int i=0; i<number_.size(); ++i){
			if(number_[i]<long_int2.number_[i]) return true;
		}
		return false;
	}
	if(number_.size()>long_int2.number_.size()) return true;
	if(number_.size()<long_int2.number_.size()) return false;
	for(int i=1; i<number_.size(); ++i){
		if(number_[i]>long_int2.number_[i]) return true;
	}
	return false;
}


LongInt &LongInt::operator=(const LongInt &long_int2){
	number_ = long_int2.number_;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
	string a, b, tmp, result_;
	if(number_[0]!='-' && long_int2.number_[0]!='-'){
		result_=long_add(number_, long_int2.number_);
	}
	if(number_[0]=='-' && long_int2.number_[0]=='-'){
		a = number_.substr(1,number_.size());
		b = long_int2.number_.substr(1,long_int2.number_.size());
		tmp = long_add(a, b);
		result_ = "-"+tmp;
	}
	if(number_[0]!='-' && long_int2.number_[0]=='-'){
		b = long_int2.number_.substr(1,long_int2.number_.size());
		if(number_==b){
			LongInt result("0");
			return result;
		}
		if(number_.size()>b.size()) result_ = long_sub(number_, b);
		else if(number_.size()<b.size()) result_='-'+long_sub(b,number_);
		else if(number_.size()==b.size()){
			if(number_>b) result_ = long_sub(number_, b);
			else result_='-'+long_sub(b,number_);
		}
	}
	if(number_[0]=='-' && long_int2.number_[0]!='-'){
		a = number_.substr(1,number_.size());
		if(a==long_int2.number_){
			LongInt result("0");
			return result;
		}
		if(a.size()>long_int2.number_.size())tmp = long_sub(a, long_int2.number_);
		else if(a.size()<long_int2.number_.size()) tmp='-'+long_sub(long_int2.number_, a);
		else if(a.size()==long_int2.number_.size()){
			if(a>long_int2.number_) tmp=long_sub(a, long_int2.number_);
			else tmp='-'+long_sub(long_int2.number_, a);
		}
		if(tmp[0]=='-') result_=tmp.substr(1, tmp.size());
		else result_ = '-'+tmp;
	}
	
	LongInt result(result_);
	return result;
}

LongInt LongInt::operator-(const LongInt &long_int2) const{
	string a, b, tmp, result_;
	if(number_[0]!='-' && long_int2.number_[0]!='-'){
		if(number_==long_int2.number_){
			LongInt result("0");
			return result;
		}
		if(number_.size()>long_int2.number_.size()) result_=long_sub(number_, long_int2.number_);
		else if(number_.size()<long_int2.number_.size()) result_='-'+long_sub(long_int2.number_, number_);
		else if(number_.size()==long_int2.number_.size()){
			if(number_>long_int2.number_) result_=long_sub(number_, long_int2.number_);
			else result_='-'+long_sub(long_int2.number_, number_);
		}
	}
	if(number_[0]=='-' && long_int2.number_[0]=='-'){
		a = number_.substr(1,number_.size());
		b = long_int2.number_.substr(1,long_int2.number_.size());
		if(a==b){
			LongInt result("0");
			return result;
		}
		if(b.size()>a.size()) result_ = long_sub(b, a);
		else if(b.size()<a.size()) result_='-'+long_sub(a,b);
		else if(b.size()==a.size()){
			if(b>a) result_ = long_sub(b, a);
			else result_='-'+long_sub(a,b);
		}
	}
	if(number_[0]!='-' && long_int2.number_[0]=='-'){
		b = long_int2.number_.substr(1,long_int2.number_.size());
		result_ = long_add(number_, b);
	}
	if(number_[0]=='-' && long_int2.number_[0]!='-'){
		a = number_.substr(1,number_.size());
		tmp = long_add(a, long_int2.number_);
		result_='-'+tmp;
	}
	
	if(result_=="-0") result_="0";
	LongInt result(result_);
	return result;
}


LongInt LongInt::operator*(const LongInt &long_int2) const{
	string a, b, tmp, result_;
	if(number_=="0" || long_int2.number_=="0"){
		result_="0";
		LongInt result(result_);
		return result;
	}
	if(number_[0]!='-' && long_int2.number_[0]!='-'){
		result_=long_mul(number_, long_int2.number_);
	}
	if(number_[0]=='-' && long_int2.number_[0]=='-'){
		a=number_.substr(1, number_.size());
		b=long_int2.number_.substr(1, long_int2.number_.size());
		result_=long_mul(a, b);
	}
	if(number_[0]!='-' && long_int2.number_[0]=='-'){
		b=long_int2.number_.substr(1, long_int2.number_.size());
		tmp=long_mul(number_, b);
		result_='-'+tmp;
	}
	if(number_[0]=='-' && long_int2.number_[0]!='-'){
		a=number_.substr(1, number_.size());
		tmp=long_mul(a, long_int2.number_);
		result_='-'+tmp;
	}
	
	LongInt result(result_);
	return result;
}

LongInt LongInt::operator/(const LongInt &long_int2) const{
	assert(long_int2.number_!="0");
	string a, b, tmp, result_;
	if(number_=="0"){
		result_="0";
		LongInt result(result_);
		return result;
	}
	if(number_[0]!='-' && long_int2.number_[0]!='-'){
		result_=long_div(number_, long_int2.number_);
	}
	if(number_[0]=='-' && long_int2.number_[0]=='-'){
		a=number_.substr(1, number_.size());
		b=long_int2.number_.substr(1, long_int2.number_.size());
		result_=long_div(a, b);
	}
	if(number_[0]!='-' && long_int2.number_[0]=='-'){
		b=long_int2.number_.substr(1, long_int2.number_.size());
		tmp=long_div(number_, b);
		result_='-'+tmp;
	}
	if(number_[0]=='-' && long_int2.number_[0]!='-'){
		a=number_.substr(1, number_.size());
		tmp=long_div(a, long_int2.number_);
		result_='-'+tmp;
	}
	
	LongInt result(result_);
	return result;
}

LongInt LongInt::operator%(const LongInt &long_int2) const{
	assert(long_int2.number_!="0");
	string a, b, tmp1, tmp2, result_;
	if(number_=="0"){
		result_="0";
		LongInt result(result_);
		return result;
	}
	if(number_[0]!='-' && long_int2.number_[0]!='-'){
		tmp1=long_div(number_, long_int2.number_);
		tmp2=long_mul(tmp1, long_int2.number_);
		result_=long_sub(number_, tmp2);
	}
	if(number_[0]=='-' && long_int2.number_[0]=='-'){
		a=number_.substr(1, number_.size());
		b=long_int2.number_.substr(1, long_int2.number_.size());
		tmp1=long_div(a, b);
		tmp2=long_mul(tmp1, b);
		result_='-'+long_sub(a, tmp2);
	}
	if(number_[0]!='-' && long_int2.number_[0]=='-'){
		b=long_int2.number_.substr(1, long_int2.number_.size());
		tmp1=long_div(number_, b);
		tmp2=long_mul(tmp1, b);
		result_=long_sub(number_, tmp2);
	}
	if(number_[0]=='-' && long_int2.number_[0]!='-'){
		a=number_.substr(1, number_.size());
		tmp1=long_div(a, long_int2.number_);
		tmp2=long_mul(tmp1, long_int2.number_);
		result_='-'+long_sub(a, tmp2);
	}
	if(result_=="-0") result_="0";
	
	LongInt result(result_);
	return result;
}

LongInt max(const LongInt &long_int1, const LongInt &long_int2){
	if(long_int1.number_[0]!='-' && long_int2.number_[0]=='-'){
		LongInt result(long_int1.number_);
		return result;
	}
	if(long_int1.number_[0]=='-' && long_int2.number_[0]!='-'){
		LongInt result(long_int2.number_);
		return result;
	}
	if(long_int1.number_[0]!='-' && long_int2.number_[0]!='-'){
		if(long_int1.number_.size()>long_int2.number_.size()){
			LongInt result(long_int1.number_);
			return result;
		}
		if(long_int1.number_.size()<long_int2.number_.size()){
			LongInt result(long_int2.number_);
			return result;
		}
		LongInt result(MAX(long_int1.number_, long_int2.number_));
		return result;
	}
	if(long_int1.number_[0]=='-' && long_int2.number_[0]=='-'){
		if(long_int1.number_.size()<long_int2.number_.size()){
			LongInt result(long_int1.number_);
			return result;
		}
		if(long_int1.number_.size()>long_int2.number_.size()){
			LongInt result(long_int2.number_);
			return result;
		}
		LongInt result(MIN(long_int1.number_, long_int2.number_));
		return result;
	}
}

LongInt min(const LongInt &long_int1, const LongInt &long_int2){
	if(long_int1.number_[0]!='-' && long_int2.number_[0]=='-'){
		LongInt result(long_int2.number_);
		return result;
	}
	if(long_int1.number_[0]=='-' && long_int2.number_[0]!='-'){
		LongInt result(long_int1.number_);
		return result;
	}
	if(long_int1.number_[0]!='-' && long_int2.number_[0]!='-'){
		if(long_int1.number_.size()<long_int2.number_.size()){
			LongInt result(long_int1.number_);
			return result;
		}
		if(long_int1.number_.size()>long_int2.number_.size()){
			LongInt result(long_int2.number_);
			return result;
		}
		LongInt result(MIN(long_int1.number_, long_int2.number_));
		return result;
	}
	if(long_int1.number_[0]=='-' && long_int2.number_[0]=='-'){
		if(long_int1.number_.size()>long_int2.number_.size()){
			LongInt result(long_int1.number_);
			return result;
		}
		if(long_int1.number_.size()<long_int2.number_.size()){
			LongInt result(long_int2.number_);
			return result;
		}
		LongInt result(MAX(long_int1.number_, long_int2.number_));
		return result;
	}
}

void LongInt::print(){
	cout<<number_;
}

//int main(){
//	LongInt a("-1"), b("-2"), c;
//	//double d=(double) a;
//	//cout<<d<<endl;
//	c=a-b;
//	c.print();
//	if(a<b) cout<<"YES"<<endl;
//	return 0;
//}
