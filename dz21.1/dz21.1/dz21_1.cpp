#include <iostream>
#include <string.h> 
using namespace std;

class person {
	char *name;
	unsigned short age;
	char pol;
	char *telefon;

public:

	person(char *name, unsigned short age, char pol, char *telefon) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->age = age;
		this->pol = pol;
		this->telefon = new char[strlen(telefon) + 1];
		strcpy(this->telefon, telefon);
	}

	person(const person &obj) {
		this->name = new char[strlen(obj.name) + 1];
		strcpy(this->name, obj.name);
		this->age = obj.age;
		this->pol = obj.pol;
		this->telefon = new char[strlen(obj.telefon) + 1];
		strcpy(this->telefon, obj.telefon);
	}

	void editName(char *name) {
		strcpy(this->name, name);
	}

	void editAge(unsigned short age) {
		this->age = age;
	}

	void editPol(char pol) {
		this->pol = pol;
	}

	void editTelefon(char *telefon) {
		strcpy(this->telefon, telefon);
	}

	void print() {
		cout << "name:\t\t" << this->name << "\n";
		cout << "age:\t\t" << this->age << "\n";
		cout << "pol:\t\t" << this->pol << "\n";
		cout << "telefon:\t" << this->telefon << "\n\n";
	}

	~person() {
		delete[] name;
		delete[] telefon;
	}

};


int main() {
	person Makas("Makas", 38, 'M', "+375(29)2678594");
	person Baraban = Makas;
	Makas.editName("Lima");
	Makas.editTelefon("+375495958385");
	Makas.editAge(25);
	Makas.editPol('W');
	Makas.print();
	Baraban.print();

	return 0;
}
