#pragma once
#include "number.h"

#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Float : public Number {
public:
	Float(double number = 0);
	virtual ~Float();

	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual void print();
	static Float *from_string(char *expression);
	double number_;

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
