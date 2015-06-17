#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

class stek {
	int N;
	int *arr;
	int idxTop;
public:
	stek()
	{
		N = 32;
		arr = new int[N];
		initArray(-1);
		idxTop = -1;
	}

	void push(int n)
	{
		if (idxTop < N - 1) {
			arr[++idxTop] = n;
		}
		else {
			int *temp = new int[N];
			temp = arr;
			N *= 2;
			arr = new int[N];
			initArray(-1);
			for (int i = 0, m = N / 2; i < m; ++i) {
				arr[i] = temp[i];
			}
			push(n);
			delete[]temp;
		}
	}

	void pop()
	{
		if (idxTop != -1) {
			arr[idxTop--] = -1;
		}
		else {
			cout << "Stek is empty\n";
		}
	}

	int top()
	{
		if (idxTop != -1)
			return arr[idxTop];
		else
			return -1;
	}

	void show()
	{
		for (int i = 0; i < N; ++i) {
			cout << arr[i] << "\t";
		}
		cout << "\n\n";
	}

	void initArray(int n)
	{
		for (int i = 0; i < N; ++i) {
			arr[i] = n;
		}
	}

	~stek()
	{
		delete[]arr;
	}
};

class stringer {
	char *str;
	int size;
public:

	stringer(char *str)
	{
		size = strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}

	stringer(const stringer &obj)
	{
		str = new char[strlen(obj.str) + 1];
		size = strlen(obj.str);
		strcpy(str, obj.str);
	}

	stringer& operator = (const stringer &obj)
	{
		if (this != &obj) {
			str = new char[strlen(obj.str) + 1];
			size = strlen(obj.str);
			strcpy(str, obj.str);
		}

		return *this;
	}

	void showString()
	{
		cout << str << "\n";
	}

	char * getString()
	{
		return str;
	}

	~stringer()
	{
		delete[]str;
	}
};

template <class T>
class Array {
	T **ptrString = nullptr;	//указатель на массив указателей объектов
	int curSize = 0;
public:
	Array()
	{

	}

	Array(const Array &obj)
	{
		curSize = obj.curSize;
		ptrString = new T*[curSize];
		for (int i = 0; i < curSize; ++i) {
			ptrString[i] = obj.ptrString[i];
		}
	}

	Array& operator = (const Array &obj) {
		if (this != &obj) {
			curSize = obj.curSize;
			ptrString = new T*[curSize];
			for (int i = 0; i < curSize; ++i) {
				ptrString[i] = obj.ptrString[i];
			}
		}
		return *this;
	}

	T*&operator [] (int index)
	{
		if (index >= 0 && index < curSize) {
			return ptrString[index];
		}
		else
			return ptrString[curSize - 1];
	}

	void Append(const Array &objFirst, const Array &objSecond)
	{
		curSize = objFirst.curSize + objSecond.curSize;
		ptrString = new T*[curSize];
		int i, j;
		for (i = 0; i < objFirst.curSize; ++i) {
			ptrString[i] = objFirst.ptrString[i];
		}
		j = i;
		for (i = 0; i < objSecond.curSize; ++i, ++j) {
			ptrString[j] = objSecond.ptrString[i];
		}
	}

	void add(T *ptr)
	{
		if (!curSize) {
			ptrString = new T*[curSize + 1];
		}
		else {
			ptrString = (T**)realloc(ptrString, sizeof(T*)* (curSize + 1));
		}
		ptrString[curSize++] = ptr;
	}

	void show()
	{
		for (int i = 0; i < curSize; ++i) {
			cout << ptrString[i] << "\t";
		}
		cout << endl;
	}

	Array * GetData()
	{
		return this;
	}

	void InsertAt(int index, T *ptr)
	{
		if (index < 0 || index > curSize) {
			return;
		}
		if (!curSize) {
			ptrString = new T*[curSize + 1];
		}
		else {
			ptrString = (T**)realloc(ptrString, sizeof(T*)* (curSize + 1));
		}
		++curSize;
		T *temp;
		for (int i = 0; i < curSize; ++i) {
			if (i >= index) {
				temp = ptrString[i];
				ptrString[i] = ptr;		//ptr больше нам не нужен
				ptr = temp;
			}
		}
	}

	void RemoveAt(int index)
	{
		if (index < 0 || index >= curSize) {
			return;
		}
		T *first = nullptr;
		for (int i = 0; i < curSize - 1; ++i) {
			if (i >= index) {
				ptrString[i] = ptrString[i + 1];
			}
		}
		ptrString = (T**)realloc(ptrString, sizeof(T*)* (--curSize));		// уменьшаем на единицу
	}

	void SetAt(int index, T *ptr)
	{
		if (index < 0 || index >= curSize) {
			return;
		}
		for (int i = 0; i < curSize; ++i) {
			if (i == index) {
				ptrString[i] = ptr;
				break;
			}
		}
	}

	T *GetAt(int index)
	{
		if (index < 0 || index >= curSize) {
			return nullptr;
		}
		T *temp = nullptr;
		for (int i = 0; i < curSize; ++i) {
			if (i == index) {
				temp = ptrString[i];
				break;
			}
		}
		return temp;
	}

	void removeAll()
	{
		if (curSize) {
			ptrString = (T**)realloc(ptrString, sizeof(T*)* (0));
			curSize = 0;
		}
	}

	bool isEmpty()
	{
		bool flag = false;
		if (curSize) {
			flag = true;
		}

		return flag;
	}

	int getSize()
	{
		return curSize;
	}

	~Array()
	{
		if (curSize) {
			delete[]ptrString;
		}
	}
};

int main() {
	stringer str1("str1");
	stringer str2("str2");
	stringer str3("str3");
	stringer str4("str4");
	stringer str5("str5");
	stek st1;
	st1.push(25);
	st1.push(30);
	st1.push(19);
	stek st2;
	st2.push(5);
	st2.push(3);
	st2.push(40);
	Array<stringer> ar1;
	ar1.add(&str1);
	ar1.add(&str3);
	ar1.add(&str2);
	ar1.add(&str5);
	ar1.add(&str2);
	ar1.show();
	stringer *temp = ar1.GetAt(1);
	Array<stringer> ar2 = ar1;
	//ar1.SetAt(4, temp);
	ar2[4] = temp;
	cout << ar1.getSize() << endl;
	ar1.show();
	Array<stek> ar3;
	ar3.add(&st1);
	ar3.add(&st2);
	ar3.add(&st2);
	ar3.show();

	return 0;
}