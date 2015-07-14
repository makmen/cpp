#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
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

	void setDateFromUnixTime(time_t result)
	{
		struct tm * timeinfo;
		timeinfo = localtime(&result);
		hour = timeinfo->tm_hour;
		minute = timeinfo->tm_min;
		second = timeinfo->tm_sec;
	}

	time_t getUnixTime()
	{
		struct tm * timeinfo;
		time_t result = time(nullptr);
		timeinfo = localtime(&result);
		timeinfo->tm_hour = hour;
		timeinfo->tm_min = minute;
		timeinfo->tm_sec = second;

		return mktime(timeinfo);
	}

	void getTime()
	{
		correctTime(hour);
		cout << ":";
		correctTime(minute);
		cout << ":";
		correctTime(second);
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

class passenger {
	watch *timeArrived = nullptr;	// время прибытия на остановку
	watch *timeGone = nullptr;		// время когда уехал пассажир
public:

	passenger() {
		timeArrived = new watch;
	}

	void gone() {
		timeGone = new watch;
	}

	watch *getTimeArrived()
	{
		return timeArrived;
	}

	watch *getTimeGone()
	{
		return timeGone;
	}
};

class marshrutka {
	watch *timeArrived = nullptr;	// время прибытия на остановку
	watch *timeGone = nullptr;		// время когда уехала 
	int freePlace;					// количество свободных мест
	int stop = 4;					// маршрутка стоит 4 секунды
public:
	marshrutka()
	{
		srand(time(NULL));
		freePlace = rand() % 12 + 3;
		timeArrived = new watch;
	}

	int getStop()
	{
		return stop;
	}

	int getFreePlace()
	{
		return freePlace;
	}

	watch *getTimeArrived()
	{
		return timeArrived;
	}

	watch *getTimeGone()
	{
		return timeGone;
	}

	void gone()
	{
		timeGone = new watch;
		time_t result = timeArrived->getUnixTime() + stop;
		timeGone->setDateFromUnixTime(result);
	}

	void showMarshrutka()
	{
		timeArrived->getTime();
		cout << endl;
		timeGone->getTime();
		cout << endl;
	}
};

// класс остановка
class stay {
	passenger **ptrPassenger = nullptr;		// массив указателей на объекты passenger
	marshrutka **ptrMarshrutka = nullptr;	// массив указателей на объекты Marshrutka
	int countPassenger = 0;					// количество пассажиров которые стоят на остановке
	int allPassenger = 0;					// количество всех пассажиров
	int allMarshrutka = 0;					// количество всех маршруток которые приехали
public:
	void addMarshrutka()
	{
		ptrMarshrutka = (marshrutka**)realloc(ptrMarshrutka, sizeof(marshrutka*)* (allMarshrutka + 1));
		ptrMarshrutka[allMarshrutka++] = new marshrutka;
		cout << "Marshrutka " << allMarshrutka << " arrived\t";
		ptrMarshrutka[allMarshrutka - 1]->getTimeArrived()->getTime();
		cout << endl;
	}

	int loading(int interval)
	{
		int countPass = ptrMarshrutka[allMarshrutka - 1]->getStop(); // сколько пассажиров нужно добавить пока стоит марштрутка?
		return countPass / interval;
	}

	void goneMarshrutka()
	{
		if (allMarshrutka) {
			int i = 0;
			while (i < allMarshrutka) {
				if (ptrMarshrutka[i++]->getTimeGone()) {
					continue;
				}
				cout << "Marshrutka " << i << " arrived\t";
				ptrMarshrutka[--i]->getTimeArrived()->getTime();
				ptrMarshrutka[i]->gone();
				// сажаем пассажиров
				int freePlace = ptrMarshrutka[i]->getFreePlace();
				while (countPassenger && freePlace) {
					delPassenger();
					--freePlace;
				}
				cout << "\t";
				ptrMarshrutka[i]->getTimeGone()->getTime();
				cout << endl;
				break;
			}
		}
	}

	void addPassenger()
	{
		ptrPassenger = (passenger**)realloc(ptrPassenger, sizeof(passenger*)* (allPassenger + 1));
		++countPassenger;
		ptrPassenger[allPassenger++] = new passenger;
		cout << "passenger " << allPassenger << " arrived\t";
		ptrPassenger[allPassenger - 1]->getTimeArrived()->getTime();
		cout << endl;
	}

	void delPassenger()
	{
		// удалять объект не будем лишь запишем timeGone
		if (countPassenger) {
			--countPassenger;
		}
		if (allPassenger) {
			int i = 0;
			while (i < allPassenger) {
				if (ptrPassenger[i++]->getTimeGone()) {
					continue;
				}
				ptrPassenger[--i]->gone();
				break;
			}
		}
	}

	void showMarshrutka()
	{
		if (allMarshrutka) {
			for (int i = 0; i < allMarshrutka; ++i) {
				cout << "Marshrutka " << i + 1 << " arrived\t";
				ptrMarshrutka[i]->getTimeArrived()->getTime();
				if (ptrMarshrutka[i]->getTimeGone()) {
					cout << "\tgone ";
					ptrMarshrutka[i]->getTimeGone()->getTime();
				}
				cout << endl;
			}
		}
		cout << allMarshrutka << endl;
	}

	void showPassenger()
	{
		cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		if (allPassenger) {
			for (int i = 0; i < allPassenger; ++i) {
				cout << "passenger " << i + 1 << " arrived\t";
				ptrPassenger[i]->getTimeArrived()->getTime();
				if (ptrPassenger[i]->getTimeGone()) {
					cout << "\tgone ";
					ptrPassenger[i]->getTimeGone()->getTime();
				}
				cout << endl;
			}
		}
		cout << countPassenger << endl;
	}

	void averageTime()
	{
		double average = 0;
		int summ = 0, j = 0;
		if (allPassenger) {
			for (int i = 0; i < allPassenger; ++i) {
				if (ptrPassenger[i]->getTimeGone()) {
					summ += ptrPassenger[i]->getTimeGone()->getUnixTime() - ptrPassenger[i]->getTimeArrived()->getUnixTime();
					++j;
				}
			}
			average = 1.0 * summ / j;
		}
		cout << "The average time of stay of the person at the bus stop: " << average << endl;
	}

};

// задержка на 1 секунду
void delayStep() {
	for (unsigned long t = 0; t < 500000000L; ++t);
}

int main() {
	int intervalMarshrutka = 10;		// интервал между маршрутками
	int intervalPassenger = 1;			// интервал между пассажирами
	int N = 5;							// не более N людей одновременно
	// сколько людей предет на остановку пока приедет маршрутка
	int interval = intervalMarshrutka / intervalPassenger;
	if (N == interval) {
		cout << "at the bus stop is no more people than " << N << endl;
	}
	else if (N < interval) {
		cout << "at the bus stop is more people than " << N << endl;
	}
	else {
		cout << "at the bus stop is more less than " << N << endl;
	}
	stay st;
	int k = 0, loading;
	while (true) {
		if (k++ == interval) {
			st.addMarshrutka();
			// погрузка
			loading = st.loading(intervalPassenger);
			while (loading--) {
				st.addPassenger();
				for (int i = 0; i < intervalPassenger; ++i)
					delayStep();
			}
			// маршрутка уезжает
			st.goneMarshrutka();
			st.showPassenger();
			k = 0;
			// определяем среднее времяпребывание человека на остановке
			st.averageTime();
			// system("pause"); 
		}
		st.addPassenger();
		for (int i = 0; i < intervalPassenger; ++i)
			delayStep();
	}

	return 0;
}
