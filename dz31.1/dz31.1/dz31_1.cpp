#include <iostream>
#include <string>
using namespace std;

class student {
protected:
	string name;
	string lastname;
	string recordBook;
	int old; 
	double raiting;
public:
	student(const string&name_, const string&lastname_, const string&recordBook_, const int&old_, const double&raiting_)
	{
		name = name_;
		lastname = lastname_;
		recordBook = recordBook_;
		old = old_;
		raiting = raiting_;
	}

	void showStudent()
	{
		cout << name << endl;
		cout << lastname << endl;
		cout << recordBook << endl;
		cout << old << endl;
		cout << raiting << endl;
	}
};

class Aspirant : student {
	int counterScience; // количество научных публикаций
public:
	Aspirant(string name_, string lastname_, string recordBook_, int old_, double raiting_) : student(name_, lastname_, recordBook_, old_, raiting_), counterScience(0)
	{

	}

	Aspirant& operator ++ ()
	{
		++counterScience;

		return *this;
	}

	Aspirant& operator += (int a)
	{
		counterScience += a;

		return *this;
	}

	void showAspirant()
	{
		showStudent();
		cout << counterScience << endl;
	}

};

int main() {
	Aspirant s1("Andrew", "Morozov", "R4549", 22, 9.2);
	s1 += 5;
	++s1;
	s1.showAspirant();

	return 0;
}