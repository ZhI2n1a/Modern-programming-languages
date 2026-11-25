// stroka.h — класс Stroka (строка как стандартный тип) с потоковым вводом-выводом
#ifndef STROKA_H
#define STROKA_H

#include <iostream>
#include <cstring>

class Stroka {
    char *str;      // указатель на символы строки (динамический буфер)
    int  kapasitet; // ёмкость буфера (выделенная память)
    int  len;       // текущая длина строки (без нуль-символа)
    // --- собственные функции работы со строками (из лабораторной работы 4) ---
    static int  m_strlen(const char *s);               // длина строки
    static void m_strcpy(char *dest, const char *src); // копирование
    static void m_strcat(char *dest, const char *src); // сцепление
    static int  m_strcmp(const char *a, const char *b);// сравнение
public:
    Stroka();                          // конструктор по умолчанию
    Stroka(const char *s);             // конструктор из C-строки
    Stroka(const Stroka &obj);         // конструктор копирования
    Stroka(int size);                  // конструктор с заданным размером памяти
    ~Stroka();                         // деструктор — освобождает буфер

    int dlina() const;                 // длина строки
    const char* get_str() const;       // доступ к внутреннему буферу (только чтение)

    Stroka& operator = (const Stroka &obj);        // присваивание
    Stroka  operator + (const Stroka &obj) const;  // сцепление
    int     operator == (const Stroka &obj) const; // сравнение

    // ---- потоковый ввод-вывод (лабораторная работа 8) ----
    // оператор вывода объявляется дружественным, т.к. слева стоит поток, а не объект
    friend std::ostream& operator << (std::ostream &os, const Stroka &s);
    // оператор ввода: читает слово до пробельного символа (аналог cin >> для char*)
    friend std::istream& operator >> (std::istream &is, Stroka &s);
    // метод ввода строки целиком с клавиатуры (до конца строки)
    void vvod(std::istream &is);
};

#endif
