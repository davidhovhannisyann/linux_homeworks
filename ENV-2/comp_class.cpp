#include <iostream>
#include <cmath>

class Complex {
public:
	int re;
	int im;
	Complex(int x, int y) {
		re = x;
		im = y;
	}
	~Complex(){}
	
	Complex Add(Complex x, Complex y) {
		x.re += y.re;
		x.im += x.im;
		return x;
	};
	Complex Sub(Complex x, Complex y) {
		x.re -= y.re;
		x.im -= x.im;
		return x;
	};
	Complex MulC(Complex x, int y) {
		x.re *= y;
		x.im *= y;
		return x;
	};
	unsigned int Abs(Complex x) {
		unsigned int abs = std::sqrt((x.re * x.re) + (x.im * x.im));
		return abs;
	};
};
