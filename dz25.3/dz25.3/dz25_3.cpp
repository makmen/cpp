#include <iostream>
#include <stdarg.h>
#define N 15
using namespace std;

void myprintf(char *, ...);
bool poiskQualifier(char, char[], int);
void showString(char *);
void showPartOfstring(char *, int, int);

void main()
{
	int a = 5;

	// пустая 
	myprintf("empty");

	// целые числа
	myprintf("in%dyyyyyYy%iu%uiisum%ms_%x_%X_%o_", 125, 6587, 4, 35, 45, 99);

	// вещественные числа
	myprintf("double %f_long double %L_exp%e_%E_", 14.2, 0.8345 * 10000000000, 105.165, 100.0);

	// символы и строки
	myprintf("i%cpill%ssms", 'f', "(string)");

	// указатели 
	myprintf("pointer: %p_", &a);

}

void myprintf(char *str, ...) {
	char arr[N] = { 'd', 'i', 'o', 'u', 'x', 'X', 'h', 'e', 'E', 'f', 'l', 'L', 'c', 's', 'p' };
	// анализируем строку на поиск процентов
	int count = 0;			// количество параметров
	for (int i = 0, n = strlen(str); i < n; ++i) {
		if (str[i] == '%' && i != (n - 1)) {
			// смотрим следующее значение
			if (str[i + 1] != '%' && poiskQualifier(str[i + 1], arr, N)) {
				++count;
			}
		}
	}
	if (count) {
		char *temp = new char[count + 1];
		int *pos = new int[count];
		// забираем спецификаторы
		for (int i = 0, j = 0, n = strlen(str); i < n; ++i) {
			if (str[i] == '%' && i != (n - 1)) {
				if (str[i + 1] != '%' && poiskQualifier(str[i + 1], arr, N)) {
					temp[j] = str[++i];
					pos[j++] = i;
				}
			}
		}
		*(temp + count) = '\0';
		va_list arg_ptr;			// создаём указатель на список параметров
		va_start(arg_ptr, str);		// получаем этот указатель, отталкиваясь  от первого фактического параметра
		showPartOfstring(str, 0, pos[0] - 1);
		for (int i = 0; i < count; ++i) {
			switch (temp[i]) {
			case 'd': case 'i':
				cout.unsetf(ios::oct);
				cout.unsetf(ios::hex);
				cout.setf(ios::dec);
				cout << va_arg(arg_ptr, int);
				break;
			case 'o':
				cout.unsetf(ios::dec);
				cout.unsetf(ios::hex);
				cout.setf(ios::oct);
				cout << va_arg(arg_ptr, int);
				break;
			case 'u':
				cout.setf(ios::dec);
				cout.unsetf(ios::hex);
				cout.setf(ios::dec);
				cout << va_arg(arg_ptr, unsigned int);
				break;
			case 'x': case 'X':
				cout.unsetf(ios::dec);
				cout.unsetf(ios::oct);
				cout.setf(ios::hex);
				cout << va_arg(arg_ptr, int);
				break;
			case 'e': case 'E':
				cout.unsetf(ios::fixed);
				cout.setf(ios::scientific);
				cout << va_arg(arg_ptr, double);
				break;
			case 'f':
				cout.unsetf(ios::scientific);
				cout.setf(ios::fixed);
				cout << va_arg(arg_ptr, long double);
				break;
			case 'L':
				cout.unsetf(ios::scientific);
				cout.setf(ios::fixed);
				cout << va_arg(arg_ptr, long double);
				break;
			case 'c':
				cout << va_arg(arg_ptr, char);
				break;
			case 's':
				cout << va_arg(arg_ptr, char *);
				break;
			case 'p':
				cout << va_arg(arg_ptr, int *);
				break;
			}
			if (i != (count - 1)) {
				showPartOfstring(str, pos[i] + 1, pos[i + 1] - 1);
			}
			else {
				showPartOfstring(str, pos[i] + 1, strlen(str));
			}
		}
		va_end(arg_ptr); // закрываем список параметров
		delete[]pos;
		delete[]temp;
		cout << endl;
	}
	else {
		cout << str << endl;
	}
}

void showPartOfstring(char *str, int istart, int ind) {
	for (int i = istart; i < ind; ++i) {
		cout << str[i];
	}
}

void showString(char *line) {
	int i, n;
	for (i = 0, n = strlen(line); i < n; ++i) {
		printf("%c", *(line + i));
	}
	printf("\n");
}

bool poiskQualifier(char ch, char arr[], int size) {
	for (int i = 0; i < size; ++i) {
		if (arr[i] == ch) {

			return true;

		}
	}

	return false;
}
