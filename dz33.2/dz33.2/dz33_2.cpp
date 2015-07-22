#include <iostream>
using namespace std;

class exceptionError {
public:
	int param;
	exceptionError(int param_) : param(param_)
	{

	}
};

class stack {
	int N;				// величина стека первоначальная
	int *arr;
	int idxTop;
public:
	stack()
	{
		N = 2;
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
			throw exceptionError(0);
		}
	}

	void pop()
	{
		if (idxTop != -1) {
			arr[idxTop--] = -1;
		}
		else {
			throw exceptionError(1);
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

	void increaseStack()
	{
		int *temp = new int[N];
		temp = arr;				// перезаписываем
		N *= 2;					// увеличиваем N в два раза
		arr = new int[N];		// выделяем новую память
		initArray(-1);			// заполняем
		idxTop = -1;
		delete[]temp;
	}

	~stack()
	{
		delete[]arr;
	}
};

int main() {
	stack st1;
	while (true) {
		try {
			st1.push(30);
			st1.push(17);
			st1.push(25);
			st1.pop();
			st1.push(30);
			st1.push(17);
			st1.push(25);
			st1.push(30);
			st1.push(17);
			st1.push(99);
			break;
		}
		catch (exceptionError& ex) {
			if (ex.param) {
				cout << "Stack is empty" << endl;
				break;
			}
			else {
				st1.increaseStack();
			}
		}
	}
	st1.show();

	return 0;
}