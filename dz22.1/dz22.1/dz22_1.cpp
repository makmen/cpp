#include <iostream>
#include <time.h>
#include <ctime>
using namespace std;

const int secondsPerDay = 86400;

class date {
	int day;
	int month;
	int year;

public:

	date()
	{	// берем текущую дату
		time_t result = time(nullptr);
		setDateFromUnixTime(result);
	}

	date(int day, int month, int year) 
	{
		struct tm * timeinfo;
		time_t result = time(nullptr);
		timeinfo = localtime ( &result );
		timeinfo->tm_year = year - 1900;
		timeinfo->tm_mon = month - 1;
		timeinfo->tm_mday = day;
		result = mktime ( timeinfo );
		if (!(timeinfo->tm_mday == day && timeinfo->tm_mon == month - 1 && timeinfo->tm_year == year - 1900 )) {
			// дата неправильная - берем текущую
			result = time(nullptr);
		}
		setDateFromUnixTime(result);
	}

	date(const date &obj) 
	{
		this->day = obj.day;
		this->month =  obj.month;
		this->year = obj.year;
	}

	date& operator = (const date &obj) 
	{
		if (this != &obj) { 
			day = obj.day;
			month =  obj.month;
			year = obj.year;
		}

		return *this;
	}

	date& operator+= (int j) 
	{
		time_t result = time(nullptr);
		result = getUnixTime(day, month, year);
		result += j * secondsPerDay; // кол-во секунд в сутках 86400
		setDateFromUnixTime(result);

		return *this;
	}

	void setDateFromUnixTime(time_t result)
	{
		struct tm * timeinfo;
		timeinfo = localtime ( &result );
		day = timeinfo->tm_mday;
		month = timeinfo->tm_mon + 1;
		year = 1900 + timeinfo->tm_year;
	}

	time_t getUnixTime(int day, int month, int year)
	{
		struct tm * timeinfo;
		time_t result = time(nullptr);
		timeinfo = localtime ( &result );
		timeinfo->tm_year = year - 1900;
		timeinfo->tm_mon = month - 1;
		timeinfo->tm_mday = day;

		return mktime ( timeinfo );
	}

	int operator- (const date &obj) 
	{
		int ret;
		time_t result = time(nullptr);
		result = getUnixTime(day, month, year);
		time_t objResult = time(nullptr);
		objResult = getUnixTime(obj.day, obj.month, obj.year);
		if (result >= objResult) {
			// вычитаем 
			ret = result - objResult;
			// высчитываем дни
			ret /= secondsPerDay; 
		} else { // вычитание не возможно
			ret = -1;
		}

		return ret;
	}

	void show()  
	{
		correctDate(1);
		correctDate(2);
		cout << year << "\n";
	}

	// отображение даты с ноликами 01, 02, 11. 
	void correctDate(int param) 
	{
		int first = (param == 1) ? day / 10 : month / 10;
		if (!first) {
			cout << 0;
		}
		first = (param == 1) ? day: month;
		cout << first << ":";
	}

};

int main() {
	date obj1;
	obj1.show();

	obj1 += 10;
	obj1.show();

	date obj2(01, 06, 2015);
	obj2.show();

	date obj3 = obj1;
	obj3.show();

	int c = obj3 - obj2;
	if (c >= 0) {
		cout << c << "\n";
	} else {
		cout << "Error. Subtraction is impossible" << "\n";
	}

	return 0;
}
