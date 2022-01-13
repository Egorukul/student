#include <iostream>
#include <string>

using namespace std;
const int n = 26;

string text_input(char alph[n]) {
	string text;
	int need_add;
	int flag = 1;
	cout << "Введите текст: ";
	cin.ignore(100, '\n');
	while (flag == 1) {
		flag = 0;
		getline(cin, text);

		//Удаление пробелов 
		for (int i = text.length(); i > 0; i--) {
			if (text[i] == ' ')
				text.erase(i, 1);
		}
		//Добавление до нужного размера
		need_add = 3 - (text.length() % 3);
		if (need_add !=3) {
			for (int i = 0; i < need_add; i++) {
				text = text + 'z';
			}
		}
		//Преобразование текст а в верхний регистр
		for (int i = 0; i < text.length(); i++)
			text[i] = toupper(text[i]);
		//Проверка на недоступные символы
		for (int i = 0; i < text.length(); i++)
		{
			for (int j = 0; j < n; j++) {
				if (text[i] == alph[j]) {
					flag = 0;
					break;
				}
				else
				{
					flag == 1;
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
string shifr(string text,int key[3][3],char alph[n]) {
	//int *shifr_matrix = new int[text.length()];
	string shifr;
	int elem;
	int *matrix = new int[text.length()];
	int len = text.length() / 3;
	//Заполнения матрицы текста
	for (int i = 0; i < text.length(); i++) {
		for (int j = 0; j < n; j++) {
			if (text[i] == alph[j]) {
				matrix[i] = j;
			}
		}
	}
	//Вывод
	for (int i = 0; i < text.length(); i++) {
		if (i % len==0)
			cout << endl;
		cout << text[i];
	}	
	cout << endl;

	//Шифрование
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < len; j++) {
			elem = 0;
			for (int z = 0; z < 3; z++) {
				elem = elem + key[i][z] * matrix[j + len * z];


			}
			shifr = shifr + alph[elem % 26];
		}
	cout << "\nShifr = " << shifr << "\n";
	return shifr;
}

string decr(string text,int back_key[3][3],char alph[n]) {
	string ishod;
	int elem;
	int* matrix = new int[text.length()];
	int len = text.length() / 3;
	//Заполнение матрицы с текстом
	for (int i = 0; i < text.length(); i++) {
		for (int j = 0; j < n; j++) {
			if (text[i] == alph[j]) {
				matrix[i] = j;
			}
		}
	}

	//Вывод
	for (int i = 0; i < text.length(); i++) {
		if (i % len == 0)
			cout << endl;
		cout << text[i];
	}
	//Дешифрование
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < len; j++) {
			elem = 0;
			for (int z = 0; z < 3; z++) {
				elem = elem + back_key[i][z] * matrix[j + len * z];

			}
			ishod = ishod + alph[elem % 26];
		}
	cout << "\nShifr = " << ishod << "\n";
	return ishod;

}

int main()
{
	setlocale(LC_ALL, "russian");
	char alph[n];
	int key[3][3] = { {2,3,7},{5,7,9},{1,2,11} };
	//int back_key[3][3] = { {59,-19,-22},{-46,15,17},{3,-1,-1} };
	int back_key_1[3][3] = { {7,7,4},{6,15,17},{3,25,25} };

	int vibor;
	string text;

	//Заполнение и вывод алфавита
	cout << "Алфавит" << endl;
	for (int i = 0; i < n; i++) {
		alph[i] = char(65 + i);
		cout << alph[i] << " ";
	}
	cout << endl;

	//Вывод ключа
	cout << "Ключ:" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << key[i][j] << "  ";
		}
		cout << endl;
	}

	while (true) {
		cout << "Шифрование - 1\nДешифрование - 2\nВыход - 3\n\n";
		cin >> vibor;
		
		switch (vibor) {
		case 1:
			text = text_input(alph);
			shifr(text, key, alph);

			break;
		case 2:
			text = text_input(alph);
			decr(text, back_key_1, alph);

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
