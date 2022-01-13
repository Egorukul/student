#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

//Функция
double f(double x) {
	return pow(x, 4) - x - 1;
	//return pow(x, 3) + x - 1;
}
//Первая производная
double df(double x,double h) {

	return (f(x + h) - f(x - h)) / (2 * h);
	//return 4 * pow(x, 3) - 1;
}
//Вторая производная
double ddf(double x,double h) {
	return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
	//return 12 * pow(x,2);
}


void Newt(int a,int b,double e){
	double x0 = 0, x1;
	int i=1;
	double h = 0.001; // шаг с которым вычисляем производную

	//Нахождение x0
	if (f(a) * ddf(a, h) > 0 && f(a)*f(b)<0) {
		x0 = a;
	}
	else if (f(b) * ddf(b,h) > 0 && f(a) * f(b) < 0)
		x0 = b;
	else {
		cout << "Условие не подходит" << endl;
		exit(1);
	}
	cout << "x0 = " << x0 << endl;
	
	//Нахождения x1
	x1 = x0 - f(x0) / df(x0,h);
	cout << "x" << i << " = " << x1 << endl;
	// x0=-0.25 x1=
	//Цикл для нахождения остальных x
	while (abs(x1 - x0) >= e)
	{
		i++;
		x0 = x1;
		x1 = x0 - f(x0) / df(x0,h);
		cout << "x" << i << " = " << x1 << endl;
	}
	cout << "Корень уравнения x = " << x1 << endl;
}

int main() {
	setlocale(LC_ALL, "russian");
	int a, b;
	double e;
	cout << "Функция: x^4-x-1"<<endl;
		cout << "Интервал от a = ";
		cin >> a;
		cout << "до b = ";
		cin >> b;
		cout << "Погрешность E= ";
		cin >> e;
		Newt(a, b, e);
	
}
