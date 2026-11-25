// Лабораторная работа 9. Шаблоны функций и шаблоны классов
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// ------------------------------------------------------------------
// Пункт 1. Шаблон функции Sort ("пузырёк") для массивов любого типа.
// Для типа T должна быть перегружена операция > (условие задачи).
// ------------------------------------------------------------------
template <class T>
void Sort(T* b, int n) {
    T tmp;                                   // временная переменная обмена
    for (int i = 0; i < n; ++i)              // число проходов
        for (int j = n - 1; j > i; --j)      // проход от конца к началу
            if (b[j - 1] > b[j]) {           // левый больше правого — обмен
                tmp = b[j];
                b[j] = b[j - 1];
                b[j - 1] = tmp;
            }
}

// Тип, определённый пользователем: запись о человеке.
// Шаблон Sort применим к нему, если перегрузить операцию >.
class Man {
    char name[15];
    int  salary;
public:
    Man() { name[0] = '\0'; salary = 0; }
    Man(const char* s, int sal) { strcpy(name, s); salary = sal; }
    // сравнение по фамилии (алфавитный порядок)
    int operator>(const Man& m) const { return strcmp(name, m.name) > 0; }
    friend ostream& operator<<(ostream& os, const Man& m);
};
ostream& operator<<(ostream& os, const Man& m) {
    os.setf(ios::left); os.width(12);
    os << m.name << " salary: " << m.salary;
    os.unsetf(ios::left);
    return os;
}

// ------------------------------------------------------------------
// Пункт 2а. Перегрузка шаблонов функций: одно имя — разные наборы
// параметров. Компилятор выбирает подходящий по списку аргументов.
// ------------------------------------------------------------------
template <class T>                        // версия для двух скаляров
T maxelem(T a, T b) { return (a > b) ? a : b; }

template <class T>                        // версия для массива
T maxelem(T* a, int n) {
    T m = a[0];
    for (int i = 1; i < n; ++i)
        if (a[i] > m) m = a[i];
    return m;
}

// ------------------------------------------------------------------
// Пункт 2б. Специализация шаблона: getmax обобщённого вида не годится
// для строк (сравнивались бы указатели), поэтому добавляется обычная
// функция с тем же именем и специфическими типами параметров.
// ------------------------------------------------------------------
template <class T>
T getmax(T a, T b) { return (a > b) ? a : b; }

char* getmax(char* a, char* b) {           // специализированная версия
    return (strcmp(a, b) > 0) ? a : b;     // сравнение содержимого строк
}

// ------------------------------------------------------------------
// Пункт 3. Шаблон класса TStack (стек на массиве заданного размера).
// Параметры шаблона: тип T и константа size.
// ------------------------------------------------------------------
template <class T, int size>
class TStack {
    T data[size];                          // массив для хранения элементов
    int top;                               // число элементов в стеке
public:
    TStack() : top(0) {}
    bool push(T x);                        // поместить элемент
    bool pop(T& x);                        // извлечь элемент
    bool peek(T& x) const;                 // просмотреть вершину без извлечения
    bool empty() const { return top == 0; }   // пуст?
    bool full()  const { return top == size; } // заполнен?
};

template <class T, int size>
bool TStack<T, size>::push(T x) {
    if (full()) return false;              // нет места — отказ
    data[top++] = x;                       // запись на вершину
    return true;
}

template <class T, int size>
bool TStack<T, size>::peek(T& x) const {
    if (empty()) return false;
    x = data[top - 1];                     // вершина стека
    return true;
}

template <class T, int size>
bool TStack<T, size>::pop(T& x) {
    if (empty()) return false;             // брать нечего — отказ
    x = data[--top];                       // элемент с вершины
    return true;
}

// ------------------------------------------------------------------
// Пункт 3 задания. Сортировка железнодорожного состава с использованием
// тупика (рис. 1 методички): вагоны входят в тупик один за другим,
// выходят в обратном порядке — поведение стека LIFO. Вход: 1 5 3,
// выход: 5 3 1. Используется шаблон класса TStack.
// ------------------------------------------------------------------
const int NCAR = 8;                        // ёмкость тупика

