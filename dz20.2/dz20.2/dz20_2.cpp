#include <iostream>
#include <string.h> 
using namespace std;

class student {
	char *grupa;
	char *name;
	char *lastName;
	char *secondName;
	char *telefon;
	char *adres;
	unsigned short age;
	double average;		// средний балл

public:

	student(char *name_, char *lastName_, char *secondName_, char *telefon_, char *adres_, unsigned short age_, double average_) {
		grupa = "P32014";
		name = new char[strlen(name_) + 1];
		strcpy(name, name_);
		lastName = new char[strlen(lastName_) + 1];
		strcpy(lastName, lastName_);
		secondName = new char[strlen(secondName_) + 1];
		strcpy(secondName, secondName_);
		telefon = new char[strlen(telefon_) + 1];
		strcpy(telefon, telefon_);
		adres = new char[strlen(adres_) + 1];
		strcpy(adres, adres_);
		age = age_;
		average = average_;
	}

	void showData() {
		cout << "grupa:\t\t" << grupa << "\n";
		cout << "name:\t\t" << name << "\n";
		cout << "lastName:\t" << lastName << "\n";
		cout << "secondName:\t" << secondName << "\n";
		cout << "telefon:\t" << telefon << "\n";
		cout << "adres:\t\t" << adres << "\n";
		cout << "age:\t\t" << age << "\n";
		cout << "average:\t" << average << "\n";
		cout << "\n";
	}

	~student() {
		delete[] name;
		delete[] lastName;
		delete[] secondName;
		delete[] telefon;
		delete[] adres;
	}

};

int main() {
	student Makas("Andrey", "Makas", "Kazimirovich", "+375(29)2647037", "Prytyckogo-16-2", 25, 9.2);
	Makas.showData();
	student Supranovich("Oleg", "Supranovich", "Andreyevich", "+375(29)2565221", "Gromova-19-95", 26, 8.1);
	Supranovich.showData();
	student Torov("Vasiliy", "Torov", "Bikolayevich", "+375(25)2984978", "odintsova-13-5-46", 24, 7.3);
	Supranovich.showData();

	return 0;
}