// ============================================================
// Лабораторная работа 10. Линейные списки и шаблоны классов
// Часть 1 - односвязный список (аналог программы из методички)
// Часть 2 - шаблон класса "односвязный линейный список"
// Часть 3 - автобусный парк на основе шаблонного списка
// ============================================================
#include <iostream>
#include <cstring>
using namespace std;

// ---------------- Часть 1. Односвязный список целых чисел ----------------

// Узел односвязного списка: поле данных и указатель на следующий узел
struct Node {
    int  key;    // поле данных (ключ)
    Node *next;  // указатель на следующий узел
};

// Создание первого узла списка.
// pbeg передаётся по адресу (Node *&): функция его изменяет
void first(Node *&pbeg, int k)
{
    pbeg = new Node;      // выделяем память под узел
    pbeg->key  = k;
    pbeg->next = 0;       // следующего узла пока нет
}

// Добавление узла в конец списка.
// pend передаётся по адресу: конец списка может измениться
void add(Node *&pbeg, Node *&pend, int k)
{
    Node *pv = new Node;  // новый узел
    pv->key  = k;
    pv->next = 0;         // новый узел становится последним
    if (pbeg == 0)        // список был пуст
        pbeg = pend = pv;
    else {                // связываем прежний конец с новым узлом
        pend->next = pv;
        pend = pv;        // новый узел становится концом списка
    }
}

// Поиск узла по ключу. Список не изменяется - указатель const
const Node *find(const Node *pbeg, int k)
{
    for (const Node *p = pbeg; p != 0; p = p->next)
        if (p->key == k) return p;   // нашли
    return 0;                        // не нашли
}

// Удаление узла с ключом k. Оба указателя передаются по адресу,
// потому что при удалении первого (последнего) узла они меняются
bool remove(Node *&pbeg, Node *&pend, int k)
{
    if (pbeg == 0) return false;          // пустой список - удалять нечего
    Node *prev = 0,                       // указатель на предыдущий узел
         *p    = pbeg;
    // ищем узел: пока не дошли до конца и ключ не совпал
    while (p != 0 && p->key != k) {
        prev = p;
        p    = p->next;
    }
    if (p == 0) return false;             // узел не найден

    if (p == pbeg) {                      // удаляется первый узел
        pbeg = p->next;                   // голову переносим на следующий
        if (pbeg == 0) pend = 0;          // список стал пустым
    } else {                              // удаление из середины или конца
        prev->next = p->next;             // обходим удаляемый узел
        if (p == pend) pend = prev;       // конец корректируется
    }
    delete p;                             // освобождаем память
    return true;
}

// Вывод списка. Список не изменяется - const указатель
void print(const Node *pbeg)
{
    for (const Node *p = pbeg; p != 0; p = p->next)
        cout << p->key << ' ';
    cout << endl;
}

// Демонстрация операций: аналог программы из методички для
// двусвязного списка, выполненный на односвязном
void demo_list()
{
    Node *pbeg = 0, *pend = 0;   // пустой список

    // начальное формирование: 5 чисел
    for (int i = 1; i <= 5; i++) add(pbeg, pend, i);
    cout << "Nachalny spisok:       "; print(pbeg);

    // добавление в конец
    add(pbeg, pend, 200);
    cout << "Posle dobavleniya 200: "; print(pbeg);

    // удаление из середины
    remove(pbeg, pend, 3);
    cout << "Posle udaleniya 3:      "; print(pbeg);

    // удаление из головы
    remove(pbeg, pend, 1);
    cout << "Posle udaleniya 1:      "; print(pbeg);

    // попытка удалить несуществующий ключ
    if (!remove(pbeg, pend, 999))
        cout << "Element 999 ne najden" << endl;

    // удаление всех элементов по одному
    while (pbeg != 0) remove(pbeg, pend, pbeg->key);
    cout << "Spisok pustoj:          "; print(pbeg);
}

// ---------------- Часть 2. Шаблон класса "односвязный список" ----------------

// Узел списка с полем данных произвольного типа
template <typename T>
struct TNode {
    T      data;   // поле данных
    TNode  *next;  // указатель на следующий узел
};

// Шаблон класса односвязного линейного списка
template <typename T>
class TList {
    TNode<T> *pbeg;   // указатель на начало списка
    TNode<T> *pend;   // указатель на конец списка
public:
    TList() : pbeg(0), pend(0) {}   // конструктор: пустой список

    // деструктор: освобождаем все узлы, иначе утечка памяти
    ~TList() {
        while (pbeg) {
            TNode<T> *p = pbeg->next;
            delete pbeg;
            pbeg = p;
        }
    }

    // добавление элемента в конец списка
    void add(const T &x) {
        TNode<T> *pv = new TNode<T>;
        pv->data = x;
        pv->next = 0;
        if (!pbeg) pbeg = pend = pv;   // список был пуст
        else { pend->next = pv; pend = pv; }
    }

    // поиск элемента по ключу. Для сравнения требуется
    // перегруженная операция == у типа T
    const TNode<T> *find(const T &key) const {
        for (TNode<T> *p = pbeg; p != 0; p = p->next)
            if (p->data == key) return p;
        return 0;
    }

    // удаление элемента с ключом key. Возвращает true, если удалён
    bool remove(const T &key) {
        TNode<T> *prev = 0, *p = pbeg;
        while (p != 0 && !(p->data == key)) {   // ищем узел и его соседа
            prev = p;
            p    = p->next;
        }
        if (p == 0) return false;               // не найден
        if (p == pbeg) {                        // удаление первого узла
            pbeg = p->next;
            if (pbeg == 0) pend = 0;
        } else {                                // из середины или конца
            prev->next = p->next;
            if (p == pend) pend = prev;
        }
        delete p;
        return true;
    }

