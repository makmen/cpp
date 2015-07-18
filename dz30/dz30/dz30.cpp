#include <iostream>
#include <fstream>
#include "windows.h"
#include <io.h>
using namespace std;

int getInt();
void russianMessage(char *, bool);

class handbook {
	char *name = "fhandbook.txt";
	int countRecords = 0;
	int limit = 20; // для всех полей ограничение по размеру
public:
	handbook() {
		
	}

	void addRecord() {
		char *nameCompany = new char[limit];
		char *owner = new char[limit];
		char *phone = new char[limit];
		char *address = new char[limit];
		char *typeActivity = new char[limit];
		enterData(nameCompany, 1);
		enterData(owner,  2);
		enterData(phone,  3);
		enterData(address,  4);
		enterData(typeActivity,  5);
		ofstream outfile(getNameFile(), ios::app);
		outfile << nameCompany << "\t"
			<< owner << "\t"
			<< phone << "\t"
			<< address << "\t"
			<< typeActivity << "\n";
		russianMessage("Запись добавлена", true);
		delete[]nameCompany;
		delete[]owner;
		delete[]phone;
		delete[]address;
		delete[]typeActivity;
	}

	void enterData(char data[], int param) {
		char *buffer = new char[255];
		char output[100];
		int lengthBuffer;
		switch (param) {
		case 1:
			strcpy(output, " название организации: ");
			break;
		case 2:
			strcpy(output, " владельца: ");
			break;
		case 3:
			strcpy(output, " номер телефона: ");
			break;
		case 4:
			strcpy(output, " адрес: ");
			break;
		default:
			strcpy(output, " род деятельности организации: ");
		}
		while (true) {
			russianMessage("Введите", false);
			russianMessage(output, false);
			cin >> buffer;
			if (cin.good()) {
				lengthBuffer = strlen(buffer);
				if (limit > lengthBuffer) {
					cin.ignore(lengthBuffer, '\n');
					strcpy(data, buffer);
					break;
				}
			}
			cin.clear();
			cin.ignore(lengthBuffer, '\n');
			russianMessage("Неверно введены данные, ограничение по размену до ", false);
			cout << limit;
			russianMessage(" символов", true);
		}
		delete[]buffer;
	}

	void showRecords() {
		if (!existsFile()) {
			russianMessage("Нет записей в справочнике", true);
			return;
		}
		int MAX = limit * 6;
		char *buffer = new char[MAX];
		int i = 0;
		ifstream infile(getNameFile());
		russianMessage("(Название фирмы, ", false);
		russianMessage("Владелец, ", false);
		russianMessage("Телефон, ", false);
		russianMessage("Адрес, ", false);
		russianMessage("Род деятельности)", true);
		while (!infile.eof()) 
		{
			infile.getline(buffer, MAX);
			if (strlen(buffer) > 0) 
				cout << ++i << ". " << buffer << endl;
		}
		delete[]buffer;
	}

	void searchBy(int param) {
		if (!existsFile()) {
			russianMessage("Нет записей в справочнике", true);
			return;
		}
		int MAX = limit * 6;
		char *buffer = new char[MAX];
		char *tempBuffer = new char[MAX];
		char *search = new char[limit];
		enterData(search, param);
		ifstream infile(getNameFile());
		bool flag = false;
		int k = 0;
		while (!infile.eof())
		{
			if (flag)
				break;
			infile.getline(buffer, MAX);
			if (strlen(buffer) > 0) { // что то есть
				strcpy(tempBuffer, buffer);
				char *pch = strtok(buffer, "\t"); 
				int i = 0;
				while (pch != NULL)
				{
					if ((i + 1) == param) { // то что нужно
						if (strstr(pch, search)) {
							russianMessage("Результат поиска: ", false);
							cout << search << endl;
							russianMessage("Запись найдена", true);
							cout << ++k << "." << tempBuffer << endl;
							flag = true;
							break;
						} 
					}
					++i;
					pch = strtok(NULL, "\t");
				}
			}
			++k;
		}
		if (!flag) {
			russianMessage("Результат поиска: ", false);
			cout << search << endl;
			russianMessage("Запись отсутствует", true);
		}
		delete[]buffer;
		delete[]tempBuffer;
		delete[]search;
	}

	bool existsFile() {
		bool ret = false;
		_finddata_t *fileinfo = new _finddata_t;
		long result = _findfirst(getNameFile(), fileinfo);
		if (result != -1) {
			ret = true;
		}
		_findclose(result);
		delete fileinfo;

		return ret;
	}

	char *getNameFile() {

		return name;
	}

	~handbook() {

	}

};

int main() {
	russianMessage("Программа СПРАВОЧНИК", true);
	russianMessage("Выбирете действие", true);
	russianMessage("1. Поиск по названию организации", true);
	russianMessage("2. Поиск по владельцу ", true);
	russianMessage("3. Поиск по номеру телефона ", true);
	russianMessage("4. Поиск по роду деятельности ", true);
	russianMessage("5. Показ всех записей ", true);
	russianMessage("6. Добавление новой записи ", true);
	russianMessage("7. Выход ", true);
	int menu;
	handbook hd;
	while (true) {
		menu = getInt();
		if (menu == 7) {
			break;
		}
		switch (menu) {
		case 1:
			russianMessage("Поиск по названию организации", true);
			hd.searchBy(menu);
			break;
		case 2:
			russianMessage("Поиск по владельцу ", true);
			hd.searchBy(menu);
			break;
		case 3:
			russianMessage("Поиск по номеру телефона ", true);
			hd.searchBy(menu);
			break;
		case 4:
			russianMessage("Поиск по роду деятельности ", true);
			hd.searchBy(menu + 1);
			break;
		case 5:
			russianMessage("Выводим список всех записей", true);
			hd.showRecords();
			break;
		case 6:
			russianMessage("Добавляем новую запись", true);
			hd.addRecord();
			break;
		}
	}

	return 0;
}

int getInt() {
	int i;
	while (true) {
		cin >> i;
		if (cin.good()) {
			cin.ignore(10, '\n');
			if (i > 0 && i < 8)  {
				break;
			}
		}
		russianMessage("Некорректные данные. Введите числа: 1, 2, 3, 4, 5, 6, 7", true);
		cin.clear();
		cin.ignore(10, '\n');
	}

	return i;
}

void russianMessage(char *message, bool enter) {
	char rmessage[256];
	CharToOem(message, rmessage);
	cout << rmessage;
	if (enter)
		cout << endl;
}