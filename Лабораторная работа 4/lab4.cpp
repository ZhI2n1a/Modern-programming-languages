
// Лабораторная работа 4. Обработка строковых данных.
// Все пункты задания в одной программе; каждый пункт помечен разделителем.

#include <iostream>
#include <cstring>      // библиотечные функции strlen, strcat, strcpy, strcmp
#include <cstdlib>      // malloc, calloc, free
#include <cstdio>

using namespace std;

// ---------- Пункт 2. Собственные варианты функций ----------

// 1-й способ: длина строки по индексам
int my_strlen_index(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;   // идём до нуль-символа
    return i;
}

// 2-й способ: длина строки через указатель (s не меняется, работаем с копией)
int my_strlen_ptr(const char* s) {
    const char* p = s;
    while (*p != '\0') p++;     // сдвигаем копию указателя до '\0'
    return p - s;               // разность указателей = число символов
}

// 3-й способ: длина строки рекурсивно
int my_strlen_rec(const char* s) {
    if (*s == '\0') return 0;               // пустая строка - длина 0
    return 1 + my_strlen_rec(s + 1);        // 1 символ + длина остатка
}

// Копирование строки: src копируется в dest, включая '\0'; возвращается dest
char* my_strcpy(char* dest, const char* src) {
    char* p = dest;                 // запоминаем начало, т.к. dest сдвинем
    while (*src != '\0') {          // копируем посимвольно до нуль-символа
        *p = *src;
        p++; src++;
    }
    *p = '\0';                      // не забываем завершающий символ
    return dest;
}

// Сравнение строк: возвращает 0 при равенстве,
// отрицательное число, если s1 < s2, положительное, если s1 > s2
int my_strcmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s1 == *s2) { // идём, пока символы равны
        s1++; s2++;
    }
    // дошли до первого несовпадающего символа (или до '\0' в одной из строк)
    return (unsigned char)*s1 - (unsigned char)*s2;
}

// Конкатенация: дописывает src в конец dest; возвращает dest
char* my_strcat(char* dest, const char* src) {
    char* p = dest;
    while (*p != '\0') p++;     // ищем конец строки dest
    while (*src != '\0') {      // переписываем туда src
        *p = *src;
        p++; src++;
    }
    *p = '\0';                  // новый нуль-символ в конце
    return dest;
}

// ---------- Пункт 3. Версии функций для динамической памяти ----------

// Копирование строки в динамический буфер, выделенный malloc
char* dyn_copy_malloc(const char* src) {
    char* p = (char*)malloc((strlen(src) + 1) * sizeof(char)); // +1 под '\0'
    if (p == NULL) { cout << "Ошибка выделения памяти!" << endl; exit(1); }
    strcpy(p, src);
    return p;
}

// Сравнение строк, память под которые выделялась динамически:
// та же логика, что и my_strcmp; отдельно оформлена для наглядности
int dyn_compare(const char* s1, const char* s2) {
    return my_strcmp(s1, s2);
}

// Соединение двух строк в НОВЫЙ динамический буфер (malloc)
char* dyn_join_malloc(const char* s1, const char* s2) {
    char* p = (char*)malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
    if (p == NULL) { cout << "Ошибка выделения памяти!" << endl; exit(1); }
    strcpy(p, s1);
    strcat(p, s2);
    return p;
}

// ---------- Пункт 4. Те же операции через calloc ----------

char* dyn_copy_calloc(const char* src) {
    // calloc получает не байты, а число элементов и размер одного элемента;
    // выделенная память ОБНУЛЯЕТСЯ, поэтому чистить её не нужно
    char* p = (char*)calloc(strlen(src) + 1, sizeof(char));
    if (p == NULL) { cout << "Ошибка выделения памяти!" << endl; exit(1); }
    strcpy(p, src);
    return p;
}

char* dyn_join_calloc(const char* s1, const char* s2) {
    char* p = (char*)calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));
    if (p == NULL) { cout << "Ошибка выделения памяти!" << endl; exit(1); }
    strcpy(p, s1);
    strcat(p, s2);
    return p;
}