    bool empty() const { return pbeg == 0; }    // список пуст?

    // вывод списка: для T требуется operator<<
    void print(ostream &out = cout) const {
        for (TNode<T> *p = pbeg; p != 0; p = p->next) out << p->data << ' ';
        out << endl;
    }
};

// Тип пользователя для демонстрации шаблона
struct Man {
    char   fio[32];   // фамилия
    double oklad;     // оклад
    Man(const char *f = "", double o = 0) : oklad(o) {
        strncpy(fio, f, sizeof(fio) - 1);
        fio[sizeof(fio) - 1] = 0;
    }
    // сравнение по фамилии (по ключу)
    bool operator==(const Man &m) const { return strcmp(fio, m.fio) == 0; }
};

ostream &operator<<(ostream &out, const Man &m)
{ return out << m.fio << " (" << m.oklad << ")"; }

// Демонстрация шаблона TList для двух типов: int и Man
void demo_template()
{
    TList<int> li;                        // представитель шаблона для int
    for (int i = 1; i <= 5; i++) li.add(i * 10);
    cout << "TList<int>:           "; li.print();
    li.remove(30);
    cout << "Posle udaleniya 30:   "; li.print();

    TList<Man> lm;                        // представитель шаблона для Man
    lm.add(Man("Ivanov",   25000));
    lm.add(Man("Petrov",   31000));
    lm.add(Man("Sidorov",  18000));
    cout << "TList<Man>:           "; lm.print();
    lm.remove(Man("Petrov"));
    cout << "Posle udaleniya:      "; lm.print();
    const TNode<Man> *p = lm.find(Man("Sidorov"));
    if (p) cout << "Najdeno:              " << p->data << endl;
}

// ---------------- Часть 3. Автобусный парк ----------------

// Сведения об автобусе
struct Bus {
    int  num;        // номер автобуса
    char fio[40];    // фамилия и инициалы водителя
    int  route;      // номер маршрута
    Bus() {}
    Bus(int n, const char *f, int r) : num(n), route(r) {
        strncpy(fio, f, sizeof(fio) - 1);
        fio[sizeof(fio) - 1] = 0;
    }
    // автобусы отождествляются по номеру
    bool operator==(const Bus &b) const { return num == b.num; }
};

ostream &operator<<(ostream &out, const Bus &b)
{ return out << "Nomer " << b.num << ", voditel: " << b.fio
             << ", marshrut: " << b.route; }

void print_menu()
{
    cout << "\n1 - nachalnoe formirovanie   2 - avtobus vyezzhaet" << endl;
    cout << "3 - avtobus vuezhaet         4 - vyvod parna"      << endl;
    cout << "5 - vyvod marshrutov         0 - vyhod"            << endl;
}

int main()
{
    demo_list();        // часть 1: односвязный список int
    demo_template();    // часть 2: шаблон класса TList<T>

    // ---------------- часть 3: автобусный парк ----------------
    TList<Bus> park, route;   // два списка: в парке и на маршруте
    int cmd;
    for (;;) {
        print_menu();
        if (!(cin >> cmd)) {           // защита от некорректного ввода:
            cout << "Oshibka vvoda" << endl; break; }
        cout << "> komanda " << cmd << endl;
        if (cmd == 0) break;
        switch (cmd) {
        case 1: {  // начальное формирование данных обо всех автобусах
            int n;
            cout << "Kolichestvo avtobusov: ";
            cin >> n;  cout << "> n = " << n << endl;
            for (int i = 0; i < n; i++) {
                int nu, rt; char fio[40];
                cout << "nomer voditel marshrut: ";
                cin >> nu >> fio >> rt;
                cout << "> " << nu << ' ' << fio << ' ' << rt << endl;
                park.add(Bus(nu, fio, rt));
            }
            break;
        }
        case 2: {  // выезд автобуса из парка
            int nu;
            cout << "Nomer avtobusa: ";
            cin >> nu;  cout << "> nomer " << nu << endl;
            Bus key(nu, "", 0);              // запись-ключ (сравнение по номеру)
            const TNode<Bus> *p = park.find(key);
            if (p == 0)
                cout << "Avtobusa " << nu << " v parke net" << endl;
            else {
                route.add(p->data);          // запись переезжает в список маршрутов
                park.remove(key);            // и удаляется из списка парка
                cout << "Avtobus " << nu << " vyezzhaet na marshrut" << endl;
            }
            break;
        }
        case 3: {  // въезд автобуса в парк
            int nu;
            cout << "Nomer avtobusa: ";
            cin >> nu;  cout << "> nomer " << nu << endl;
            Bus key(nu, "", 0);
            const TNode<Bus> *p = route.find(key);
            if (p == 0)
                cout << "Avtobusa " << nu << " na marshrute net" << endl;
            else {
                park.add(p->data);           // запись возвращается в парк
                route.remove(key);           // и удаляется из списка маршрутов
                cout << "Avtobus " << nu << " vozvrashaetsya v park" << endl;
            }
            break;
        }
        case 4:
            cout << "Avtobusy v parke:" << endl;
            park.print();
            break;
        case 5:
            cout << "Avtobusy na marshrute:" << endl;
            route.print();
            break;
        default:
            cout << "Neizvestnaya komanda" << endl;
        }
    }
    // при выходе срабатывают деструкторы TList - вся память освобождена
    return 0;
}
