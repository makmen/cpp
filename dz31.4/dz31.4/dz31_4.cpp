#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

// класс "точка"
class Point{
	int X = 0;
	int Y = 0;
public:
	Point()
	{

	}

	int getX()
	{
		return X;
	}

	int getY()
	{
		return Y;
	}

	void SetPoint(int iX, int iY)
	{
		X = iX;
		Y = iY;
	}

	void Show()
	{
		cout << X << "\t" << Y << "\n\n";
	}
};

//класс фигура
class Figura{
	// агрегация точки (координаты углов)
	Point *pnt = nullptr;
	// количество координат
	int count = 0;
	// цвет фигуры
	int color = 0;
public:
	Figura()
	{
		srand(time(NULL));
	}

	void CreateCoordinates(int cr, int ct)
	{
		//инициализация цвета и количества углов
		count = ct;
		color = cr;
		// выдделение памяти под массив точек
		pnt = new Point[count];
		if (!pnt) exit(0);
		//установка координат точек
		int tempX, tempY;
		for (int i = 0; i < count; i++){
			tempX = rand() % 50 + 200;
			tempY = rand() % 50;
			pnt[i].SetPoint(tempX, tempY);
		}
	}

	void ShowFigura()
	{
		cout << "----------------------------\n\n";
		cout << "Color = " << color << "\n\nPoints = " << count << "\n\n";
		for (int i = 0; i<count; i++){
			pnt[i].Show();
		}
		cout << "----------------------------\n\n";
	}

	Point *getPoint()
	{
		return pnt;
	}

	int getCountPoint()
	{
		return count;
	}

	~Figura()
	{
		if (pnt != nullptr)
			delete[]pnt;
	}
};

// класс рисунок, включает в себя нисколько фигур и прорисовывает каждую фигуру
class picture {
	signed count = 0;		// количество фигур 
	Figura *fgr = nullptr;	// массив указателей на фигуры
public:
	picture()
	{
		srand(time(NULL));
	}

	void addFigura() 
	{
		// выделяем память
		fgr = (Figura *)realloc(fgr, sizeof(Figura)* ++count);
		int i = count - 1;
		fgr[i].CreateCoordinates(255, (rand() % 4 + 3));
		fgr[i].ShowFigura();
	}

	void drawFigura() 
	{
		if (fgr) {
			HWND hWnd = GetConsoleWindow();
			HDC hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(WHITE_PEN));
			POINT op;
			int startX = 100, startY = 50;
			int offset = 100;
			int countPoint = 0;							// количество точек
			int x, y;
			Point *pnt = nullptr;
			for (int i = 0; i < count; ++i) {
				startX += offset;
				MoveToEx(hDC, startX, startY, &op);		// начало отсчета для всех фигур пусть будет одинаково
				countPoint = fgr[i].getCountPoint();
				pnt = fgr[i].getPoint();
				for (int j = 0; j < countPoint; ++j) {
					x = pnt[j].getX();
					if (j)
						x += offset;
					y = pnt[j].getY();
					LineTo(hDC, x, y);
				}
				// Замыкаем фигуру
				LineTo(hDC, startX, startY);
			}
			ReleaseDC(hWnd, hDC);
		}
	}

	~picture()
	{

	}
};

int main() {
	picture pc;
	pc.addFigura();
	pc.addFigura();
	pc.addFigura();
	pc.drawFigura();

	return 0;
}