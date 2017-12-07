#include<iostream>
#include<string>
#include<cstring>
#include<locale>
#include<cstdlib>
using namespace std;

void cr(int**& c, int& a, int& b, int argc, char* argv[]){
    int i, j, n;
    n = 2;
    string x, y;
    for ( i=0; (argv[1][i] != 'x') && (argv[1][i] != 'X'); i++ )
        x += argv[1][i];
    for ( i += 1; i < strlen(argv[1]); i++ )
        y += argv[1][i];
    a = atoi(x.c_str());
    b = atoi(y.c_str());
    if ( a==0 || b==0 )
        cout << "Неверная матрица, повторите ввод" << endl;
    c = new int*[a];
    for ( i = 0; i < a; i++ )
        c[i] = new int [b];
    for ( i = 0; i < a; i++ )
        for ( j = 0; j < b; j++ )
            c[i][j]=0;
    for ( i = 0; i < a; i++ )
        for ( j = 0; j < b; j++, n++){
            if ( n < argc )
                c[i][j] = atoi( argv[n] );
        }
}

void menu(){
    cout << "Выберите одну из операций" << endl;
    cout << "1. Вывести матрицу" << endl;
    cout << "2. Сложить матрицу" << endl;
    cout << "3. Умножить матрицу" << endl;
    cout << "4. Транспонировать матрицу" << endl;
    cout << "5. Сохранить в файл" << endl;
    cout << "6. Загрузить из файла" << endl;
    cout << "7. Сортировать матрицу" << endl;
    cout << "8. завершить работу программы" << endl;
}

void out( int**&c, int a, int b){
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
            cout << c[i][j] << endl;
}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "Russian");
    int** c = nullptr;
    int a, b;
    int choise;
    cr(c, a, b, argc, argv);
    while(true){
        menu();
        cin >> choise;
        switch (choise){
            case 1:
            out (c, a, b);
            break;
        }
    }
}
