#include <iostream>
using namespace std;

template <class T>
struct listnode{
	T value;
	listnode *prev;
	listnode *next;
	listnode(int vl, listnode *prv, listnode *nxt) : value(vl), prev(prv), next(nxt)
	{

	}
};

template <class T>
class list {
	int count = 0;
	listnode<T> *head = nullptr;
	listnode<T> *last = nullptr;
public:
	void push(T value)
	{
		if (!count) {
			last = head = new listnode<T>(value, last, nullptr);
			++count;
			return;
		}
		listnode<T> *temp = last;
		last = new listnode<T>(value, last, nullptr);
		temp->next = last;
		if (count == 1) {
			head->next = last;
		}
		++count;
	}

	void pop()
	{
		if (!count) {
			return;
		}
		listnode<T> *temp = head;
		head = head->next;
		if (head)
			head->prev = nullptr;
		delete temp;
		--count;
		if (!count)
			last = nullptr;
	}

	void show()
	{
		listnode<T> *temp = head;
		while (temp)
		{
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void showLast()
	{
		listnode<T> *temp = last;
		while (temp)
		{
			cout << temp->value << " ";
			temp = temp->prev;
		}
		cout << endl;
	}

	void showCount()
	{
		cout << count << endl;
	}
};

int main() {
	list<char> lst;
	lst.push('a');
	lst.push('4');
	lst.push('d');
	lst.push('e');
	lst.push('s');
	lst.push('2');
	lst.show();
	lst.pop();
	lst.pop();
	lst.show();
	lst.showCount();

	return 0;
}