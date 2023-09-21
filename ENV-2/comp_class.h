#pragma once

#ifndef HEADER_CLASS
#define HEADER_CLASS
//Header for comp_class.cpp


class Complex {
public:
	int re;
	int im;
	Complex Add(Complex x, Complex y);
	Complex Sub(Complex x, Complex y);
	Complex MulC(Complex x, int y);
	unsigned int Abs(Complex x);
};

#endif