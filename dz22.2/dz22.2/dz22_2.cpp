#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class stringer {

	char *str;
	int size;

public:

	stringer() 
	{
		size = 80;
		str = new char[size + 1];
		randomString();
	}

	stringer(char *str) 
	{
		size =  strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}

	stringer(int size) 
	{
		this->size = size;  
		if (size <= 0) {
			this->size = 80;  
		}
		this->str = new char[this->size + 1];
		randomString();
	}

	// конструктор копирования
	stringer(const stringer &obj) 
	{
		str = new char[strlen(obj.str) + 1];
		size = strlen(obj.str);
		strcpy(str, obj.str);
	}

	// оператор присваивания
	stringer& operator = (const stringer &obj) {
		if (this != &obj) {
			str = new char[strlen(obj.str) + 1];
			size = strlen(obj.str);
			strcpy(str, obj.str);
		}

		return *this;
	}

	// оператор индексирования
	char & operator [] (int index) 
	{
		if (index >= 0 && index < size) {
			return str[index];
		} else 
			return str[size - 1];
	}

	// оператор +=
	stringer& operator += (const stringer &obj) 
	{
		char *temp;
		temp = new char[size + strlen(obj.str) + 1];
		strcpy(temp, str);
		strcat(temp, obj.str);
		size = size + strlen(obj.str);
		delete[]str;
		str = temp;

		return *this;
	}

	stringer operator * (const stringer &obj) 
	{
		int i, j, k = 0; 
		stringer temp(size + 1);
		for (i = 0; i < size; ++i) {
			for (j = 0; j < obj.size; ++j) {
				if (str[i] == obj.str[j]) {
					temp.str[k] = str[i]; 
					++k;
				}
			}
		}
		temp.str[k] = '\0';

		return temp;
	}

	// заполняем строку случайными символами
	void randomString() 
	{
		int len = 62;
		int i, j;
		char *chars, *temp;
		chars = new char[len];		//все нужные нам символы 0-9, a-z, A-Z
		for(i = 48, j = 0; i < 58; ++i, ++j) {
			chars[j] = (char) i; 
		}
		for(i = 65; i < 91; ++i, ++j) {
			chars[j] = (char) i;
		}
		for(i = 97; i < 123; ++i, ++j) {
			chars[j] = (char) i;
		}
		// формируем строчку размером size - 1
		temp = new char[size + 1];
		srand(time(NULL));
		for(i = 0; i < size; ++i) {
			j = rand() % len;
			temp[i] = chars[j]; 
		}
		temp[i] = '\0';
		strcpy(str, temp);
		delete []temp;
		delete []chars;
	}

	void show() 
	{
		cout << str << "\n";
	}

	~stringer() 
	{
		delete []str;
	}

};

int main() {
	stringer str1;
	str1 = "de34r5";
	str1.show();

	stringer str2("line df");
	str2.show();

	stringer str3 = 3;
	str3.show();

	stringer str4 = str3;
	str4 = str1;

	str4 += "fdfd";
	str4.show();
	str2.show();

	str3 = str4 * str2;
	str3.show();

	return 0;
}