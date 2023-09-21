#include <iostream>
#include "comp_sort.h"

void sortComp(Complex* arr, int length) {
	int real = 0, imag = 0;
	bool swap = false;
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1; j++) {
			if (arr[j].re > arr[j + 1].re) {
				real = arr[j].re;
				imag = arr[j].im;
				arr[j].re = arr[j + 1].re;
				arr[j].im = arr[j + 1].im;
				arr[j+1].re = real;
				arr[j+1].im = imag;
				swap = true;
			}
		}
		if (swap == false) {
			break;
		}
	}
}

void printCompArr(Complex *arr, int length) {
	for (int i = 0; i < length; i++) {
		cout << "El : " << i << "  || Re : " << arr[i].re << " Im : " << arr[i].im << endl;
	}
}