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
			cout << "������������ ������." << endl;
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
			cout << "������������ ������." << endl;
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
			cout << "������������ ������. ������� �����: 1, 2, 3, 4, 5" << endl;
			cin.clear();
			cin.ignore(10, '\n');
		}

		return i;
	}
};

struct nodeTickets {
	int num;			// ����� ��������������
	double summa;		// ����� ������
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
			cout << "����� ���������: " << temp->num << endl;
			cout << "����� ������: " << temp->summa << endl;
			temp = temp->next;
		}
	}

	~tickets() 
	{
		delList();
	}
};

struct Node{
	int value;		// ����� ������
	string fio;
	tickets *numTicket = nullptr;
	Node *left, *right, *parent;

	Node(int vl, Node *lft, Node *rght, Node *prnt) : value(vl), left(lft), right(rght), parent(prnt)
	{
		cout << "��� ����� ���������� " << value << endl;
		cout << "������� ������� � ��� �������� ��������: ";
		cin >> fio;
		numTicket = new tickets;
		addTicket();
	}

	void addTicket()
	{
		int num;
		double summa;
		cout << "������� ����� ���������: " << endl;
		num = numbers::isSignedType();
		cout << "������� ����� ������: " << endl;
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
		else { // ��������� ���������� ��������
			currentParent->addTicket();
			return;
		}
		if (prevElement) { // ������ ��� ��� 
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
			cout << "��� ����� ���������� " << currentElement->value << endl;
			cout << "������� � ��� �������� �������� " << currentElement->fio << endl;
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
				cout << "��� ����� ���������� " << currentElement->value << endl;
				cout << "������� � ��� �������� ��������" << currentElement->fio << endl;
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
			cout << "������� ������ �����: " << endl;
			first = numbers::isSignedType();
			cout << "������� ������ �����: " << endl;
			second = numbers::isSignedType();
			if (second > first) {
				int i = first;
				while (i <= second) {
					if (!showNumerAuto(root, i)) {
						cout << "��� ������� �� ������ ���������� " << i << endl;
					}
					++i;
				}
				break;
			}
			cout << "������������ �������� �������" << endl;
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
	cout << "��������� ���� ������ ��� �� �������� ����������" << endl;
	cout << "�������� ��������" << endl;
	cout << "1. �������� ���������" << endl;
	cout << "2. �������� ���� ���� ������" << endl;
	cout << "3. �������� ���� ������ �� ���������� ������" << endl;
	cout << "4. �������� ���� ������ �� ���������� ���������" << endl;
	cout << "5. ����� " << endl;
	int menu;
	int nomerAuto;
	while (true) {
		menu = numbers::getIntRange();
		if (menu == 5) {
			break;
		}
		switch (menu) {
		case 1:
			cout << "�������� ���������" << endl;
			cout << "������� ����� ������" << endl;
			nomerAuto = numbers::isSignedType();
			Tree.addNode(nomerAuto, Tree.getRoot());
			cout << "�������� ����������� �������" << endl;
			break;
		case 2:
			cout << endl;
			cout << "�������� ���� ���� ������" << endl;
			Tree.show(Tree.getRoot());
			break;
		case 3:
			cout << endl;
			cout << "�������� ���� ������ �� ���������� ������" << endl;
			cout << "������� ����� ����������" << endl;
			nomerAuto = numbers::isSignedType();
			if (!Tree.showNumerAuto(Tree.getRoot(), nomerAuto)) {
				cout << "��� ������� �� ������ ���������� " << nomerAuto << endl;
			}
			break;
		default:
			cout << "�������� ���� ������ �� ���������� ���������" << endl;
			Tree.showRangeNumerAuto();
		}
	}

	return 0;
}


