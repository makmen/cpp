#include <iostream>
using namespace std;

class timer {
	unsigned short count;
	unsigned short countMax;

public:

	timer() {
		count = 0;
		countMax = 100;
	}

	unsigned short getCount() {

		return count;
	}

	void incrementCount() {
		count = (count == 100) ? 0 : ++count;
	}

	void decrementCount() {
		count = (!count) ? 100 : --count;
	}

	void setMax() {
		count = countMax;
	}

	void setMin() {
		count = 0;
	}

	~timer() {
		cout << "object deleted\n";
	}

};

int main() {
	timer tmr;
	unsigned short value;
	value = tmr.getCount();		// получаем значение count
	cout << value << "\n";
	tmr.decrementCount();		// уменьшаем на 1
	value = tmr.getCount();
	cout << value << "\n";
	tmr.incrementCount();		// увеличиваем на 1
	tmr.incrementCount();		// увеличиваем на 1
	tmr.incrementCount();		// увеличиваем на 1
	value = tmr.getCount();
	cout << value << "\n";
	tmr.setMax();				// устанавливаем в MAX
	value = tmr.getCount();
	cout << value << "\n";
	tmr.incrementCount();
	value = tmr.getCount();
	cout << value << "\n";
	tmr.incrementCount();
	value = tmr.getCount();
	cout << value << "\n";
	tmr.setMin();				// устанавливаем в MIN
	value = tmr.getCount();
	cout << value << "\n";

	return 0;
}