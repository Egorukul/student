#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int n = 26;
int nod(int x, int y) {
	return y ? nod(y, x % y) : x;
}
int preobr(int i) {
	if (i % n >= 0) { // Если число больше 0 как остаток от деления на n
		i = i % 26;
	}
	else if (i % n < 0) { //Если число меньше 0 как остаток от деления на n 
		while (i < 0)
			i = i + n;
	}
	return i;
}
string vvod_text(char alph[n]) {
	//Ввод текста 
	string text;
	int flag = 1;
	cout << "Введите текст: ";
	cin.ignore();
	while (flag == 1) {
		flag = 0;
		getline(cin, text);

		//Удаление пробелов
		for (int i = text.length(); i > 0; i--) {
			if (text[i] == ' ')
				text.erase(i, 1);
		}
		//Преобразование текста в верхний регистр
		for (int i = 0; i < text.length(); i++)
			text[i] = toupper(text[i]);
		//Проверка на ввод
		for (int i = 0; i < text.length(); i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (text[i] == alph[j])
				{
					flag = 0;
					break;
				}
				else
				{
					//cout << text[i];
					flag = 1;
				}
			}
			if (flag == 1) {
				cout << "Недопустимые символы" << endl;
				cout << "Введите текст заново: ";
				break;
			}
		}
	}
	return text;
}

int vvod_a() {
	//Ввод a
	int a;
	while (true) {
		cout << "Введите a = ";
		cin >> a;
		cin.ignore(100, '\n');
		a = preobr(a);
		//Проверка на недопустимые символы
		if (cin.fail()) {
			cin.clear();
			cin.ignore(30, '\n');
			cout << "Введено не число\n\n";
			continue;
		}

		if (nod(a, n) == 1) {
			break;
		}
		cout << "Число не подходит\n\n";
	}

	return a;
}

int vvod_b() {
	//Ввод b
	int b;
	while (true) {
		cout << "Введите b = ";
		cin >> b;
		cin.ignore(100, '\n');
		
		if (cin.fail()) {
			cin.clear();
			cin.ignore(30, '\n');
			cout << "Введено не число\n\n";
			continue;
		}
		b = preobr(b);
		break;
	}
	return b;
}

//Основная программа
int main()
{
	setlocale(LC_ALL, "russian");

	//Объявление переменных
	char alph[n];
	int a, a1, b, pos_x, pos_sh, vibor;
	string text, shifr, ishod;

	//Заполнение и вывод алфавита
	cout << "Алфавит" << endl;
	for (int i = 0; i < n; i++) {
		alph[i] = char(65 + i);
		cout << alph[i] << " ";
	}
	cout << endl;

	//Цикл
	while (true) {
		cout << "Шифрование - 1\nДешифрование - 2\nВыход - 3" << endl;
		cin >> vibor;
		switch (vibor) {
			//Выбор шифрования
		case 1:
			text = vvod_text(alph);
			a = vvod_a();
			b = vvod_b();
			shifr = "";
			//Функция шифрования
			for (int i = 0; i < text.length(); i++) {
				for (int j = 0; j < n; j++) {
					if (text[i] == alph[j])
						pos_x = j;
				}
				pos_sh = (a * pos_x + b) % n;
				shifr = shifr + alph[pos_sh];
				cout << pos_x << endl;
			}
			cout << "Шифр: " << shifr << "\n\n";
			break;

			//Выбор расшифрования	
		case 2:
			text = vvod_text(alph);
			a = vvod_a();
			b = vvod_b();
			ishod = "";
			//Обратный элемент в кольце по модулю
			for (int i = 1; i < n; i++) {
				if (a * i % n == 1) {
					a1 = i;
					break;
				}
			}

			//функция расшифрования
			cout << a1 << endl;
			for (int i = 0; i < text.length(); i++) {
				for (int j = 0; j < n; j++) {
					if (text[i] == alph[j]) {
						pos_x = j;
					}
				}
				pos_sh = (a1 * (pos_x + n - b)) % n;
				ishod = ishod + alph[pos_sh];
			}
			cout << "Исходный текст: " << ishod << "\n\n";
			break;

		case 3:
			exit(1);

		default:
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Такой функции нет" << endl;
			break;
		}
	}
}

