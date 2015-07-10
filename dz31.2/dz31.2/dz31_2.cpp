#include <iostream>
#include <string>
using namespace std;
#define MAX 50 // максимальное количество записей

class passport {
protected:
	string name;
	string lastname;
	string number;
	string identifier;
	string countryCode;
	char sex;
public:
	passport(const string&name_, const string&lastname_, const string&number_, const string&identifier_, const string&countryCode_, const char&sex_)
	{
		name = name_;
		lastname = lastname_;
		number = number_;
		identifier = identifier_;
		countryCode = countryCode_;
		sex = sex_;
	}

	void showPassport()
	{
		cout << name << endl;
		cout << lastname << endl;
		if (number != "")
			cout << number << endl;
		cout << identifier << endl;
		cout << countryCode << endl;
		cout << sex << endl;
	}

};

struct visa {
	string num;
	string dateCreated;
	string name;
	string lastname;
	string type;

	visa(string num_, string dateCreated_, string name_, string lastname_, string type_) : num(num_), dateCreated(dateCreated_),  name(name_), lastname(lastname_), type(type_)
	{

	}
};

class ForeignPassport : public passport {
	int counterVisa;
	visa *ptr[MAX];		// максимальное количество виз для иностранца
	string numberForeignPassport;
public:
	ForeignPassport(string name_, string lastname_, string number_, string identifier_, string countryCode_, char sex_, string numberForeignPassport_) : passport(name_, lastname_, number_, identifier_, countryCode_, sex_), 
		numberForeignPassport(numberForeignPassport_), counterVisa(0)
	{

	}

	void addViza(string num_, string dateCreated_, string name_, string lastname_, string type_)
	{
		ptr[counterVisa++] = new visa(num_, dateCreated_, name_, lastname_, type_);
	}

	void showVisa() {
		if (counterVisa) {
			for (int i = 0; i < counterVisa; ++i) {
				cout << "visa " << i + 1 << endl;
				cout << (ptr[i])->num << endl;
				cout << (ptr[i])->dateCreated << endl;
				cout << (ptr[i])->name << endl;
				cout << (ptr[i])->lastname << endl;
				cout << (ptr[i])->type << endl;
				cout << endl;
			}
		}
	}

	void showForeignPassport()
	{
		cout << numberForeignPassport << endl << endl;
	}

	~ForeignPassport()
	{
		if (counterVisa) {
			for (int i = 0; i < counterVisa; ++i) {
				delete ptr[i];
			}
		}
	}
};


int main() {
	ForeignPassport fp1("Pavlik", "Morozov", "", "3257412563AO25", "RUS", 'M', "d100as433");
	fp1.showPassport();
	fp1.showForeignPassport();
	fp1.addViza("125et", "25-06-2015", "Pavlik", "Morozov", "MUL");
	fp1.addViza("365", "25-06-2015", "Pavlik", "Morozov", "MUL");
	fp1.showVisa();
	passport ps1("Egor", "Linder", "MP254512", "38545w563AO25", "BLR", 'M');
	ps1.showPassport();
	ForeignPassport fp2("Lena", "Begemot", "", "9595AE345T5", "RUS", 'W', "95934eer");
	fp2.showPassport();
	fp2.showForeignPassport();
	
	return 0;
}