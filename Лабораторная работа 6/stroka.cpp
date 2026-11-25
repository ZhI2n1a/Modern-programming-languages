// stroka.cpp - opredelenie metodov klassa Stroka
#include "stroka.h"

// ---- sobstvennye strokovye funkci (lab. 4) ----
int Stroka::m_strlen(const char *s) {          // dlina stroki
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}
int Stroka::m_strcmp(const char *a, const char *b) { // sravnenie
    while (*a != '\0' && *b != '\0' && *a == *b) { ++a; ++b; }
    return (unsigned char)*a - (unsigned char)*b;
}
void Stroka::m_strcpy(char *dst, const char *src) {  // kopirovanie
    while ((*dst++ = *src++) != '\0') { }
}
void Stroka::m_strcat(char *dst, const char *src) {  // konatenaciya
    while (*dst != '\0') dst++;
    while ((*dst++ = *src++) != '\0') { }
}

// ---- konstruktory ----
Stroka::Stroka() {                       // pustaya stroka
    str = new char[1]; str[0] = '\0'; cap = 1; len = 0;
}
Stroka::Stroka(const char *s) {          // iz C-stroki
    len = m_strlen(s);
    cap = len + 1;
    str = new char[cap];
    m_strcpy(str, s);
}
Stroka::Stroka(const Stroka &obj) {      // kopirovanie (glubokoe)
    len = obj.len; cap = obj.cap;
    str = new char[cap];
    m_strcpy(str, obj.str);
}
Stroka::Stroka(int size) {               // p.4: zadannyi razmer pamyati
    cap = size > 0 ? size : 1;
    str = new char[cap];
    str[0] = '\0'; len = 0;
}
Stroka::~Stroka() {                      // destruktor: osvobozhdenie pamyati
    delete[] str;
}

// ---- operacii ----
Stroka &Stroka::operator=(const Stroka &obj) {
    if (this == &obj) return *this;      // zashchita ot s = s
    delete[] str;                        // staryi bufer osvobozhdaetsya
    len = obj.len; cap = obj.cap;
    str = new char[cap];
    m_strcpy(str, obj.str);
    return *this;
}
Stroka Stroka::operator+(const Stroka &obj) const {
    Stroka tmp(len + obj.len + 1);       // +1 pod nul-simvol!
    m_strcpy(tmp.str, str);
    m_strcat(tmp.str, obj.str);
    tmp.len = len + obj.len;
    return tmp;
}
bool Stroka::operator==(const Stroka &obj) const {
    if (len != obj.len) return false;
    return m_strcmp(str, obj.str) == 0;
}

// ---- metody ----
int Stroka::dlina() const { return len; }

void Stroka::vvod() {                    // vvod s ogranicheniem cap
    cin.getline(str, cap);
    len = m_strlen(str);
}
void Stroka::vyvod() const {
    cout << str;
}
