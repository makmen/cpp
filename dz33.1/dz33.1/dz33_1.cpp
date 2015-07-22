#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class converter {
public:
	void calculation(string str) {
		if (str.empty()) {
			throw 0;
		}
		double maxInt = 2147483648;
		double minInt = -2147483647;
		double limit = 0;
		int temp;
		bool isNegotive = false;
		for (int i = 0, count = str.length(); i < count; ++i) {
			temp = CharToInt(str[i]);
			if (!i && count > 1 && (int)str[i] == 45) {// знак минус
				isNegotive = true;
				continue;
			}
			if (temp < 0 || temp > 9) {
				throw 1;
			}
			if (isNegotive) {
				limit -= temp * pow(10, count - i - 1);
			}
			else {
				limit += temp * pow(10, count - i - 1);
			}
			if (!(limit < maxInt && limit > minInt)) { // не лежит в пределах int
				throw 2;
			}
		}
		cout << "Number " << (int)limit << " converted successfully" << endl;
	}

	int CharToInt(char c) {
		return c - '0';
	}
};

int main() {
	string str = "-2147483646";
	converter cnv;
	try {
		cnv.calculation(str);
	}
	catch (int error) {
		switch (error) {
		case 0:
			cout << "The string is empty" << endl;
			break;
		case 1:
			cout << "The string \"" << str << "\" contains not numeric symbols" << endl;
			break;
		case 2:
			cout << str << endl;
			cout << "Out of the range determined by the type int" << endl;
			break;
		}
	}

	return 0;
}