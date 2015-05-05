#include <iostream>
#include <string.h> 
using namespace std;

class String{
	char *str;

public:

	// ������ ������� 80
	String() {
		int n = 80;
		this->str = new char[n + 1];
	}

	// ������ ���������� �� ������������
	String(char *str) {
		this->str = new char[strlen(str) + 1];
		strcpy(this->str, str);
	}

	// ������ ������������� �������
	String(int n) {
		if (n > 0) {
			this->str = new char[n + 1];
		}
	}

	// ����������� �����������
	String(const String &obj) {
		this->str = new char[strlen(obj.str) + 1];
		strcpy(this->str, obj.str);
	}

	void editString(char *str) {
		strcpy(this->str, str);
	}

	void enterString() {
		char temp[255];
		gets(temp);
		this->str = new char[strlen(temp) + 1];
		strcpy(this->str, temp);
	}

	void show() {
		cout << str << "\n";
	}

	~String() {
		delete[]str;
	}


};

int main() {
	String str("reti834");
	str.show();

	String str1 = str;
	str1.show();

	String str2;
	str2.enterString();
	str2.show();

	String str3(5);
	str3.editString("kow");
	str3.show();

	return 0;
}
