#include <iostream>
#include <vector>
#include <iterator> // заголовочный файл итераторов
#include <stdlib.h>
#include <time.h>
using namespace std;
void showVector(vector<int> &);
void fillVector(int, vector<int> &);

int main() {
	vector<int> vect;
	srand(time(NULL));
	int size = 10;
	fillVector(size, vect);
	showVector(vect);

	return 0;
}

void fillVector(int size, vector<int> &vect) {
	vect.resize(size);
	for (int i = 0, count = vect.size(); i < count; ++i) {
		vect[i] = rand() % 10;
		vect[i] = vect[i] * vect[i];
	}
}

void showVector(vector<int> &vect)
{
	copy(vect.begin(), vect.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

