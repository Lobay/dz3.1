#include<iostream>
#include<string>
#include<cstring>
#include<locale>
#include<cstdlib>
#include<fstream>
using namespace std;

void cr(int**& c, int& a, int& b, int argc, char* argv[]){
    int i, j, n, d;
    n = 2;
    string x, y, prom;
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
    if(argc==3) {
	string prom;
	d=0;
	for ( i = 0; i < a; i++ )
		for ( j = 0; j < b; j++) {
			for(; d<strlen(argv[2]); d++) {
				if( argv[2][d]>='0' && argv[2][d]<='9' ) {
					prom = argv[2][d];
					c[i][j] = c[i][j]*10+atoi( prom.c_str() );
				}else if(argv[2][d] == ','){
				    d++;
				    break;
				}

			}
		}
}
    for ( i = 0; i < a; i++ )
        for ( j = 0; j < b; j++, n++ ){
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

void out( int**c, int a, int b){
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++)
            cout << c[i][j] << " ";
        cout<< endl;}
}

void add(int**&c, int a, int b)
{
    int dopmat, i, j;
    cout << "Введите матрицу " << a << "x" << b << endl;
    for(i = 0; i < a; i++){
        for(j = 0; j < b; j++){
        cin >> dopmat;
        c[i][j] = c[i][j] + dopmat;}
    }
    cout << endl;
    for( i=0; i < a; i++){
        for(j=0; j < b; j++){
        cout << c[i][j] << " ";}
    cout << endl;
    }
}

void mul(int**&c, int a, int b)
{
    int i, j, s, m, n;
    string x, x1, x2;
    cout << "Ведите размер матрицы" << endl;
    cin >> x;
    for( i=0; x[i] != 'x' && x[i] != 'X'; i++){
        x1 += x[i];
    }
    for( i += 1; i < x.length(); i++){
        x2 += x[i];
    }
    m = atoi (x1.c_str());
    n = atoi (x2.c_str());
    if(b == m){
        cout << "Введите элементы матрицы" << endl;
        int **dopmat1;
        dopmat1 = new int*[m];
        for( i=0; i < m; i++)
            dopmat1[i] = new int[n];
        for( i=0; i < m; i++)
            for( j=0; j < n; j++)
                cin >> dopmat1[i][j];
        int **dopmat2;
        dopmat2 = new int*[a];
        for( i=0; i < a; i++)
            dopmat2[i] = new int[n];
        for( i=0; i < a; i++)
            for( j=0; j < n; j++)
                dopmat2[i][j] = 0;
        for(i=0; i < a; i++){
            for(j=0; j < n; j++){
                for( s=0; s < m; s++)
                    dopmat2[i][j] += c[i][s] * dopmat1[s][j];}}
        cout << "Результат:" << endl;
        b = n;
        for( i=0; i < m; i++)
            delete[] dopmat1[i];
        delete[] dopmat1;
        for( i=0; i < a; i++)
            delete[] c[i];
        delete[] c;
        c = dopmat2;
        out(c, a, b);
    }
    else cout << "Неверный размер";
}

void tran(int**&c, int &a, int &b)
{
    int i, j;
    int **dopmat = nullptr;
    dopmat = new int*[b];
    for(i=0; i<b; i++)
    dopmat[i] = new int[a];
    for(i=0; i<b; i++)
        for(j=0; j<a; j++)
        dopmat[i][j] = c[j][i];
        for( i=0; i < a; i++)
            delete[] c[i];
        delete[] c;
    c= dopmat;
    swap( a, b );
}


void stf(int**c, int a, int b)
{
    int i, j;
    ofstream file ("matrix.txt");
    file << a << " " << b << endl;
    for( i=0; i < a; i++){
        for( j=0; j < b; j++)
        file << c[i][j] << " ";
        file << endl;
    }
    file.close();
}

