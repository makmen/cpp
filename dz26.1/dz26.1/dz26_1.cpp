#include <iostream>
#include <stdlib.h>
#include <time.h>
#define N 6
using namespace std;

class drum {

	char *arr;

public:

	drum()
	{
		srand(time(NULL));
		arr = new char[N];
		fillQueue();
	}

	void shift()
	{
		int first = arr[0];
		for (int i = 0; i < N - 1; ++i) {
			arr[i] = arr[i + 1];
		}
		arr[N - 1] = first;
	}

	void fillQueue()
	{
		for (int i = 0, j = 33; i < N; ++i, ++j) {
			arr[i] = j;
		}
	}

	char twist()
	{
		int rnd = rand() % 20;
		for (int i = 0; i < rnd; ++i) {
			shift();
		}

		return arr[0];
	}

	void show()
	{
		for (int i = 0; i < N; ++i) {
			cout << arr[i] << "\t";
		}
		cout << "\n\n";
	}

	~drum()
	{
		delete[]arr;
	}
};

int main() {
	setlocale(LC_CTYPE, "Russian");
	cout << "Добро пожаловать в игру однорукий бандит\n";
	drum d1;
	drum d2;
	drum d3;
	char symbol, ch;
	char res1, res2, res3;
	cout << "Нажмите Enter чтобы продолжить игру\n";
	while ((ch = getchar()) != '\n');
	while (true) {
		res1 = d1.twist();
		res2 = d2.twist();
		res3 = d3.twist();
		cout << res1 << " " << res2 << " " << res3 << "\n";
		if (res1 == res2 && res1 == res3) {
			cout << "Вы выиграли!!! Ура!!!\n";
		}
		else {
			cout << "Вы проиграли\n";
		}
		cout << "Продолжить игру, y - да, n - нет?\n";
		cin >> (char)symbol;
		while ((ch = getchar()) != '\n');
		if (symbol == 'n') {
			cout << "До свидания\n";
			break;
		}
	}

	return 0;
}