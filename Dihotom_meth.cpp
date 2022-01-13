#include <iostream>
#include <cmath>

using namespace std;
double func(float arg) {
	return pow(arg, 5) - arg - 2;

}
int dihotom(float a,float b,float e) {
	float x;

	do {
		x = (a + b) / 2;

		if (func(x) < 0 || func(b)<0)
			a = x;
		else
			b = x;

	} while (abs(b - a) > e);

	cout <<"Значение x = "<< x << endl;
	cout << "Отрезок ot a = " << a << " до b= " << b << endl;
	cout << "Погрешность e = " << abs(b - a) << endl;
	cout << "F(x) = " << func(x) << endl;
	return 0;
	
}
int main()
{
	setlocale(LC_ALL, "russian");
	float a, b, e;
	while (true) {
		cout << "Функция: x^5-x-2" << endl;
		cout << "Введите значения" << endl;
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		cout << "e = ";
		cin >> e;
		dihotom(a, b, e);
	}
}

