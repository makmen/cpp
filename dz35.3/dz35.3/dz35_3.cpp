#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct vectorStudent
{
	string name;
	string lastName;
	int cource;
};

class student {
	string name;
	string lastName;
	int cource;
public:
	student(vector<vectorStudent> &ivector)
	{
		enterDataString(1);
		enterDataString(2);
		cout << "Введите курс: ";
		cource = isType<int>();
		addInVector(ivector);
	}

	student(string name_, string lastName_, int cource_, vector<vectorStudent> &ivector) : name(name_), lastName(lastName_), cource(cource_)
	{
		addInVector(ivector);
	}

	void addInVector(vector<vectorStudent> &ivector)
	{
		int i = ivector.size();
		ivector.resize(ivector.size() + 1);
		ivector[i].name = name;
		ivector[i].lastName = lastName;
		ivector[i].cource = cource;
	}

	void addIntToString(string &str) {
		char *temp = new char[10];
		_itoa_s(cource, temp, 10, 10);
		str.append(temp);

		delete temp;
	}

	void enterDataString(int i)
	{
		string buffer;
		int lengthBuffer;
		int limit = 50;
		while (true) {
			cout << "Введите ";
			switch (i) {
			case 1:
				cout << "имя: ";
				break;
			case 2:
				cout << "фамилию: ";
				break;
			}
			cin >> buffer;
			if (cin.good()) {
				lengthBuffer = buffer.length();
				if (limit > lengthBuffer) {
					cin.ignore(lengthBuffer, '\n');
					if (i == 1) {
						name = buffer;
					}
					else if (i == 2) {
						lastName = buffer;
					}
					else {

					}
					break;
				}
			}
			cin.clear();
			cin.ignore(lengthBuffer, '\n');
			cout << "Неверно введены данные, ограничение по размену до" << limit << " символов" << endl;
		}
	}

	template <typename T>
	static T isType() {
		T i;
		while (true) {
			cin >> i;
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cout << "Некорректные данные." << endl;
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}

	void show()
	{
		cout << endl << "Name: " << name << endl;
		cout << "Last name: " << lastName << endl;
		cout << "Course: " << cource << endl;
	}
};

void printVector(vector<vectorStudent> &);
bool sortByName(const vectorStudent &, const vectorStudent &);
bool sortByLastName(const vectorStudent &, const vectorStudent &);
bool sortByCource(const vectorStudent &, const vectorStudent &);

int main() {
	setlocale(LC_CTYPE, "Russian");
	vector<vectorStudent> st;
	student st1("Lima", "Borov", 1, st);
	student st2("Roma", "Belov", 1, st);
	student st3("Kili", "Varava", 2, st);
	student st4("Pers", "Gromov", 4, st);
	student st5("Vasya", "Baronov", 3, st);
	student st6("Nick", "Parter", 3, st);
	student st7("Lom", "Drinov", 2, st);
	//st1.show();
	cout << "Not sort" << endl;
	printVector(st);

	cout << "Sort by name:" << endl;
	sort(st.begin(), st.end(), sortByName);
	printVector(st);

	cout << "Sort by lastName:" << endl;
	sort(st.begin(), st.end(), sortByLastName);
	printVector(st);

	cout << "Sort by cource:" << endl;
	sort(st.begin(), st.end(), sortByCource);
	printVector(st);

	return 0;
}

void printVector(vector<vectorStudent> &vect)
{
	for (vector<vectorStudent>::size_type i = 0, count = vect.size(); i != count; ++i) {
		cout << vect[i].name << "\t" << vect[i].lastName << "\t" << vect[i].cource << endl;
	}
	cout << endl;
}

bool sortByName(const vectorStudent &lhs, const vectorStudent &rhs)
{
	return lhs.name < rhs.name;
}

bool sortByLastName(const vectorStudent &lhs, const vectorStudent &rhs)
{
	return lhs.lastName < rhs.lastName;
}

bool sortByCource(const vectorStudent &lhs, const vectorStudent &rhs)
{
	return lhs.cource < rhs.cource;
}
