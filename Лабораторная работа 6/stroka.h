// stroka.h - opisanie klassa Stroka (laba 6)
#ifndef STROKA_H
#define STROKA_H
#include <iostream>
using namespace std;

class Stroka {
    char *str;   // ukazatel na simvoly stroki
    int   cap;   // emkost buféra (vydelennaya pamyat)
    int   len;   // tekuschaya dlina stroki
public:
    Stroka();                          // konstruktor po umolchaniyu
    Stroka(const char *s);             // konstruktor iz C-stroki
    Stroka(const Stroka &obj);         // konstruktor kopirovaniya
    Stroka(int size);                  // s zadannym razmerom pamyati (p.4)
    ~Stroka();                         // destruktor
    Stroka &operator=(const Stroka &obj); // prisvaivanie
    Stroka operator+(const Stroka &obj) const; // sceplenie
    bool operator==(const Stroka &obj) const;  // sravnenie
    int  dlina() const;                // dlina stroki
    void vvod();                       // vvod stroki
    void vyvod() const;                // vyvod stroki
private:
    // sobstvennye funkci iz labi 4 vmesto string.h
    static int  m_strlen(const char *s);
    static int  m_strcmp(const char *a, const char *b);
    static void m_strcpy(char *dst, const char *src);
    static void m_strcat(char *dst, const char *src);
};
#endif
