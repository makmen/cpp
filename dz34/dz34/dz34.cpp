#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h> 

using namespace std;

template <class T>
class stek {
	T *arr = nullptr;
	int idxTop ;
public:
	stek() : idxTop(-1)
	{

	}

	void push(T ch)
	{
		int size = ++idxTop + 1;
		arr = (T *)realloc(arr, sizeof(T)* size);
		arr[idxTop] = ch;
	}

	void pop()
	{
		if (idxTop != -1) {
			arr = (T *)realloc(arr, sizeof(T)* idxTop--);
		}
	}

	void clear()
	{
		arr = (T *)realloc(arr, sizeof(T)* 0);
		idxTop = -1;
	}

	T top()
	{
		if (idxTop != -1)
			return arr[idxTop];
		return (T)0;
	}

	bool isEmpty() {
		if (idxTop == -1) {
			return true;
		}

		return false;
	}

	void show()
	{
		for (int i = 0, N = idxTop + 1; i < N; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl << endl;
	}

	bool serchPoint() {
		for (int i = 0, N = idxTop + 1; i < N; ++i) {
			if (arr[i] == '.') {
				return true;
			}
		}

		return false;
	}

	~stek()
	{
		if (arr)
			delete[]arr;
	}
};

bool searchOperation(char);
int checkNumber(char, stek<char> *);
string getString(stek<char> *);
double calculate(string, string, char);
void replaceResulr(int, int, double, string &);
int runCalculationExpression(string &, int);
bool calculateBracket(string &);

int main() {
	setlocale(LC_CTYPE, "Russian");
	char open = '(';
	char closed = ')';
	stek<int> st1;
	string str = "2 * ( 4 + ((( 2 * 5) + 1)))-(2*3-(2^3)-10) + 4 * (25 - 10)";
	// удалим все пробелы из строки
	int i;
	int posi;
	while ((i = str.find(' ')) != string::npos)
		str.erase(i, 1);
	cout << str << endl;
	string calc;
	for (int i = 0, count = str.length(); i < count; ++i) {
		if (str[i] == open) {
			st1.push(i);
			continue;
		}
		if (str[i] == closed) {
			if (st1.isEmpty()) {
				st1.push(i);
				break;
			}
			// все хорошо, можно высчитывать скобки 
			posi = st1.top() + 1; 
			calc = str.substr(posi, i - posi);
			cout << calc << " = ";
			if (!calculateBracket(calc)) {
				break;
			} 
			else {
				cout << calc << endl;
				str.replace(posi - 1, i - posi + 2, calc);
				st1.clear();
				i = -1;
				count = str.length();
			}
		}
	}
	// высчитываем выражение без скобок
	cout << str << " = ";
	if (calculateBracket(str)) {
		cout << str << endl;
	}

	return 0;
}

bool searchOperation(char ch) 
{
	const int n = 5;
	char ptr[n] = { '+', '-', '*', '/', '^' };
	for (int i = 0; i < n; ++i) {
		if (ptr[i] == ch) {
			return true;
		}
	}

	return false;
}

int checkNumber(char chr, stek<char> *forNumbers)
{
	if (((int)chr >= 48 && (int)chr < 58) || (int)chr == 46)  {
		// более двух точек не должно быть
		if (chr == '.' && forNumbers->serchPoint()) {
			return -1;
		}
		forNumbers->push(chr);
		return 1;
	}

	return 0;
}

string getString(stek<char> *forNumbers)
{
	string temp;
	while (!forNumbers->isEmpty()) {
		temp += forNumbers->top();
		forNumbers->pop();
	}
	return temp;
}

double calculate(string first, string second, char chr) 
{
	double res;
	switch (chr) {
	case '^':
		res = pow(atof(first.c_str()), atof(second.c_str()));
		break;
	case '*':
		res = atof(first.c_str()) * atof(second.c_str());
		break;
	case '/':
		res = atof(first.c_str()) / atof(second.c_str());
		break;
	case '+':
		res = atof(first.c_str()) + atof(second.c_str());
		break;
	case '-':
		res = atof(first.c_str()) - atof(second.c_str());
		break;
	}

	return res;
}

void replaceResulr(int posA, int posB, double res, string &calc)
{
	string temp = to_string(res);
	calc.replace(posA, posB - posA + 1, temp);
}

int runCalculationExpression(string &calc, int i)
{
	stek<char> forNumbers;
	int position;
	int flag;
	// получаем первое число
	for (position = i - 1; position >= 0; --position) {
		flag = checkNumber(calc[position], &forNumbers);
		if (flag) {
			continue;
		}
		else if (flag == -1) {
			cout << "Error in expression: " << calc << endl;
			return -1;
		}
		// проверка на операцию
		if (!searchOperation(calc[position])) {
			cout << "Error in expression: " << calc << endl;
			return -1;
		}
		else if (calc[position] == '-' && !position) {
			forNumbers.push(calc[position]);
		}
		break;
	}
	int posA = (position) ? position + 1 : position;
	string first = getString(&forNumbers);
	int count = calc.length();
	for (position = i + 1; position < count; ++position) {
		flag = checkNumber(calc[position], &forNumbers);
		if (flag) {
			continue;
		}
		else if (flag == -1) {
			cout << "Error in expression: " << calc << endl;
			return -1;
		}
		// проверка на операцию
		if (!searchOperation(calc[position])) {
			cout << "Error in expression: " << calc << endl;
			return -1;
		}
		else if (calc[position] == '-' && forNumbers.isEmpty()) {
			forNumbers.push(calc[position]);
			continue;
		}
		else if (calc[position] == '-' && forNumbers.top() == '-') {
			forNumbers.pop();
			continue;
		}
		break;
	}
	int posB = position - 1;
	string second = getString(&forNumbers);
	reverse(second.begin(), second.end());
	if (first.empty() && calc[i] != '-') {
		cout << "Error in expression: " << calc << endl;
		return -1;
	}
	if (second.empty()) {
		cout << "Error in expression: " << calc << endl;
		return -1;
	}
	double res = calculate(first, second, calc[i]);
	replaceResulr(posA, posB, res, calc);

	return 0;
}

bool calculateBracket(string &calc) 
{
	// вычисляем сперва ^
	int j = 0;
	for (int i = 0, count = calc.length(); i < count; ++i) {
		if (calc[i] == '^') {
			j = runCalculationExpression(calc, i);
			if (j == -1) {
				return false;
			}
			else {
				count = calc.length();
				i = 0;
			}
		}
	}
	// после / или *
	for (int i = 0, count = calc.length(); i < count; ++i) {
		if ((calc[i] == '/') || (calc[i] == '*')) {
			j = runCalculationExpression(calc, i);
			if (j == -1) {
				return false;
			}
			else {
				count = calc.length();
				i = 0;
			}
		}
	}
	// вычисляем последними - или +
	for (int i = 0, count = calc.length(); i < count; ++i) {
		if ((calc[i] == '-') || (calc[i] == '+')) {
			j = runCalculationExpression(calc, i);
			if (j == -1) {
				return false;
			}
			else {
				count = calc.length();
				i = 0;
			}
		}
	}

	return true;
}