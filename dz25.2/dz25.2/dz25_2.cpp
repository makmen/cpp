#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class colodaKart {

	int size;			// ������� ���� � ������
	int N;				// ����� �������� ���� �� 2 - 10, �����, ����, ������, ���, ����� 13
	int countDeck;		// ���������� ����� 6, �� 52 ����� � ������
	int countkartInDeck;// ���������� ���� � ������ ������ 52
	int countColour;	// ���������� ������ � ������ 4
	int **koloda;		// ��� ������ 
	int *current;		// ��������� �� ����� (����� � ������ �������������� � ����� ������� ������, � �� ����� ����� �����
						// � 0 � �� 312, ��� ����� ����� ��������� �� �����, ��� ������ ����� ������ ++current[�����])
public:

	colodaKart()
	{
		countDeck = 6;
		countkartInDeck = 52;
		N = 13;
		countColour = 4;
		current = 0;
		int n = N * countDeck;
		current = new int[countColour];
		// ������������� ������
		koloda = new int*[n];
		for (int i = 0; i < n; ++i) {
			koloda[i] = new int[countColour];
		}
		for (int i = 0, k = 2; i < n; ++i, ++k) {
			for (int j = 0; j < countColour; ++j) {
				if (k > 14) k = 2;
				koloda[i][j] = k;
			}
		}
		newTurn();
		srand(time(NULL));
	}

	void newTurn()
	{
		size = 312;
		// ������������ ������
		for (int i = 0, j = 0, n = N * countDeck; i < n; ++i) {
			swap(koloda[i][j], koloda[rand() % n][j]);
			if (i == (n - 1) && j < countColour) {
				i = 0;
				++j;
			}
		}
		// ������������� 0 current
		for (int i = 0; i < countColour; ++i) {
			current[i] = 0;
		}
	}

	int getSize()
	{

		return size;
	}

	void getKart(int *karta)
	{
		int rndColour = rand() % countColour;		// �������� �����
		karta[0] = koloda[current[rndColour]][rndColour];
		karta[1] = rndColour;
		++current[rndColour];
		showKart(karta[0], karta[1]);
		--size;
	}

	void showKart(int karta, int colour)
	{
		switch (karta) {
		case 2:
			cout << "��� ";
			break;
		case 3:
			cout << "��� ";
			break;
		case 4:
			cout << "������ ";
			break;
		case 5:
			cout << "���� ";
			break;
		case 6:
			cout << "����� ";
			break;
		case 7:
			cout << "���� ";
			break;
		case 8:
			cout << "������ ";
			break;
		case 9:
			cout << "������ ";
			break;
		case 10:
			cout << "������ ";
			break;
		case 11:
			cout << "����� ";
			break;
		case 12:
			cout << "���� ";
			break;
		case 13:
			cout << "������ ";
			break;
		case 14:
			cout << "��� ";
			break;
		}
		switch (colour) {
		case 0:
			cout << "����";
			break;
		case 1:
			cout << "�����";
			break;
		case 2:
			cout << "�����";
			break;
		case 3:
			cout << "�����";
			break;
		}
		cout << "\n";
	}

	void show()
	{
		for (int i = 0, n = N * countDeck; i < n; ++i) {
			for (int j = 0; j < countColour; ++j) {
				cout << koloda[i][j] << "\t";
			}
			cout << "\n";
		}
	}

	void swap(int &left, int &right)
	{
		int tmp = left;
		left = right;
		right = tmp;
	}

	~colodaKart()
	{
		for (int i = 0, n = N * countDeck; i < n; ++i) {
			delete[]koloda[i];
		}
		delete[]koloda;
		delete[]current;
	}

};

class players {

	int count;			// ������ ����� ����� ����� � ����
	int **karts;		// ����� ����� ������� �����
	int N;				// ������������ ���������� ����, ������� ����� �������� ����� 11
	int indexKarta;		// ������� �����
	int win;

public:

	players()
	{
		N = 11;
		win = 21;
		karts = new int*[N]; // 0 - �������� �����(�����, ����, ... ) 1 - ����� �� 0 ... 3 
		for (int i = 0; i < N; ++i) {
			karts[i] = new int[2];
		}
		newRound();
	}

