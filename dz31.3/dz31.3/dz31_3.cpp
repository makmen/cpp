#include <iostream>
#include <windows.h>
using namespace std;

class circle {
protected:
	int x, y;
	int radius;
public:
	circle(int x_, int y_, int radius_, HDC hDC) : x(x_), y(y_), radius(radius_)
	{
		SelectObject(hDC, GetStockObject(WHITE_BRUSH));
		Ellipse(hDC, x_, y_, radius_, radius_);
	}
};

class square {
protected:
	int x, y;
	int height;
public:
	square(int x_, int y_, int height_, HDC hDC) : x(x_), y(y_), height(height_)
	{
		SelectObject(hDC, GetStockObject(WHITE_PEN));
		POINT op;
		MoveToEx(hDC, x_, y_, &op);
		LineTo(hDC, x_, height_);
		LineTo(hDC, height_, height_);
		LineTo(hDC, height_, y_);
		LineTo(hDC, x_, y_);
	}
};

class circleSquare : circle, square {
public:
	// указываем только параметры квадрата
	circleSquare(int x_, int y_, int height_, HDC hDC) : square(x_, y_, height_, hDC), circle(x_, y_, height_, hDC)
	{


	}
};

int main() {
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	circleSquare cs(50, 50, 200, hDC);
	ReleaseDC(hWnd, hDC);

	return 0;
}