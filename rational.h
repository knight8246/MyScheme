#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	Rational(string numerator = "0", string denominator = "1");
	virtual ~Rational();

	void reduce();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual void print();
	static Rational *from_string(char *expression);
	LongInt numerator_;
	LongInt denominator_;

	virtual Number *real_part();
	virtual Number *imag_part();
	virtual Number *numerator();
	virtual Number *denominator();
	virtual Number *max_num(Number *number2);
	virtual Number *min_num(Number *number2);
	virtual Number *floor();
	virtual Number *ceiling();
	virtual Number *truncate();
	virtual Number *round();
	virtual Number *abs();
	virtual Number *quotient(Number *number2);
	virtual Number *remainder(Number *number2);
	virtual Number *modulo(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *expt(Number *number2);
	virtual Number *sqrt();
	virtual Number *inexact();
	virtual Number *exact();
};
