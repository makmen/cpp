#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class massiv {
	int size;
	int *arr;

public:

	massiv(int size) {
		this->size = size;
		if (size > 0) {
			arr = new int[size]; 
		}
	}

	massiv(const massiv &obj) {
		size = obj.size;
		arr = new int[obj.size];
		for(int i = 0; i < size; ++i) {
			 *(arr + i) = obj.arr[i];
		}
	}

	void fillMass() {
		// srand(time(NULL));
		srand(20);
		for(int i = 0; i < this->size; ++i) {
			 *(arr + i) = rand() % 41;
		}
	}

	void showArray() {
		for (int i = 0; i < size; ++i) {
			cout << *(arr + i) << "\n"; 
		}
		cout << "\n";
	}

	int & operator [] (int index) {
		if (index >= 0 && index < size) {

			return arr[index];

		} else 

			return arr[size - 1];
	}

	massiv& operator = (const massiv &obj) {
		if (this != &obj) {
			size = obj.size;
			arr = new int[obj.size];
			for(int i = 0; i < size; ++i) {
				 *(arr + i) = obj.arr[i];
			}
		}

		return *this;
	}

	massiv operator + (const massiv &obj) {
		int n = size + obj.size; 
		massiv temp(n);
		for(int i = 0; i < size; ++i) {
			*(temp.arr + i) = *(arr + i);
		}
		for(int i = 0, j = size; i < obj.size; ++i, ++j) {
			*(temp.arr + j) = *(obj.arr + i);
		}

		return temp;
	}

	massiv operator - (const massiv &obj) {
		// Разность двух массивов arr1 и arr2 - элементы массива arr1, которых нет в массиве arr2.
		int *buff, j = 0;
		buff = new int[size];
		for (int i = 0; i < size; ++i) {
			if (inArray(*(arr + i), obj.arr, obj.size)) {
				*(buff + j) = *(obj.arr + i); 
				++j;
			}
		}
		massiv temp(j);
		for(int i = 0; i < j; ++i) {
			*(temp.arr + i) = *(buff + i);
		}

		return temp;
	}

	bool inArray(int search, int *arr, int size) {
		bool ret = false;
		for (int i = 0; i < size; ++i) {
			if (*(arr + i) == search) {
				ret = true;
				break;
			}
		}

		return ret;
	}

	massiv operator ++ (int) {
		int i, n = size + 1; 
		massiv temp(n);
		for(i = 0; i < size; ++i) {
			*(temp.arr + i) = *(arr + i);
		}
		srand(time(NULL));
		*(temp.arr + i) = rand() % 41;

		return temp;
	}

	massiv operator -- (int) {
		size--;
		massiv temp(size);
		for(int i = 0; i < size; ++i) {
			*(temp.arr + i) = *(arr + i);
		}

		return temp;
	}

	~massiv() {
		if (size) {
			delete []arr;
		}
	}
};

int main() {
	massiv A(7);
	A.fillMass();
	A[2] = 155;
	A.showArray();

	massiv B = A;
	B.showArray();

	massiv C(3);
	C = B;
	C.showArray();

	massiv E(6);
	E.fillMass();
	E.showArray();

	massiv D(10);
	D = A + E;
	D.showArray();

	massiv F1(4);
	F1.fillMass();
	F1.showArray();

	massiv F2(8);
	F2.fillMass();
	F2.showArray();

	massiv F3(5);
	F3 = F1 - F2;
	F3.showArray();

	F3 = F3++;
	F3.showArray();

	massiv F4(10);
	F4.fillMass();
	F4.showArray();
	F4--;
	F4.showArray();


	return 0;
}