	void newRound()
	{
		count = 0;
		indexKarta = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < 2; ++j) {
				karts[i][j] = 0;
			}
		}
	}

	int takeKart(colodaKart *ptr)
	{
		ptr->getKart(karts[indexKarta]);
		count += getValueKart(karts[indexKarta][0]);
		int ace = searchAce(); // ���� ����� ���� ��� ���, � ��������� ������ ���������� ������ ���� ��� ������
		if (ace > 0) {		  // ������������ ��������� �������� ������� � 21, ������� �� ��������
			bestCount(ace);
		}
		cout << "����� ����������� �����: " << count << "\n";
		++indexKarta;
		return count;
	}

	void bestCount(int ace)
	{
		count = 0;
		// ������ ����������� ���������� �����, �������������
		for (int i = 0; i < N; ++i) {
			if (!karts[i][0]) {
				break;
			}
			count += getValueKart(karts[i][0]);
		}
		int max = count;
		for (int i = 0; i < ace; ++i) {
			max += 10;
		}
		do {
			if (max == win || max < win) {
				count = max;
				break;
			}
			else {
				max -= 10;
			}
		} while (--ace);
	}

	int searchAce() // ������� ������ ���������� �����
	{
		int k = 0; // ����� ����
		for (int i = 0; i < N; ++i) {
			if (!karts[i][0]) {
				break;
			}
			if (karts[i][0] == 14) {
				++k;
			}
		}

		return k;
	}

	int haveBlackJack()
	{
		if (indexKarta == 2) { // �������� ���� ����
			int k = 0;
			for (int i = 0; i < indexKarta; ++i) {
				if (karts[i][0] == 10 || karts[i][0] == 14) {
					++k;
				}
			}
			if (k == 2) {
				cout << "\nBlackJack!!!\n";
				return k;
			}
		}

		return 0;
	}

	int getValueKart(int karta)
	{
		switch (karta) {
		case 11: case 12: case 13:
			karta = 10;
			break;
		case 14:
			karta = 1;
			break;
		}

		return karta;
	}

	~players()
	{
		for (int i = 0; i < N; ++i) {
			delete[]karts[i];
		}
		delete[]karts;
	}

};

const int win = 21;

void delayStep()
{
	unsigned long t;
	for (t = 0; t < 500000000L; ++t);
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "����� ���������� � ��������� ���� ����-����\n";
	cout << "������� Enter ����� ������ ����\n";
	char ch, symbol;
	bool turn = true;			// true - ��� ������, false ��� �����
	bool statusGame = true;		// true - ���� ����, false ����� 
	bool exit = false;			// ����� �� ����
	int count = 0, countComp = 0;
	while ((ch = getchar()) != '\n');
	colodaKart ck;
	players p1;
	players comp;
	int compBlackJack = 0;
	int p1BlackJack = 0;
	// ������� ������ ���� �����
	count = p1.takeKart(&ck);
	while (true) {
		if (turn) {
			cout << "������ ��� �����? ������� y - ��, n - ���.\n";
			while (true) {
				cin >> (char)symbol;
				while ((ch = getchar()) != '\n');
				if (symbol == 'n') {
					turn = false;	// ��� �����
					break;
				}
				else if (symbol == 'y') {
					count = p1.takeKart(&ck);
					break;
				}
				else {
					cout << "������� y - ��, n - ���.\n";
				}
			}
			if (turn && statusGame) {
				if (count > win){
					statusGame = false;
				}
				else if (count == win) {
					p1BlackJack = p1.haveBlackJack();
					turn = false;	// ��� �����
				}
			}
		}
		else { // ��� �����. ������ ����� ������� ���� ����� ������ ��� � ������ �� ����� ����� ���� �� �������� ��� ���� �� ����� ��������
			cout << "\n��� ����������... \n";
			while (true) {
				delayStep();
				countComp = comp.takeKart(&ck);
				if (countComp < win && countComp < count) {
					continue;
				}
				else if (countComp == count) {
					if (countComp < 15) {
						continue;
					}
					else {// ������� �� ����, ����� ����� ����� �����
						statusGame = false;
						break;
					}
				}
				else {
					// ��� ������� ���� ���� �������
					statusGame = false;
					break;
				}
			}
		}

		if (!statusGame) {
			if (countComp == win) {
				compBlackJack = comp.haveBlackJack();
			}
			cout << "\n";
			if (count > win){
				cout << "�� ���������. � ��� �������. ����� �����: " << count << "\n";
			}
			else if (count == countComp) {
				if (compBlackJack && !p1BlackJack) {
					cout << "�� ���������. ����� ����� � ���: " << count << "\n";
					cout << "�������� � ����������.\n";
				}
				else if (!compBlackJack && p1BlackJack) {
					cout << "�� ��������.� ��� ��������\n";
					cout << "����� ����� � ����������: " << countComp << "\n";
				}
				else if (compBlackJack && p1BlackJack) {
					cout << "�����. � ��� ��������\n";
					cout << "�������� � ����������.\n";
				}
				else {
					cout << "�����. ����� ����� � ���: " << count << "\n";
					cout << "����� ����� � ����������: " << countComp << "\n";
				}
			}
			else if (count > countComp || countComp > win) {
				cout << "�� ��������. ����� ����� � ���: " << count << "\n";
				cout << "����� ����� � ����������: " << countComp << "\n";
			}
			else {
				cout << "�� ���������. ����� ����� � ���: " << count << "\n";
				cout << "����� ����� � ����������: " << countComp << "\n";
			}
			while (true) {
				cout << "\n���������� ����, y - ��, n - ���?\n";
				cin >> (char)symbol;
				while ((ch = getchar()) != '\n');
				if (symbol == 'n') {
					cout << "�� ��������\n";
					exit = true;
					break;
				}
				else if (symbol == 'y') { // ��������� ����� �����
					cout << "\n";
					p1.newRound();
					comp.newRound();
					statusGame = true;
					turn = true;
					// ���� � ������ ������ 150 ���� ����������� ������
					if (ck.getSize() < 150) {
						ck.newTurn();
					}
					count = p1.takeKart(&ck);
					break;
				}
				else {
					cout << "������� y - ��, n - ���.\n";
				}
			}
		}
		if (exit)
			break;
	}

	return 0;
}