void lff(int**&c, int &a, int &b)
{
    int i, j;
    ifstream fin("matrix.txt");
    if(fin.is_open()) {
        fin >> a >> b;
        if(c!=nullptr){
        for(int i=0;i<a;i++)
        delete []c[i];
        delete []c;
        }
        c = new int*[a];
        for ( i=0; i < a; i++)
        c[i] = new int[b];
        for( i=0; i<a; i++)
            for( j =0; j < b; j++)
            fin >> c[i][j];
        fin.close();
    }
    else cout << " Файл не найден ";
}

void sort(int**&c, int a, int b){
    int k, i, j;
    char ch;
    cout << "Введите порядок сортировки" << endl;
    cout << "s: Змейкой" << endl;
    cout << "e: Улиткой" << endl;
    cout << "a: Муравьём" << endl;
    int *mas = new int[a*b];
    for ( i=0, k=0; i < a; i++)
        for( j=0; j < b; j++, k++)
            mas[k] = c[i][j];
    for ( i=0; i < (a*b); i++)
        for( j=(i+1); j < (a*b); j++){
            if ( mas[i] > mas[j]){
                swap ( mas[i], mas[j] );
            }
        }
    cin >> ch;
    switch (ch){
        case 's' :{
        for( i=0, k=0; i < b; i++ )
            for( j=0; j < a; j++, k++ )
                c[j][i] = mas[k];
        for( i=0; i <(a/2); i++){
            for(j=0; j < b; j++){
                if((j%2) ==1){
                    swap( c[i][j], c[a-i-1][j]);
                }
            }
        }
        for( i=0; i < a; i++ ){
            for( j=0; j < b; j++ ){
                cout << c[i][j] << " ";
                }
            cout << endl;
            }
            break;
        }
        case 'e':{
            int x = a;
            int y = b;
            int ogr;
            int n = 0;
            int m = 0;
            int t = 0;
            while ( x > 0 && y > 0) {
                if ((((x+y) * 2) - 4) > 0 && x > 1 && y > 1)
                    ogr = (((x + y) * 2) - 4);
                else if ((((x + y) * 2) - 4) > 0 && x == 1)
                    ogr = y;
                else if ((((x + y) * 2) - 4) > 0 && y == 1)
                    ogr = x;
                else if ((((x + y) * 2) - 4) == 0)
                    ogr = 1;
                for ( int i = n, j = m, k = 0; k < ogr; k++){
                    if ( j < (b - 1) - m && i == n){
                        c[i][j] = mas [t];
                        j++;
                        t++;}
                    else if (i < (a - 1) - n && j == (b - 1) - m){
                        c[i][j] = mas[t];
                        i++;
                        t++;}
                    else if (j > m && i == (a - 1) - n){
                        c[i][j] = mas[t];
                        j--;
                        t++;}
                    else if (i > n && j == m){
                        c[i][j] = mas[t];
                        i--;
                        t++;}
                    else if (i == j && ogr == 1){
                        c[i][j] = mas[t];
                        j++;
                        t++;}
                    }
                    n++;
                    m++;
                    x = x-2;
                    y = y-2;
            }
            for (i=0; i < a; i++){
                for(j=0; j < b; j++){
                    cout << c[i][j] << " ";
                }
                cout << endl;
            }
            break;
        }
        case 'a' :{
            for (i=0, k=0; i < a; i++){
                for (j=0; j < b; j++, k++){
                    cout << mas[k] << " "; }
                cout << endl;
            }
            break;
        }
    }
    delete [] mas;
}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "Russian");
    int** c = nullptr;
    int a, b;
    int choise;
    if (argc<3){
    cout << "Hеверное количество элементов" << endl;
    return 0;}
    cr(c, a, b, argc, argv);
    while(true){
        menu();
        cin >> choise;
        switch (choise){
            case 1:
            out (c, a, b);
            break;
            case 2:
            add (c, a, b);
            break;
            case 3:
            mul (c, a, b);
            break;
            case 4:
            tran (c, a, b);
            break;
            case 5:
            stf (c, a, b);
            break;
            case 6:
            lff (c, a, b);
            break;
            case 7:
            sort (c, a, b);
            break;
            case 8:
            delete[] c;
            return 0;
            default:
                cout << " Неверная команда " << endl;
        }
    }
}
