#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class matrix {

	int **p;
	int N;
	int M;

public:

	matrix(int _N, int _M) : N(_N), M(_M)
	{
		p = new int*[N];
		for (int i = 0; i < N; ++i) {
			p[i] = new int[M];
		}
		fillMatrica();
	}

	matrix(const matrix &obj) 
	{
		N = obj.N;
		M = obj.M;
		p = new int*[N];
		for (int i = 0; i < N; ++i) {
			p[i] = new int[M];
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				p[i][j] = obj.p[i][j];
			}
		}
	}

	matrix& operator = (const matrix &obj) 
	{
		if (this != &obj) {
			N = obj.N;
			M = obj.M;
			p = new int*[N];
			for (int i = 0; i < N; ++i) {
				p[i] = new int[M];
			}
			for (int i = 0; i < N; ++i) {
				p[i] = new int[M];
			}
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					p[i][j] = obj.p[i][j];
				}
			}
		}

		return *this;
	}

	// сложение матриц
	matrix operator + (const matrix &obj) 
	{
		matrix temp(N, M);
		if (N == obj.N) { // возможно сложение, если матрицы одинакового порядка
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					temp.p[i][j] = p[i][j] + obj.p[i][j];
				}
			}
		}

		return temp;
	}

	// сложение на число
	matrix& operator += (int a)
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				p[i][j] += a;
			}
		}

		return *this;
	}

	// умножение матриц
	matrix operator * (const matrix &obj) 
	{
		matrix temp(N, M);
		// возможно умножение, если матрицы согласованы, если матрицы одинакового порядка
		if (N == obj.N) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					temp.p[i][j] = p[i][j] * obj.p[j][i];
				}
			}
		}

		return temp;
	}

	// умножение на число
	matrix& operator *= (int a) 
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				p[i][j] *= a;
			}
		}

		return *this;
	}

	// оператор индексирования
	int &operator() (int iN, int iM)
	{

		return p[iN][iM];
	}

	void fillMatrica()
	{
		srand(100);
		//srand(time(NULL));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				p[i][j] = rand() % 10;
			}
		}
	}

	void showMatrica()
	{
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cout << p[i][j] << "\t";
			}
			cout << "\n";
		}
		cout << "\n";
	}

	void setValue(int iN, int iM, int value) 
	{
		if ((N > iN) && (M > iM)) {
			p[iN][iM] = value;
		}
	}

	int getValue(int iN, int iM) 
	{
		if ((N > iN) && (M > iM)) {
			return p[iN][iM]; 
		}

		return p[N-1][M-1]; 
	}

	void transponirovaniye()
	{
		matrix temp(N, M);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				temp.p[i][j] = p[j][i]; 
			}
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				p[i][j] = temp.p[i][j]; 
			}
		}
	}

	~matrix()
	{
		if (N) {
			for (int i = 0; i < N; ++i) {
				delete[]p[i];
			}
			delete[]p;
		}
	}

};


int main() 
{
	matrix m1(5, 5);
	m1.showMatrica();

	matrix m2 = m1;
	m2.showMatrica();

	matrix m3(6, 6);
	m3.showMatrica();

	m2 = m3;
	m2.showMatrica();

	m2.setValue(5, 2, 10); 
	m2.showMatrica();
	int value = m2.getValue(5, 2); 

	m2(3,3) = 40;
	m2.showMatrica();

	m2.transponirovaniye();
	m2.showMatrica();
	m3.showMatrica();

	m1 = m2 + m3;
	m1.showMatrica();

	m1 += 3;
	m1.showMatrica();

	m1 = m2 * m3;
	m1.showMatrica();

	m1 *= 2;
	m1.showMatrica();

	return 0;
}