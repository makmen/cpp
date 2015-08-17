#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>

using namespace std;
void addIntToString(string &, int);

int main() {
	int row = 9;
	int col = 8;
	vector<vector<string>> imatrix(row);
	string temp;
	for (int i = 0, k = 2; i < row; ++i)
	{
		imatrix[i].resize(col);
		for (int j = 0; j < col; ++j) {
			addIntToString(temp, k);
			temp.append(" * ");
			addIntToString(temp, i + 1);
			temp.append(" = ");
			addIntToString(temp, (k++) * (i + 1));
			imatrix[i][j] = temp;
			temp = "";
		}
		k = 2;
	}
	for (int i = 0; i < row; i++) {
		copy(
			imatrix[i].begin(), 
			imatrix[i].end(), 
			ostream_iterator<string>(cout, "\t"));
		cout << endl << endl;
	}

	return 0;
}

void addIntToString(string &str, int num) {
	char *temp = new char[10];
	_itoa_s(num, temp, 10, 10);
	str.append(temp);

	delete temp;
}
