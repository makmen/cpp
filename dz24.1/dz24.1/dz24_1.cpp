#include <iostream>
#include <time.h>
using namespace std;
// время едино, не будем плодить более одного класса
class watch {

	static watch*ptr;
	int hour;
	int minute;
	int second;

	watch()
	{
		time_t result = time(nullptr);
		setDateFromUnixTime(result);
	}

public:

	void setDateFromUnixTime(time_t result)
	{
		struct tm * timeinfo;
		timeinfo = localtime ( &result );
		hour = timeinfo->tm_hour;
		minute = timeinfo->tm_min;
		second = timeinfo->tm_sec;
	}

	static watch * getReference() 
	{
		return ptr;
	}

	void getTime()
	{
		correctTime(hour);
		cout << ":";
		correctTime(minute);
		cout << ":";
		correctTime(second);
		cout << "\n";
	}

	void setTime(int _hour, int _minute, int _second) 
	{
		if (checkTime(_hour, _minute,_second)) {
			hour = _hour;
			minute = _minute;
			second = _second;
		} else { // берем текущую дату
			time_t result = time(nullptr);
			setDateFromUnixTime(result);
		}
	}

	void add(int sec) 
	{
		time_t result = getUnixTime(hour, minute, second);
		result += sec;
		setDateFromUnixTime(result);
	}

	void sub(int sec) 
	{
		time_t result = getUnixTime(hour, minute, second);
		result -= sec;
		setDateFromUnixTime(result);
	}

	void convertToAmerica() 
	{
		char buffer [80];
		time_t result = getUnixTime(hour, minute, second);
		struct tm * timeinfo;
		timeinfo = localtime(&result);	
		strftime(buffer,80,"it's %I:%M %p",timeinfo);
		cout << buffer << "\n";
	}

	bool checkTime(int hour, int minute, int second)
	{
		bool flag = false;
		if (hour >= 0 && hour < 24) {
			flag = true;
		} else {
			return false;
		}
		if (minute >= 0 && minute < 60) {
			flag = true;
		} else {
			return false;
		}
		if (second >= 0 && second < 60) {
			flag = true;
		} else {
			return false;
		}

		return flag;
	}

	time_t getUnixTime(int _hour, int _minute, int _second)
	{
		struct tm * timeinfo;
		time_t result = time(nullptr);
		timeinfo = localtime ( &result );
		timeinfo->tm_hour = _hour;
		timeinfo->tm_min = _minute;
		timeinfo->tm_sec = _second;

		return mktime ( timeinfo );
	}

	void correctTime(int param) 
	{
		int first = param / 10;
		if (!first) {
			cout << 0;
		}
		cout << param;
	}

};

watch * watch::ptr = new watch(); 

int main () {
	watch*p = watch::getReference(); 
	p->getTime();
	p->setTime(15,10,58);
	p->getTime();
	p->add(10);
	p->getTime();
	p->sub(10);
	p->getTime();
	p->convertToAmerica();

	return 0;
}