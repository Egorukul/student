#include <iostream>
#include <string>
using namespace std;
const int n = 26;

string input_text(char mas[n][n]) {
    string text;
    int flag = 1;
    while (flag == 1) {
        
        cin >> text;
        for (int i = 0; i < text.length(); i++)
            text[i] = toupper(text[i]);
  
        flag = 0;
        for (int i = 0; i < text.length(); i++) {
            for (int j = 0; j < n; j++) {
                if (text[i] == mas[0][j]) {
                    flag = 0;
                    break;
                }
                else {
                    flag = 1;
                }
            }
            if (flag == 1) {
                cout << "Введено неверное значение";
                cout << "Введите заново : ";
                break;
            }
        }
         
    }
    return text;
}

int main()
{
    setlocale(LC_ALL, "russian");
    int asic = 65;
    char mas[n][n];
    string text, key, shifr, full_key;
    int vibor,diff;
    //Матрица алфавита
    for (int i = 0; i < n; i++) {

        asic = asic + i;

        for (int j = 0; j < n; j++) {

            if (asic >= 91)
                asic = 65;
            mas[i][j] = char(asic);
            cout << mas[i][j] << " ";
            asic++;

        }
        asic = 65;
        cout << endl;
    }
    while (true) {
        cout << "1 - Шифрование\n2 - Дешиврование\n3 - Выход\n";
        cin >> vibor;
        switch (vibor) {
        case 1:
            shifr = "";
            cout << "Введите исходный текст: ";
            text = input_text(mas);
            cout << "Введите ключ: ";
            key = input_text(mas);

            diff = text.length() - key.length();
            //Key length = text length
            if (key.length() < text.length())
                for (int i = 0; i < diff; i++) {
                    key = key + key[i % key.length()];
                }
            else
                key.resize(text.length());

            for (int i = 0; i < text.length(); i++) {
                shifr = shifr + char(65 + (int(text[i]) + int(key[i])) % 26);
            }
            cout << shifr<<endl;
            break;
            
        case 2:
            shifr = "";
            cout << "Введите исходный текст: ";
            text = input_text(mas);
            cout << "Введите ключ: ";
            key = input_text(mas);

            diff = text.length() - key.length();
            //Key length = text length
            if (key.length() < text.length())
                for (int i = 0; i < diff; i++) {
                    key = key + key[i % key.length()];
                }
            else
                key.resize(text.length());

            for (int i = 0; i < text.length(); i++) {
                shifr = shifr + char(65 + (int(text[i]) +26- int(key[i])) % 26);
            }
            cout << shifr << endl;
            break;
        case 3:
            exit(1);
        default:
            cout << "Такой функции нет" << endl;
        }
       
    }
}
