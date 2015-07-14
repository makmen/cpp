#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

class watch {
	int hour;
	int minute;
	int second;
public:
	watch()
	{
		time_t result = time(nullptr);
		setDateFromUnixTime(result);
	}

	void setTime()
	{
		time_t result = time(nullptr);
		setDateFromUnixTime(result);
	}

	void setDateFromUnixTime(time_t result)
	{
		struct tm * timeinfo;
		timeinfo = localtime(&result);
		hour = timeinfo->tm_hour;
		minute = timeinfo->tm_min;
		second = timeinfo->tm_sec;
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

	void correctTime(int param)
	{
		int first = param / 10;
		if (!first) {
			cout << 0;
		}
		cout << param;
	}
};

class klient {
	int priority;
	string name;
public:
	klient()
	{

	}

	klient(int priority_, string name_) : priority(priority_), name(name_)
	{

	}

	string getName()
	{
		return name;
	}

	int getPriority()
	{
		return priority;
	}

	void showKlient()
	{
		cout << priority << endl;
		cout << name << endl;
	}
};

class statistik {
	klient *ptrKlient = nullptr;
	watch *timePrint = nullptr;
public:
	statistik(klient *ptrKlient_) : ptrKlient(ptrKlient_)
	{
		timePrint = new watch;
	}

	klient *getKlient()
	{
		return ptrKlient;
	}

	watch *getTimePrint()
	{
		return timePrint;
	}
};

class printer {
	klient **ptr = nullptr;			// массив указателей на указатель на объект klient(клиенты в очереди)
	signed curSize = 0;				// количество клиетов в очереди
	statistik **ptrStat = nullptr;	// все данные о печати
	signed countPrint = 0;			// общее количество клиентов которые печатали
public:
	printer()
	{

	}

	void printDoc(klient *ptrkl)
	{
		ptr = (klient**)realloc(ptr, sizeof(klient*)* ++curSize);
		int pos = curSize - 1;
		// ставим просто в очередь, в соответствии с приоритетом (чем ниже curSize тем круче клиент)
		if (curSize == 1) {
			ptr[pos] = ptrkl;
			return;
		}
		int priority = ptrkl->getPriority();
		for (int i = 0; i < pos; ++i) {
			if (ptr[i]->getPriority() > priority) {
				for (int j = pos; j > i; --j) {
					ptr[j] = ptr[j - 1];
				}
				ptr[i] = ptrkl;
				return;
			}
		}
		ptr[pos] = ptrkl;
	}

	void print() // непосредственно печатаем докумерт, убираем клиента из очереди
	{
		if (curSize) {
			cout << "PRINT ... " << ptr[0]->getName() << endl;
			delayStep();
			ptrStat = (statistik**)realloc(ptrStat, sizeof(statistik*)* ++countPrint);
			int pos = countPrint - 1;
			ptrStat[pos] = new statistik(ptr[0]);
			for (int i = 0; i < curSize - 1; ++i) {
				ptr[i] = ptr[i + 1];
			}
			ptr = (klient**)realloc(ptr, sizeof(klient*)* --curSize);
		}
		else {
			cout << "the queue is empty" << endl;
		}
	}

	void show()
	{
		for (int i = 0; i < curSize; ++i) {
			cout << ptr[i]->getPriority() << "\t" << ptr[i]->getName() << "\t" << ptr[i] << endl;
		}
		cout << "curSize = " << curSize << endl;
	}

	void statistika()
	{
		cout << endl;
		cout << "Statistica: " << endl;
		for (int i = 0; i < countPrint; ++i) {
			cout << ptrStat[i]->getKlient()->getPriority() << "\t" << ptrStat[i]->getKlient()->getName() << "\t";
			ptrStat[i]->getTimePrint()->getTime();
		}
	}

	void delayStep() {
		for (unsigned long t = 0; t < 1000000000L; ++t);
	}
};

int main() {
	printer pr;
	klient kl1(5, "user 1");
	klient kl2(7, "user 2");
	klient kl3(10, "user 3");
	klient kl4(2, "user 4");

	cout << endl;
	pr.printDoc(&kl1);
	pr.printDoc(&kl2);
	pr.printDoc(&kl3);
	pr.printDoc(&kl4);
	pr.printDoc(&kl2);
	pr.printDoc(&kl1);
	pr.printDoc(&kl4);
	pr.show();
	cout << endl;
	pr.print();
	pr.print();
	pr.print();
	pr.print();
	pr.print();
	pr.show();
	pr.statistika();

	return 0;
}