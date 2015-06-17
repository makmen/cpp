#include <iostream>
#include <stdlib.h>
using namespace std;

struct listnode{
	int value;
	listnode *next;
	listnode(int n, listnode *ptr) : value(n), next(ptr)
	{

	}
};

class list {
	int count = 0;
	listnode *head = nullptr;
	listnode *last = nullptr;
public:
	void addInLast(int n)
	{
		if (!head) {
			addInHead(n);
			return;
		}
		listnode *newElem = new listnode(n, nullptr);
		last->next = newElem;
		last = newElem;
		++count;
	}

	void addInHead(int n)
	{
		head = new listnode(n, head);
		++count;
		if (!last) {
			last = head;
		}
	}

	void addInAny(int n, int index)
	{
		if (index < 0) {
			return;
		}
		if (!head || !index) {
			addInHead(n);
			return;
		}
		if (index >= count) {
			addInLast(n);
			return;
		}
		listnode *current = head;
		listnode *prev = head;
		int i = 1;
		for (int i = 1; i < count; ++i)
		{
			current = current->next;
			if (i == index - 1) {
				prev = current;
			}
			if (i == index) {
				break;
			}
		}
		listnode *any = new listnode(n, current);
		prev->next = any;
		++count;
	}

	void delHead()
	{
		if (count) {
			if (count == 1) {
				head = last = nullptr;
			}
			else {
				head = head->next;
			}
			--count;
			if (count == 1) {
				last = head;
			}
		}
	}

	void del(int index)
	{
		if (index <= 0) {
			delHead();
			return;
		}
		if (index >= count) {
			return;
		}
		listnode *current = head;
		listnode *prev = head;
		for (int i = 1; i < count; ++i)
		{
			current = current->next;
			if (i == index - 1) {
				prev = current;
			}
			if (i == index) {
				prev->next = current->next;
				--count;
				if (index == count) {// элемент последний
					last = prev;
				}

				return;
			}
		}
	}

	void show()
	{
		listnode * temp = head;
		while (temp)
		{
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	int searchValue(int n)
	{
		listnode * temp = head;
		int i = 0, ret = -1;
		while (temp) {
			if (temp->value == n) {
				return i;
			}
			temp = temp->next;
			++i;
		}

		return ret;
	}

	void showCount()
	{
		cout << count << endl;
	};

};

int main() {
	list lst;
	lst.addInHead(305);
	lst.addInHead(25);
	lst.addInHead(10);
	lst.addInAny(3200, 0);
	lst.addInAny(9900, 5);
	lst.addInAny(200, 3);
	lst.show();
	lst.del(4);
	lst.showCount();
	lst.show();
	cout << lst.searchValue(200) << endl;

	return 0;
}