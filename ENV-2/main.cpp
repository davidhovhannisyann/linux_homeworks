#include <iostream>
#include "comp_sort.h"

int main() {
	int length = 10;
	Complex* array = new Complex[length];
	cout << "Array : " << endl;
	for (int i = 0; i < length; i++) {
		array[i].re = length - i;
		array[i].im = i;
	}
	printCompArr(array, length);
	
	sortComp(array, length);
	cout << endl << "Sorted Array : " << endl;
	printCompArr(array, length);

	return 0;
}
