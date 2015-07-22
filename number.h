#pragma once

#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Number {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		COMPLEX = 3
	} type_;
	Number(){}
	virtual ~Number(){}
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2)  = 0;
	virtual Number *sub(Number *number2)  = 0;
	virtual Number *mul(Number *number2)  = 0;
	virtual Number *div(Number *number2)  = 0;
	virtual void print() = 0;

	virtual Number *real_part() = 0;
	virtual Number *imag_part() = 0;
	virtual Number *numerator() = 0;
	virtual Number *denominator() = 0;
	virtual Number *max_num(Number *number2) = 0;
	virtual Number *min_num(Number *number2) = 0;
	virtual Number *floor() = 0;
	virtual Number *ceiling() = 0;
	virtual Number *truncate() = 0;
	virtual Number *round() = 0;
	virtual Number *abs() = 0;
	virtual Number *quotient(Number *number2) = 0;
	virtual Number *remainder(Number *number2) = 0;
	virtual Number *modulo(Number *number2) = 0;
	virtual Number *gcd(Number *number2) = 0;
	virtual Number *lcm(Number *number2) = 0;
	virtual Number *expt(Number *number2) = 0;
	virtual Number *sqrt() = 0;
	virtual Number *inexact() = 0;
	virtual Number *exact() = 0;
};
