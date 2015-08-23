#include <iostream>
#include <string>
#include "windows.h"
#include <fstream>
#include <iostream>

using namespace std;

void russianMessage(char *, bool);

class numbers {
public:
	template <typename T>
	static T isType() {
		T i;
		while (true) {
			cin >> i;
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			russianMessage("������������ ������.", true);
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}

	static char isYesOrNo() {
		char i;
		while (true) {
			cin >> i;
			if (cin.good()) {
				cin.ignore(10, '\n');
				if (i == 'y' || i == 'n')  {
					break;
				}
			}
			russianMessage("������������ ������. ������� y/n.", true);
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}

	static signed isSignedType() {
		signed i;
		while (true) {
			cin >> i;
			if (cin.good()) {
				cin.ignore(10, '\n');
				if (i > 0)  {
					break;
				}
			}
			russianMessage("������������ ������.", true);
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}

	static int getIntRange() {
		int i;
		while (true) {
			cin >> i;
			if (cin.good()) {
				cin.ignore(10, '\n');
				if (i > 0 && i < 11)  {
					break;
				}
			}
			russianMessage("������������ ������. ������� �����: 1, 2, 3, 4, 5, 6, 7, 8, 9 or 10", true);
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}
};
struct nodePhone;

struct nodeLastName{
	string value;		// ������� 
	nodeLastName *left, *right, *parent;
	nodePhone *ptrPhone = nullptr;

	nodeLastName(string vl, nodeLastName *lft, nodeLastName *rght, nodeLastName *prnt) :
		value(vl), left(lft), right(rght), parent(prnt)
	{

	}

	~nodeLastName()
	{

	}
};

struct nodePhone{
	long value;		// ����� ��������
	nodePhone *left, *right, *parent;
	nodeLastName *ptrLastName = nullptr;

	nodePhone(int vl, nodePhone *lft, nodePhone *rght, nodePhone *prnt) : 
		value(vl), left(lft), right(rght), parent(prnt)
	{

	}

	~nodePhone()
	{

	}
};

template <class T>
class binaryTree {
	T *root = nullptr;
	char *dltype;		//��� � ������� ��������
public:

	binaryTree() = default;

	template <typename TT>
	T *addNode(TT val, T *currentParent)
	{
		if (!root) {
			dltype = (char *)typeid(val).name();
			root = new T(val, nullptr, nullptr, nullptr);
			return root;
		}
		T *prevElement = currentParent;
		if (currentParent->value > val) {
			prevElement = currentParent->left;
		}
		else if (currentParent->value < val) {
			prevElement = currentParent->right;
		}
		else { // ��������� ���������� ��������
			//currentParent->addTicket();
			//return nullptr;
			prevElement = currentParent->right;
		}
		if (prevElement) { // ������ ��� ��� 
			return addNode(val, prevElement);
		}
		else {
			T *newElement = new T(val, nullptr, nullptr, currentParent);
			if (currentParent->value > val) {
				currentParent->left = newElement;
			}
			else {
				currentParent->right = newElement;
			}
			return newElement;
		}
	}

	void deleteAllItems()
	{
		T *current = root;
		while (current) {
			if (current->left) {
				current = current->left;
			}
			else if (current->right)
			{
				current = current->right;
			}
			else {
				current = deleteNode(current);
			}
		}
		root = nullptr;
	}

	T *deleteNode(T *currentElement)
	{
		T *previous = currentElement->parent;
		if (!previous) {
			delete currentElement;
			return nullptr;
		}
		if (previous->left == currentElement) {
			previous->left = nullptr;
		}
		else {
			previous->right = nullptr;
		}
		delete currentElement;

		return previous;
	}

	void show(T *currentElement)
	{
		if (currentElement) {
			show(currentElement->left);
			if (!strcmp(dltype, "long")) {
				russianMessage("����� ��������: ", false);
			}
			else {
				russianMessage("�������: ", false);
			}
			cout << currentElement->value << endl;
			cout << endl;
			show(currentElement->right);
		}
	}

	T *showNumerPhone(T *currentElement, long num)
	{
		T *temp = nullptr;
		if (currentElement) {
			temp = showNumerPhone(currentElement->left, num);
			if (currentElement->value == num) {
				russianMessage("����� ��������: ", false);
				cout << currentElement->value << endl;
				russianMessage("�������: ", false);
				cout << currentElement->ptrLastName->value << endl;
				return currentElement;
			}
			if (currentElement != nullptr)
				temp = showNumerPhone(currentElement->right, num);
		}

		return temp;
	}

	T *showLastName(T *currentElement, string num)
	{
		T *temp = nullptr;
		if (currentElement) {
			temp = showLastName(currentElement->left, num);
			if (currentElement->value == num) {
				russianMessage("����� ��������: ", false);
				cout << currentElement->ptrPhone->value << endl;
				russianMessage("�������: ", false);
				cout << currentElement->value << endl;
				return currentElement;
			}
			if (!currentElement)
				temp = showLastName(currentElement->right, num);
		}
		return temp;
	}

	void infile(char *name, T *currentElement)
	{
		if (currentElement) {
			infile(name, currentElement->left);
			ofstream os(name, ios::binary | ios::app);
			os << currentElement->value << "\t"
				<< currentElement->ptrLastName->value <<"\r\n";
			os.close();
			infile(name, currentElement->right);
		}
	}

	T *getRoot()
	{
		return root;
	}

	~binaryTree()
	{
		deleteAllItems();
	}
};

class handbook {
	char *name = "fhandbook.dat";
public:
	handbook()
	{

	}

	void save(binaryTree <nodePhone>&treePhone)
	{
		ofstream os(name, ios::binary);
		os.write(reinterpret_cast<char*>(&treePhone), sizeof(treePhone));
		os.close();
		// treePhone.infile(name, treePhone.getRoot());
	}

	void load(binaryTree <nodePhone>&treePhone)
	{
		ifstream file(name, ios::binary);
		treePhone.show(treePhone.getRoot());
		treePhone.deleteAllItems();
		treePhone.show(treePhone.getRoot());
		file.read(reinterpret_cast<char*>(&treePhone), sizeof(treePhone));
		treePhone.show(treePhone.getRoot());
		cout << treePhone.getRoot() << endl;
	}

	char *getNameFile()
	{

		return name;
	}

	~handbook()
	{

	}
};


int main() {
	russianMessage("��������� ����������", true);
	russianMessage("�������� ��������", true);
	russianMessage("1. ���������� ����� ������", true);
	russianMessage("2. �������� ��������� �� ����", true);
	russianMessage("3. ����������� ������ �������� ", true);
	russianMessage("4. ����� ��������� �� ����������� ������", true);
	russianMessage("5. ����� ��������� �� �������", true);
	russianMessage("6. ���������� � ���������� ������� ��������� �� ��������� ��������� �������", true);
	russianMessage("7. ���������� � ���������� ������� ��������� �� ��������� ��������� �������", true);
	russianMessage("8. ���������� ���� � ����", true);
	russianMessage("9. �������� ���� �� �����", true);
	russianMessage("10. ����� ", true);
	int menu;
	long numerPhone;
	string lastName;
	binaryTree <nodePhone>treePhone;
	binaryTree <nodeLastName>treeLastName;
	nodePhone *newElemPhone;
	nodeLastName *newElemLastName;
	handbook hd;
	char symbol;

	while (true) {
		menu = numbers::getIntRange();
		if (menu == 10) {
			break;
		}
		switch (menu) {
		case 1:
			russianMessage("��������� ����� ������", true);
			russianMessage("������� ����� ��������: ", false);
			numerPhone = numbers::isType<long>();
			newElemPhone = treePhone.addNode<long>(numerPhone, treePhone.getRoot());
			russianMessage("������� �������: ", false);
			cin >> lastName;
			newElemLastName = treeLastName.addNode(lastName, treeLastName.getRoot());
			newElemPhone->ptrLastName = newElemLastName;
			newElemLastName->ptrPhone = newElemPhone;
			russianMessage("������ ���������", true);
			break;
		case 2:
			russianMessage("�������� ��������� �� ���� ", true);
			russianMessage("������� ����� ��������: ", false);
			numerPhone = numbers::isType<long>();
			newElemPhone = treePhone.showNumerPhone(treePhone.getRoot(), numerPhone);
			if (!newElemPhone) {
				russianMessage("��� ������� �� ����������� ������: ", false);
				cout << numerPhone << endl;
			}
			else {
				russianMessage("������� ������ �������� ������ ", false);
				cout << numerPhone;
				russianMessage(". ������� y/n ", true);
				symbol = numbers::isYesOrNo();
				if (symbol == 'y') { // �������
					newElemLastName = newElemPhone->ptrLastName;
					treePhone.deleteNode(newElemPhone);
					treeLastName.deleteNode(newElemLastName);
					russianMessage("������ �������", true);
				}
			}
			break;
		case 3:
			russianMessage("����������� ������ �������� ", true);
			russianMessage("������� ����� ��������: ", false);
			numerPhone = numbers::isType<long>();
			newElemPhone = treePhone.showNumerPhone(treePhone.getRoot(), numerPhone);
			if (!newElemPhone) {
				russianMessage("��� ������� �� ����������� ������: ", false);
				cout << numerPhone << endl;
			} 
			else {
				russianMessage("������ �������� ������ �������� ������ ", false);
				cout << numerPhone;
				russianMessage(". ������� y/n ", true);
				symbol = numbers::isYesOrNo();
				if (symbol == 'y') { // ������������
					russianMessage("������� ����� ��������: ", false);
					numerPhone = numbers::isType<long>();
					russianMessage("������� �������: ", false);
					cin >> lastName;
					// �������
					newElemLastName = newElemPhone->ptrLastName;
					treePhone.deleteNode(newElemPhone);
					treeLastName.deleteNode(newElemLastName);
					// ���������
					newElemPhone = treePhone.addNode<long>(numerPhone, treePhone.getRoot());
					newElemLastName = treeLastName.addNode(lastName, treeLastName.getRoot());
					newElemPhone->ptrLastName = newElemLastName;
					newElemLastName->ptrPhone = newElemPhone;
					russianMessage("������ ��������", true);
				}
			}
			break;
		case 4:
			russianMessage("����� ��������� �� ����������� ������", true);
			russianMessage("������� ����� ��������: ", false);
			numerPhone = numbers::isType<long>();
			newElemPhone = treePhone.showNumerPhone(treePhone.getRoot(), numerPhone);
			if (!newElemPhone) {
				russianMessage("��� ������� �� ����������� ������: ", false);
				cout << numerPhone << endl;
			}
			break;
		case 5:
			russianMessage("����� ��������� �� �������", true);
			russianMessage("������� �������: ", false);
			cin >> lastName;
			newElemLastName = treeLastName.showLastName(treeLastName.getRoot(), lastName);
			if (!newElemLastName) {
				russianMessage("��� ������� �� ������ �������: ", false);
				cout << lastName << endl;
			}
			break;
		case 6:
			russianMessage("���������� � ���������� ������� ��������� �� ��������� ��������� �������", true);
			treePhone.show(treePhone.getRoot());
			break;
		case 7:
			russianMessage("���������� � ���������� ������� ��������� �� ��������� ��������� �������", true);
			treeLastName.show(treeLastName.getRoot());
			break;
		case 8:
			russianMessage("���������� ���� � ����", true);
			hd.save(treePhone);
			russianMessage("������ ������� ���������", true);
			break;
		case 9:
			russianMessage("�������� ���� �� �����", true);
			hd.load(treePhone);
			break;
		}
	}

	return 0;
}

void russianMessage(char *message, bool enter) {
	char rmessage[256];
	CharToOem(message, rmessage);
	cout << rmessage;
	if (enter)
		cout << endl;
}