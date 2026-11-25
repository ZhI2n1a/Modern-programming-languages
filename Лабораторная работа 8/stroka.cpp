// stroka.cpp — методы класса Stroka
#include "stroka.h"

// --- собственные функции работы со строками (из лабораторной работы 4) ---
// длина строки: подсчёт по индексам
int Stroka::m_strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;   // идём до нуль-символа
    return n;
}
// копирование строки из src в dest
void Stroka::m_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') { dest[i] = src[i]; i++; }
    dest[i] = '\0';                       // не забываем нуль-символ
}
// сцепление: дописываем src в конец dest
void Stroka::m_strcat(char *dest, const char *src) {
    m_strcpy(dest + m_strlen(dest), src);
}
// сравнение: оба символа читаются на каждой итерации, поэтому
// для равных строк корректно возвращается 0
int Stroka::m_strcmp(const char *a, const char *b) {
    unsigned char ca, cb;                 // беззнаковое сравнение кодов символов
    while ((ca = (unsigned char)*a) == (cb = (unsigned char)*b) && ca != 0) {
        a++; b++;                         // продвижение к следующему символу
    }
    return (int)ca - (int)cb;             // 0 при равенстве, знак — порядок строк
}

// --- конструкторы и деструктор ---
Stroka::Stroka() {                       // пустая строка с небольшим запасом
    kapasitet = 16;
    str = new char[kapasitet];
    str[0] = '\0';
    len = 0;
}
Stroka::Stroka(const char *s) {          // из C-строки
    len = m_strlen(s);
    kapasitet = len + 1;
    str = new char[kapasitet];
    m_strcpy(str, s);
}
Stroka::Stroka(const Stroka &obj) {      // копирование: своя память под копию
    len = obj.len;
    kapasitet = obj.kapasitet;
    str = new char[kapasitet];
    m_strcpy(str, obj.str);
}
Stroka::Stroka(int size) {               // буфер заранее заданного размера
    kapasitet = (size > 0 ? size : 1);
    str = new char[kapasitet];
    str[0] = '\0';
    len = 0;
}
Stroka::~Stroka() { delete[] str; }      // обязательный деструктор — память из new

int Stroka::dlina() const { return len; }
const char* Stroka::get_str() const { return str; }

// --- перегруженные операции ---
Stroka& Stroka::operator = (const Stroka &obj) {  // присваивание
    if (this == &obj) return *this;       // защита от s = s
    delete[] str;                         // освобождаем старую память
    len = obj.len;
    kapasitet = obj.kapasitet;
    str = new char[kapasitet];
    m_strcpy(str, obj.str);
    return *this;                         // возвращаем ссылку — цепочка s1=s2=s3
}
Stroka Stroka::operator + (const Stroka &obj) const { // сцепление
    Stroka tmp(len + obj.len + 1);        // буфер под обе строки плюс нуль-символ
    m_strcpy(tmp.str, str);
    m_strcat(tmp.str, obj.str);
    tmp.len = len + obj.len;
    return tmp;                           // временный объект (копия вернётся)
}
int Stroka::operator == (const Stroka &obj) const {   // сравнение
    return m_strcmp(str, obj.str) == 0;
}

// --- потоковые операции (новое в лабораторной работе 8) ---
std::ostream& operator << (std::ostream &os, const Stroka &s) {
    os << s.str;                          // выводим символы строки в поток
    return os;                            // возвращаем поток — цепочка a << b << c
}
std::istream& operator >> (std::istream &is, Stroka &s) {
    char buf[256];                        // временный буфер
    is >> buf;                            // читаем слово до пробела
    if (is) s = Stroka(buf);              // если чтение успешно — присваиваем
    return is;
}
void Stroka::vvod(std::istream &is) {     // ввод строки целиком
    char buf[256];
    is.getline(buf, 256);                 // до перевода строки
    *this = Stroka(buf);
}