// Сортировка состава с использованием тупика (рис. 1 методички).
// Тупик работает как стек LIFO: вагон либо заезжает в тупик,
// либо вагон с вершины тупика выводится на магистраль.
// Правило выбора: выводить вагон с вершины можно только тогда,
// когда его номер не меньше самого большого номера среди вагонов,
// ещё не заехавших в тупик (rest[i]). Так состав получается
// упорядоченным по убыванию: вход 1 5 3 -> выход 5 3 1.
void sortTrain(const int* in, int n) {
    int rest[NCAR + 1];                    // rest[i] = max(in[i..n-1])
    rest[n] = 0;                           // за последним вагоном пути нет
    for (int i = n - 1; i >= 0; --i)       // суффиксные максимумы
        rest[i] = (in[i] > rest[i + 1]) ? in[i] : rest[i + 1];

    TStack<int, NCAR> deadEnd;             // тупик — шаблон класса TStack
    string out;                            // накопитель строки вывода
    int car, topCar, i = 0;
    cout << "  input:  ";
    for (int k = 0; k < n; ++k) cout << in[k] << ' ';
    cout << endl;
    while (i < n || !deadEnd.empty()) {
        if (i < n && (deadEnd.empty() ||
                      !deadEnd.peek(topCar) || topCar < rest[i])) {
            // вершина тупика меньше максимального из оставшихся —
            // выводить её рано, вагон заезжает в тупик
            if (!deadEnd.push(in[i])) {
                cout << "  tupik polon (vagon " << in[i]
                     << " ne vmeschilsya)" << endl;
                return;
            }
            ++i;
        } else {
            deadEnd.pop(car);              // вагон с вершины — на выход
            out += to_string(car) + ' ';
        }
    }
    cout << "  output: " << out << endl;
}

int main() {
    cout << "=== 1. Shablon Sort dlya standartnyh tipov i tipa Man ===" << endl;
    int    ai[] = { 3, 1, 5, 2, 4 };
    double ad[] = { 2.5, 1.1, 3.9, 0.7 };
    Sort(ai, 5);                           // представитель для int
    Sort(ad, 4);                           // представитель для double
    cout << "  int:    ";
    for (int i = 0; i < 5; ++i) cout << ai[i] << ' ';
    cout << "\n  double: ";
    for (int i = 0; i < 4; ++i) cout << ad[i] << ' ';

    Man m[4] = { Man("Ivanov", 30000), Man("Petrov", 25000),
                 Man("Sidorov", 40000), Man("Antonov", 20000) };
    Sort(m, 4);                            // представитель для Man
    cout << "\n  Man (po familiyam):" << endl;
    for (int i = 0; i < 4; ++i) cout << "    " << m[i] << endl;

    cout << "\n=== 2a. Peregruzka shablonov maxelem ===" << endl;
    int x = 10, y = 25;
    int arr[5] = { 4, 9, 2, 17, 6 };
    cout << "  maxelem(x, y)      = " << maxelem(x, y) << endl;
    cout << "  maxelem(arr, 5)    = " << maxelem(arr, 5) << endl;

    cout << "\n=== 2b. Specializaciya getmax dlya strok ===" << endl;
    char s1[] = "apple", s2[] = "orange";
    cout << "  getmax(41, 7)        = " << getmax(41, 7) << endl;
    cout << "  getmax(s1, s2)       = " << getmax(s1, s2) << endl;

    cout << "\n=== 3. Shablon klassa TStack ===" << endl;
    TStack<int, 10> st_int;                // стек целых чисел
    for (int i = 1; i <= 4; ++i) st_int.push(i * 11);
    cout << "  pop: ";
    int v;
    while (st_int.pop(v)) cout << v << ',';
    cout << endl;
    TStack<double, 5> st_dbl;              // тот же шаблон для double
    st_dbl.push(1.5); st_dbl.push(2.5);
    double d;
    while (st_dbl.pop(d)) cout << d << ' ';
    cout << endl;

    cout << "\n=== 3 zadaniya. Sortirovka sostava cherez tupik ===" << endl;
    int train1[3] = { 1, 5, 3 };           // пример из задания (рис. 1)
    int train2[6] = { 4, 2, 6, 1, 3, 5 };  // более длинный состав
    cout << " sostav 1:" << endl;
    sortTrain(train1, 3);
    cout << " sostav 2:" << endl;
    sortTrain(train2, 6);
    return 0;
}
