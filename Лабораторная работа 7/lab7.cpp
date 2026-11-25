
// =====================================================================
// Лабораторная работа 7. Перевод программы с Паскаля на С++
// Наследование, виртуальные функции: Point -> Krug -> Ring
// Дополнение (п.2): SetCvet и Sektor + смена цвета и сектора
// одновременно с перемещением (виртуальный хук Izmenenie)
// Графическая библиотека Borland эмулируется (graph_emu.h)
// =====================================================================
#include "graph_emu.h"
#include "conio_emu.h"
#include <cstdlib>

// ================== Базовый класс Point ==================
class Point {
protected:
    int X, Y;      // координаты фигуры
    int Cvet;      // цвет фигуры
public:
    Point() : X(0), Y(0), Cvet(0) {}
    virtual ~Point() {}
    void Init(int x, int y) { X = x; Y = y; }
    int  GetX() const { return X; }
    int  GetY() const { return Y; }
    void SetCvet(int c) { Cvet = c; }
    virtual void Show() {}        // виртуальные методы-заглушки:
    virtual void Hide() {}        // переопределяются в наследниках
    virtual void Izmenenie() {}   // хук: смена вида при перемещении
    void Fly(int &Xl, int &Yl);   // перемещение со случайным шагом
};

// Перемещение: аналог Паскаль-процедуры Fly(Xl, Yl: integer)
void Point::Fly(int &Xl, int &Yl) {
    int dx = (rand() % 9 - 4) * 10;   // случайный шаг по X, пиксели
    int dy = (rand() % 9 - 4) * 10;   // случайный шаг по Y, пиксели
    Hide();                           // стереть фигуру (виртуальный вызов)
    if (X + dx < 0 || X + dx > SCREEN_W - 1) dx = -dx;  // не выходить за экран
    if (Y + dy < 0 || Y + dy > SCREEN_H - 1) dy = -dy;
    X += dx; Y += dy;
    Izmenenie();                      // смена цвета/сектора (полиморфизм)
    Show();                           // нарисовать на новом месте
    Xl = X; Yl = Y;                   // параметры-результаты (аналог Var)
}

// ================== Класс Krug (наследник Point) ==================
class Krug : public Point {
protected:
    int Radius;             // радиус круга
    static int u1, u2;      // границы вырезанного сектора (общие для фигур)
public:
    void Init(int x, int y, int r, int c) {
        Point::Init(x, y);            // аналог inherited Init
        Radius = r; Cvet = c;
    }
    void Show();
    void Hide();
    void Sektor(int a1, int a2) { u1 = a1; u2 = a2; }  // задать сектор
    void Izmenenie();             // смена цвета и сужение-расширение сектора
};
int Krug::u1 = 320, Krug::u2 = 40;

void Krug::Show() {               // круг с вырезанным сектором u1..u2
    setfillstyle(SOLID_FILL, Cvet);
    setcolor(Cvet);
    pieslice(X, Y, u2, u1, Radius);   // заливка от u2 до u1: 320 градусов
}
void Krug::Hide() {               // стереть круг цветом фона
    setfillstyle(SOLID_FILL, 0);
    setcolor(0);
    pieslice(X, Y, 0, 360, Radius);
}
// Дополнение (п.2): цвет и границы сектора меняются при каждом шаге
void Krug::Izmenenie() {
    static int shag = 0; shag++;
    const int cv[4] = { 4, 5, 6, 3 };                  // цикл цветов
    Cvet = cv[shag % 4];
    u1 = (320 - (shag % 3) * 10 + 360) % 360;          // начало выреза
    u2 = (u1 + 40 - 10 * (shag % 3) + 360) % 360;      // ширина выреза 40/30/20
}

// ================== Класс Ring (наследник Krug) ==================
class Ring : public Krug {
protected:
    int Width;             // ширина кольца
public:
    void Init(int x, int y, int r, int c, int w) {
        Krug::Init(x, y, r, c);       // аналог inherited Init
        Width = w;
    }
    void Show();                      // своя отрисовка кольца
};
void Ring::Show() {
    setcolor(Cvet);                   // внешняя и внутренняя окружности
    circle(X, Y, Radius);
    circle(X, Y, Radius - Width);
    setcolor(0);                      // вырез сектора цветом фона
    setfillstyle(SOLID_FILL, 0);
    pieslice(X, Y, u1, u2, Radius);
}

// ================== Главная функция ==================
int main() {
    srand(42);                        // фиксированное зерно: воспроизводимый прогон
    int gdriver = 0, gmode = 0;
    initgraph(&gdriver, &gmode, (char*)"");
    conio_init();                     // эмуляция: нажатия клавиш берутся из stdin

    Krug kr;  Ring ring;
    kr.Init(200, 140, 45, 4);         // круг в позиции (200,140)
    kr.Sektor(320, 40);               // вырезанный сектор 320..40
    ring.Init(430, 300, 60, 3, 10);   // кольцо в позиции (430,300)
    kr.Show();  ring.Show();  delay(400);   // начальный кадр

    int Xl = 0, Yl = 0;
    do {                              // аналог Repeat..Until
        while (!keypressed()) { }     // ожидание нажатия клавиши
        int c = getch();
        if (c == 27) break;           // Esc — конец работы
        kr.Fly(Xl, Yl);               // перемещение обеих фигур;
        ring.Fly(Xl, Yl);             // виртуальные Show/Hide/Izmenenie
        delay(400);                   // отрисовать кадр
    } while (true);
    getch();
    closegraph();
    return 0;
}
