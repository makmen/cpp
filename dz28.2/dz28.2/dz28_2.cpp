#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

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
			cout << "Некорректные данные." << endl;
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
			cout << "Некорректные данные." << endl;
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
				if (i > 0 && i < 6)  {
					break;
				}
			}
			cout << "Некорректные данные. Введите числа: 1, 2, 3, 4, 5" << endl;
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}
};

struct nodeTickets {
	int num;			// номер правонарушения
	double summa;		// сумма штрафа
	nodeTickets *next;
	nodeTickets(int num_, double summa_, nodeTickets *next_) : num(num_), summa(summa_), next(next_)
	{

	}
};

class tickets {
	int count;
	nodeTickets *head;
	nodeTickets *last;
public:
	tickets() : head(nullptr), last(nullptr), count(0)
	{

	}

	void addInHead(int num, double summa)
	{
		head = new nodeTickets(num, summa, head);
		++count;
		if (!last) {
			last = head;
		}
	}

	void addInLast(int num, double summa)
	{
		if (!head) {
			addInHead(num, summa);
			return;
		}
		nodeTickets *newElem = new nodeTickets(num, summa, nullptr);
		last->next = newElem;
		last = newElem;
		++count;
	}

	void delList()
	{
		nodeTickets *temp = head;
		while (head) {
			temp = head->next;;
			delete head;
			head = temp;
		}
	}

	void show()
	{
		nodeTickets * temp = head;
		while (temp)
		{
			cout << "Номер квитанции: " << temp->num << endl;
			cout << "Сумма штрафа: " << temp->summa << endl;
			temp = temp->next;
		}
	}

	~tickets() 
	{
		delList();
	}
};

struct Node{
	int value;		// номер машины
	string fio;
	tickets *numTicket = nullptr;
	Node *left, *right, *parent;

	Node(int vl, Node *lft, Node *rght, Node *prnt) : value(vl), left(lft), right(rght), parent(prnt)
	{
		cout << "Гос номер автомабиля " << value << endl;
		cout << "Введите фамилию и имя отчество водителя: ";
		cin >> fio;
		numTicket = new tickets;
		addTicket();
	}

	void addTicket()
	{
		int num;
		double summa;
		cout << "Введите номер квитанции: " << endl;
		num = numbers::isSignedType();
		cout << "Введите сумму штрафа: " << endl;
		summa = numbers::isType<double>();
		numTicket->addInLast(num, summa);
	}

	~Node()
	{
		if (numTicket) {
			delete numTicket;
		}
	}

};

class binaryTree {
	Node *root = nullptr;
public:

	binaryTree() = default;

	void addNode(int val, Node *currentParent)
	{
		if (!root) {
			root = new Node(val, nullptr, nullptr, nullptr);
			return;
		}
		Node *prevElement = currentParent;
		if (currentParent->value > val) {
			prevElement = currentParent->left;
		}
		else if (currentParent->value < val) {
			prevElement = currentParent->right;
		}
		else { // вставляем одинаковые значения
			currentParent->addTicket();
			return;
		}
		if (prevElement) { // входим еще раз 
			addNode(val, prevElement);
		}
		else {
			Node *newElement = new Node(val, nullptr, nullptr, currentParent);
			if (currentParent->value > val) {
				currentParent->left = newElement;
			}
			else {
				currentParent->right = newElement;
			}
		}
	}

	void deleteAllItems()
	{
		Node *current = root;
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

	Node *deleteNode(Node *currentElement)
	{
		Node *previous = currentElement->parent;
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

	void show(Node *currentElement)
	{
		if (currentElement) {
			show(currentElement->left);
			cout << "Гос номер автомабиля " << currentElement->value << endl;
			cout << "Фамилия и имя отчество водителя " << currentElement->fio << endl;
			currentElement->numTicket->show();
			cout << endl;
			show(currentElement->right);
		}
	}

	bool showNumerAuto(Node *currentElement, int num)
	{
		bool flag = false; 
		if (currentElement) {
			flag = showNumerAuto(currentElement->left, num);
			if (currentElement->value == num) {
				cout << "Гос номер автомабиля " << currentElement->value << endl;
				cout << "Фамилия и имя отчество водителя" << currentElement->fio << endl;
				currentElement->numTicket->show();
				cout << endl;
				return true;
			}
			if (!flag)
				flag = showNumerAuto(currentElement->right, num);
		}
		return flag;
	}

	void showRangeNumerAuto() 
	{
		int first;
		int second;
		while (true) {
			cout << "Введите первый номер: " << endl;
			first = numbers::isSignedType();
			cout << "Введите второй номер: " << endl;
			second = numbers::isSignedType();
			if (second > first) {
				int i = first;
				while (i <= second) {
					if (!showNumerAuto(root, i)) {
						cout << "Нет записей по номеру автомобиля " << i << endl;
					}
					++i;
				}
				break;
			}
			cout << "Неправильный диапазон адресов" << endl;
		}
	}

	Node *getRoot()
	{
		return root;
	}

	~binaryTree()
	{
		deleteAllItems();
	}
};

int main() { 
	setlocale(LC_CTYPE, "Russian");
	binaryTree Tree;
	cout << "Программа база данных ГАИ по штрафным квитанциям" << endl;
	cout << "Выбирете действие" << endl;
	cout << "1. Добавить квитанцию" << endl;
	cout << "2. Просмотр всей базы данных" << endl;
	cout << "3. Просмотр базы данных по указанному номеру" << endl;
	cout << "4. Просмотр базы данных по указанному диапазону" << endl;
	cout << "5. Выход " << endl;
	int menu;
	int nomerAuto;
	while (true) {
		menu = numbers::getIntRange();
		if (menu == 5) {
			break;
		}
		switch (menu) {
		case 1:
			cout << "Добавить квитанцию" << endl;
			cout << "Введите номер машины" << endl;
			nomerAuto = numbers::isSignedType();
			Tree.addNode(nomerAuto, Tree.getRoot());
			cout << "Операция произведена успешно" << endl;
			break;
		case 2:
			cout << endl;
			cout << "Просмотр всей базы данных" << endl;
			Tree.show(Tree.getRoot());
			break;
		case 3:
			cout << endl;
			cout << "Просмотр базы данных по указанному номеру" << endl;
			cout << "Введите номер автомобиля" << endl;
			nomerAuto = numbers::isSignedType();
			if (!Tree.showNumerAuto(Tree.getRoot(), nomerAuto)) {
				cout << "Нет записей по номеру автомобиля " << nomerAuto << endl;
			}
			break;
		default:
			cout << "Просмотр базы данных по указанному диапазону" << endl;
			Tree.showRangeNumerAuto();
		}
	}

	return 0;
}


