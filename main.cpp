#include "calc_exp.h"
#include <iostream>
#include<cstdlib>
using namespace std;

int main() {
    try {
		Number *res;
		res = calc_exp();
		res -> print();
	}
	catch(int){cerr<<"Wrong";}
	//system("pause");
    return 0;
}
