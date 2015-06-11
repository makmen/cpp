#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class colodaKart {

	int size;			// счетчик карт в колоде
	int N;				// число значений карт от 2 - 10, валет, дама, король, туз, всего 13
	int countDeck;		// количество колод 6, по 52 карты в каждой
	int countkartInDeck;// количество карт в каждой колоде 52
	int countColour;	// количество мастей в колоде 4
	int **koloda;		// вся колода 
	int *current;		// указатель на карту (карты в колоде перемешиваются и затем берутся сверху, и мы будем брать также
						// с 0 и до 312, для этого нужен указатель на карту, при выдачи новой делаем ++current[масть])
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
		// инициализация колоды
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
		// перемешиваем колоду
		for (int i = 0, j = 0, n = N * countDeck; i < n; ++i) {
			swap(koloda[i][j], koloda[rand() % n][j]);
			if (i == (n - 1) && j < countColour) {
				i = 0;
				++j;
			}
		}
		// инициализация 0 current
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
		int rndColour = rand() % countColour;		// получить масть
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
			cout << "два ";
			break;
		case 3:
			cout << "три ";
			break;
		case 4:
			cout << "четыре ";
			break;
		case 5:
			cout << "пять ";
			break;
		case 6:
			cout << "шесть ";
			break;
		case 7:
			cout << "семь ";
			break;
		case 8:
			cout << "восемь ";
			break;
		case 9:
			cout << "девять ";
			break;
		case 10:
			cout << "десять ";
			break;
		case 11:
			cout << "валет ";
			break;
		case 12:
			cout << "дама ";
			break;
		case 13:
			cout << "король ";
			break;
		case 14:
			cout << "туз ";
			break;
		}
		switch (colour) {
		case 0:
			cout << "пики";
			break;
		case 1:
			cout << "трефы";
			break;
		case 2:
			cout << "червы";
			break;
		case 3:
			cout << "бубны";
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

	int count;			// здесть будет число очков в игре
	int **karts;		// какие карты вытянул игрок
	int N;				// максимальное количество карт, которые может вытянуть игрок 11
	int indexKarta;		// текущая карта
	int win;

public:

	players()
	{
		N = 11;
		win = 21;
		karts = new int*[N]; // 0 - значение карты(валет, дама, ... ) 1 - масть от 0 ... 3 
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
		int ace = searchAce(); // если тузов нету все гуд, в противном случае определяем лучший счет для игрока
		if (ace > 0) {		  // возвращается результат наиболее близкий к 21, перебор не допустим
			bestCount(ace);
		}
		cout << "общее колечиество очков: " << count << "\n";
		++indexKarta;
		return count;
	}

	void bestCount(int ace)
	{
		count = 0;
		// ставим минимальное количество очков, пересчитываем
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

	int searchAce() // функция вернет количество тузов
	{
		int k = 0; // тузов нету
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
		if (indexKarta == 2) { // возможен блэк джек
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
	cout << "Добро пожаловать в карточную игру Блэк-Джек\n";
	cout << "Нажмите Enter чтобы начать игру\n";
	char ch, symbol;
	bool turn = true;			// true - ход игрока, false ход компа
	bool statusGame = true;		// true - игра идет, false конец 
	bool exit = false;			// выход из игры
	int count = 0, countComp = 0;
	while ((ch = getchar()) != '\n');
	colodaKart ck;
	players p1;
	players comp;
	int compBlackJack = 0;
	int p1BlackJack = 0;
	// раздаем играку одну карту
	count = p1.takeKart(&ck);
	while (true) {
		if (turn) {
			cout << "Хотите еще карту? Нажмите y - да, n - нет.\n";
			while (true) {
				cin >> (char)symbol;
				while ((ch = getchar()) != '\n');
				if (symbol == 'n') {
					turn = false;	// ход компа
					break;
				}
				else if (symbol == 'y') {
					count = p1.takeKart(&ck);
					break;
				}
				else {
					cout << "Нажмите y - да, n - нет.\n";
				}
			}
			if (turn && statusGame) {
				if (count > win){
					statusGame = false;
				}
				else if (count == win) {
					p1BlackJack = p1.haveBlackJack();
					turn = false;	// ход компа
				}
			}
		}
		else { // ход компа. логика компа простая если сумма меньше чем у игрока он берет карты пока не выиграет или пока не будет перебора
			cout << "\nХод компьютера... \n";
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
					else {// выходим из игры, пусть лучше будет ничья
						statusGame = false;
						break;
					}
				}
				else {
					// это перебор либо комп выиграл
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
				cout << "Вы проиграли. У вас перебор. Сумма очков: " << count << "\n";
			}
			else if (count == countComp) {
				if (compBlackJack && !p1BlackJack) {
					cout << "Вы проиграли. Сумма очков у вас: " << count << "\n";
					cout << "БлэкДжек у компьютера.\n";
				}
				else if (!compBlackJack && p1BlackJack) {
					cout << "Вы Выиграли.У вас БлэкДжек\n";
					cout << "Сумма очков у компьютера: " << countComp << "\n";
				}
				else if (compBlackJack && p1BlackJack) {
					cout << "Ничья. У вас БлэкДжек\n";
					cout << "БлэкДжек у компьютера.\n";
				}
				else {
					cout << "Ничья. Сумма очков у вас: " << count << "\n";
					cout << "Сумма очков у компьютера: " << countComp << "\n";
				}
			}
			else if (count > countComp || countComp > win) {
				cout << "Вы выиграли. Сумма очков у вас: " << count << "\n";
				cout << "Сумма очков у компьютера: " << countComp << "\n";
			}
			else {
				cout << "Вы проиграли. Сумма очков у вас: " << count << "\n";
				cout << "Сумма очков у компьютера: " << countComp << "\n";
			}
			while (true) {
				cout << "\nПродолжить игру, y - да, n - нет?\n";
				cin >> (char)symbol;
				while ((ch = getchar()) != '\n');
				if (symbol == 'n') {
					cout << "До свидания\n";
					exit = true;
					break;
				}
				else if (symbol == 'y') { // запускаем новый раунд
					cout << "\n";
					p1.newRound();
					comp.newRound();
					statusGame = true;
					turn = true;
					// если в колоде меньше 150 карт перетосовка колоды
					if (ck.getSize() < 150) {
						ck.newTurn();
					}
					count = p1.takeKart(&ck);
					break;
				}
				else {
					cout << "Нажмите y - да, n - нет.\n";
				}
			}
		}
		if (exit)
			break;
	}

	return 0;
}