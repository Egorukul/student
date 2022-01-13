#include <iostream>
#include <utility>
#include <typeinfo>
using namespace std;
//Преобразование знаменателя
/*int poryadok(int p) {
	int m;
	float n;
	n = p + 1 + 2 * sqrt(p);
	m = ceil(sqrt(n));
	return m;
}
*/
int x_r(int x, int p) {
	for (int i = 1; i < p; i++) {
		if (abs(x) * i % p == 1)
			if (x < 0)
				return -i;
			else if (x > 0)
				return i;
	}
	return 0;
}
//Преобразование числа по модулю
int preobr(int i, int p) {
	if (i % p >= 0) { // Если число больше 0 как остаток от деления на n
		i = i % p;
	}
	else if (i % p < 0) { //Если число меньше 0 как остаток от деления на n 
		while (i < 0)
			i = i + p;
	}
	return i;
}

//Сумма точек
std::pair<int, int> sum(int p, int x1, int y1, int x2, int y2) {
	int l, x3, y3;

	l = (y2 - y1) * x_r(x2 - x1, p); //Ф-ла (y2-y1)/(x2-x1) 
	if (x_r(x2 - x1, p) == 0)
		return pair<int, int>(0, 0);
	l = preobr(l, p);

	x3 = preobr(pow(l, 2) - x1 - x2, p);
	y3 = preobr(l * (x1 - x3) - y1, p);


	return pair<int, int>(x3, y3);
}
//Удвоение точек
std::pair<int, int> mult(int p, int x1, int y1, int a) {
	int l, x3, y3;
	l = (3 * pow(x1, 2) + a) * x_r(2 * y1, p); //Ф-ла (3*x1^2+a)//2*y1
	l = preobr(l, p);

	x3 = preobr(pow(l, 2) - 2 * x1, p);

	y3 = preobr(l * (x1 - x3) - y1, p);

	//cout << "2P = P + P = (" << x3 << "," << y3 << ")" << endl;

	return pair<int, int>(x3, y3);
}
//Скалярное произведение
std::pair<int, int> skal(int m, int p, int a, int b, int x1, int y1) {
	int i = 2;
	auto s = mult(p, x1, y1, a);
	while ((s.first != 0 || s.second != 0) && i != m) {
		i = i++;
		s = sum(p, x1, y1, s.first, s.second);

	}
	cout << i << "P(" <<x1<<","<<y1<<") = "<< i - 1 << "P + P = " << "(" << s.first << "," << s.second << ")" << endl;
	return pair<int, int>(s.first, s.second);
}
//Секретный ключ
std::pair<int, int> sec_key(int p, int a, int b, int x1, int y1, int c, int d) {
	auto A_key = skal(c, p, a, b, x1, y1);
	int check;
	check = preobr(pow(A_key.first, 3) + 2 * A_key.first + a,p);
	cout << "Проверка на принадлежность точки к кривой:\ny^2=x^3+ax+b" << endl;
	cout << preobr(pow(A_key.second, 2) << "=" <<check;

	if (preobr(pow(A_key.second, 2), p) != check) {
		cout << "Проверка на принадлежность точки к кривой не пройдена" << endl;
		return pair<int, int >(0, 0);
	}
	
	auto B_key = skal(d, p, a, b, x1, y1);
	auto AB_key = skal(c, p, a, b, B_key.first, B_key.second);
	auto BA_key = skal(d, p, a, b, A_key.first, A_key.second);
	//cout << "1:" << A_key.first << "," << A_key.second << endl;
	cout << "Секретный ключ = (" << AB_key.first << "," << AB_key.second << ")\n\n" ;
//	cout << "Секретный ключ = (" << BA_key.first << "," << BA_key.second << ")" << endl;
	return pair<int, int>(AB_key.first, AB_key.second);
}
int main()
{
	setlocale(LC_ALL, "Russian");

	int p, a, b, x1, y1, m, c, d;
	int x2, y2;
	int i;
	auto s = sum(1, 1, 1, 1, 1);
	while (true) {
		int vibor;
		cout << "1 - Сумма\n2 - Умножение\n3 - Порядок точки\n4 - Скалярное произведение точки\n5 - Секретный ключ\n6 - Выход" << endl;
		cin >> vibor;
		switch (vibor) {
			//Сумма
		case 1:
			cout << "Введите поле E, p = ";
			cin >> p;
			cout << "Введите a = ";
			cin >> a;
			cout << "Введите b = ";
			cin >> b;
			cout << "Введите базовую точку P, x1 = ";
			cin >> x1;
			cout << "Введите базовую точку P, y1 = ";
			cin >> y1;
			cout << "Введите базовую точку Q, x2 = ";
			cin >> x2;
			cout << "Введите базовую точку Q, y2 = ";
			cin >> y2;
			s = sum(p, x1, y1, x2, y2);
			cout << "P + Q = (" << s.first << "," << s.second << ")" << endl;
			break;
			//Умножение
		case 2:
			cout << "Введите поле E, p = ";
			cin >> p;
			cout << "Введите a = ";
			cin >> a;
			cout << "Введите b = ";
			cin >> b;
			cout << "Введите базовую точку P, x1 = ";
			cin >> x1;
			cout << "Введите базовую точку P, y1 = ";
			cin >> y1;
			s = mult(p, x1, y1, a);
			cout << "P + P = (" << s.first << "," << s.second << ")" << endl;
			break;
			//Порядок точки
		case 3:

			cout << "Введите поле E, p = ";
			cin >> p;
			cout << "Введите a = ";
			cin >> a;
			cout << "Введите b = ";
			cin >> b;
			cout << "Введите базовую точку P, x1 = ";
			cin >> x1;
			cout << "Введите базовую точку P, y1 = ";
			cin >> y1;
			i = 2;
			s = mult(p, x1, y1, a);
			cout << "2P = P + P = (" << s.first << "," << s.second << ")" << endl;
			while (s.first != 0 || s.second != 0) {
				i = i++;
				s = sum(p, x1, y1, s.first, s.second);
				cout << i << "P = " << i - 1 << "P + P = " << "(" << s.first << "," << s.second << ")" << endl;
			}
			//cout << i << "P = " << i - 1 << "P + P = " << "(oo)" << endl;
			cout << "Порядок точки = " << i << endl;
			break;
			//скалярное произведение
		case 4:
			cout << "Введите число m = ";
			cin >> m;
			cout << "Введите поле E, p = ";
			cin >> p;
			cout << "Введите a = ";
			cin >> a;
			cout << "Введите b = ";
			cin >> b;
			cout << "Введите базовую точку P, x1 = ";
			cin >> x1;
			cout << "Введите базовую точку P, y1 = ";
			cin >> y1;
			skal(m, p, a, b, x1, y1);
			break;
			//секретный ключ
		case 5:
			cout << "Введите поле E, p = ";
			cin >> p;
			cout << "Введите a = ";
			cin >> a;
			cout << "Введите b = ";
			cin >> b;
			cout << "Введите базовую точку P, x1 = ";
			cin >> x1;
			cout << "Введите базовую точку P, y1 = ";
			cin >> y1;
			cout << "Введите число пользователя A c = ";
			cin >> c;
			cout << "Введите число пользователя B d = ";
			cin >> d;
			sec_key(p, a, b, x1, y1, c, d);

			break;
		case 6:
			exit(1);
			break;
		default:
			cout << "Такой функции нету" << endl;
			break;
		}
	}
}
