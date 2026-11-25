
// Лабораторная работа 1, задание 3
// Обмен значениями двух переменных: int, int* и int&
#include <iostream>
using namespace std;

void obmen1(int a, int b)   // передача по значению
{
    int t = a;
    a = b;
    b = t;
}                           // копии поменялись, оригиналы — нет

void obmen2(int *a, int *b) // передача указателей
{
    int t = *a;
    *a = *b;
    *b = t;
}

void obmen3(int &a, int &b) // передача по ссылке
{
    int t = a;
    a = b;
    b = t;
}

int main()
{
    int a = 2, b = 5;

    cout << "do obmena:      a = " << a << ", b = " << b << endl;

    obmen1(a, b);
    cout << "posle obmena 1: a = " << a << ", b = " << b << endl;

    obmen2(&a, &b);
    cout << "posle obmena 2: a = " << a << ", b = " << b << endl;

    obmen3(a, b);
    cout << "posle obmena 3: a = " << a << ", b = " << b << endl;

    return 0;
}