int main() {
    // ---------- Пункт 1. Библиотечные функции ----------
    cout << "=== Пункт 1. Библиотечные функции string.h ===" << endl;
    char a[80] = "systems";
    char b[80] = "programming";
    char c[80];

    cout << "strlen(a) = " << strlen(a) << ", strlen(b) = " << strlen(b) << endl;

    strcpy(c, a);                       // c = a
    cout << "strcpy: c = " << c << endl;

    strcat(c, b);                       // c = a + b
    cout << "strcat: c = " << c << endl;

    cout << "strcmp(a, b) = " << strcmp(a, b) << " (a < b, буква s раньше p)" << endl;
    cout << "strcmp(a, a) = " << strcmp(a, a) << " (равны)" << endl;
    cout << "strcmp(b, a) = " << strcmp(b, a) << " (b > a)" << endl;

    // ---------- Пункт 2. Собственные функции ----------
    cout << "\n=== Пункт 2. Собственные варианты функций ===" << endl;
    char s[] = "laboratory work";
    cout << "Строка: \"" << s << "\"" << endl;
    cout << "длина (по индексам):   " << my_strlen_index(s) << endl;
    cout << "длина (по указателю):  " << my_strlen_ptr(s) << endl;
    cout << "длина (рекурсивно):    " << my_strlen_rec(s) << endl;

    char d[80];
    my_strcpy(d, s);
    cout << "копирование: \"" << d << "\"" << endl;

    char e[80] = " of system programming";
    my_strcat(d, e);
    cout << "конкатенация: \"" << d << "\"" << endl;

    cout << "сравнение \"" << s << "\" и \"" << e << "\" -> " << my_strcmp(s, e) << endl;
    cout << "сравнение \"abc\" и \"abd\" -> " << my_strcmp("abc", "abd") << endl;

    // ---------- Пункт 3. Динамическая память (malloc) ----------
    cout << "\n=== Пункт 3. Динамическая память, malloc ===" << endl;
    const char* base = "dynamic string";
    char* p1 = dyn_copy_malloc(base);
    cout << "копия в динамической памяти: \"" << p1 << "\" (длина "
         << my_strlen_ptr(p1) << ")" << endl;

    char* p2 = dyn_join_malloc("first + ", "second");
    cout << "соединение: \"" << p2 << "\"" << endl;
    cout << "сравнение копии и оригинала: " << dyn_compare(p1, base) << endl;

    free(p1);   // освобождаем память
    free(p2);

    // ---------- Пункт 4. Динамическая память (calloc) ----------
    cout << "\n=== Пункт 4. Динамическая память, calloc ===" << endl;
    char* q1 = dyn_copy_calloc(base);
    char* q2 = dyn_join_calloc("first + ", "second");
    cout << "копия: \"" << q1 << "\"" << endl;
    cout << "соединение: \"" << q2 << "\"" << endl;
    cout << "сравнение результатов malloc- и calloc-версий: "
         << dyn_compare(q2, "first + second") << endl;
    free(q1);
    free(q2);

    // ---------- Пункт 5. Массив строк ----------
    cout << "\n=== Пункт 5. Массив строк ===" << endl;
    // массив указателей на динамические строки
    const char* words[4] = {"dynamic", "string", "in", "C++"};
    char* arr[4];                       // копии строк в динамической памяти
    for (int i = 0; i < 4; i++)
        arr[i] = dyn_copy_calloc(words[i]);

    // применяем свои функции к каждой строке массива
    for (int i = 0; i < 4; i++)
        cout << "arr[" << i << "] = \"" << arr[i] << "\", длина = "
             << my_strlen_ptr(arr[i]) << endl;

    // сравнение соседних строк массива
    for (int i = 0; i < 3; i++)
        cout << "strcmp(arr[" << i << "], arr[" << i + 1 << "]) = "
             << my_strcmp(arr[i], arr[i + 1]) << endl;

    // конкатенация всех строк массива в одну
    char* all = (char*)calloc(100, sizeof(char));
    for (int i = 0; i < 4; i++) {
        my_strcat(all, arr[i]);
        if (i < 3) my_strcat(all, " ");
    }
    cout << "конкатенация всего массива: \"" << all << "\"" << endl;
    cout << "её длина: " << my_strlen_rec(all) << endl;

    for (int i = 0; i < 4; i++) free(arr[i]);
    free(all);

    return 0;
}
