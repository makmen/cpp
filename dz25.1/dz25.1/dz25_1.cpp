#include <iostream>
using namespace std;

class complex {

	double x;
	double y;

public:

	complex(double _x, double _y) : x(_x), y(_y)
	{

	}

	complex(double _x) : x(_x), y(0)
	{

	}

	complex(const complex &obj)
	{
		x = obj.x;
		y = obj.y;
	}

	complex& operator = (const complex &obj)
	{
		if (this != &obj) {
			x = obj.x;
			y = obj.y;
		}

		return *this;
	}

	complex operator + (const complex &obj)
	{
		complex temp(x, y);
		temp.x = x + obj.x;
		temp.y = y + obj.y;

		return temp;
	}

	complex& operator += (double a)
	{
		x += a;

		return *this;
	}

	complex operator - (const complex &obj)
	{
		complex temp(x, y);
		temp.x = x - obj.x;
		temp.y = y - obj.y;

		return temp;
	}

	complex& operator -= (double a)
	{
		x -= a;

		return *this;
	}

	complex operator * (const complex &obj)
	{
		complex temp(x, y);
		temp.x = x * obj.x - y * obj.y;
		temp.y = x * obj.y + y * obj.x;

		return temp;
	}

	complex& operator *= (double a)
	{
		x *= a;
		y *= a;

		return *this;
	}

	complex operator / (const complex &obj)
	{
		complex temp(x, y);
		temp.x = (x * obj.x + y * obj.y) / (obj.x * obj.x + obj.y * obj.y);
		temp.y = (y * obj.x - x * obj.y) / (obj.x * obj.x + obj.y * obj.y);

		return temp;
	}

	complex& operator /= (double a)
	{
		x /= a;
		y /= a;

		return *this;
	}

	bool operator == (const complex &obj)
	{
		bool flag = false;
		if (x == obj.x && y == obj.y) {
			flag = true;
		}

		return flag;
	}

	void show()
	{
		cout << x;
		if (y >= 0)
			cout << " + i * " << y;
		else
			cout << " - i * " << y*(-1);
		cout << "\n";
	}

};

int main() {
	complex c1(5, 3);
	complex c2(5, -3);
	complex c3(4, -2);
	complex c4(1, 0);

	if (c1 == c2) {
		c1.show();
		c2.show();
	}

	c1.show();
	c2.show();
	c3.show();
	c4.show();

	return 0;
}