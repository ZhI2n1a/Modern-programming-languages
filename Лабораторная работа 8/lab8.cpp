// lab8.cpp — лабораторная работа 8: классы потоков языка C++
// Компиляция: g++ lab8.cpp stroka.cpp -o lab8
#include "stroka.h"
#include <fstream>
#include <sstream>
using namespace std;

// ============ Пункт 2: программы из «Классов потоков» ============
// Метод. указания [11] в распоряжении отсутствуют, поэтому приведены
// типовые программы, иллюстрирующие три раздела темы:
// файловые потоки (ifstream/ofstream), строковые потоки (stringstream)
// и флаги/методы управления состоянием потока.

// (2a) файловые потоки: запись и построчное чтение файла
void prog_file() {
    cout << "---- 2a. File streams ----" << endl;
    ofstream out("streams.txt");              // поток для записи
    out << "first line" << endl;
    out << "second line" << endl;
    out << "third line" << endl;
    out.close();                              // закрываем — данные на диске

    ifstream in("streams.txt");               // поток для чтения
    char line[80];
    int n = 0;
    while (in.getline(line, 80)) {            // читаем по строкам
        cout << "line " << ++n << ": " << line << endl;
    }
    in.close();
}

// (2b) строковые потоки: чтение и разбор прямо из буфера в памяти
void prog_stringstream() {
    cout << "---- 2b. String streams ----" << endl;
    stringstream ss("10 3.14 stream");        // поток над строкой
    int i; double d; char w[20];
    ss >> i >> d >> w;                        // извлекаем как из cin
    cout << "i=" << i << " d=" << d << " w=" << w << endl;
    // сборка строки обратно из значений
    ostringstream os;
    os << "sum=" << i + (int)d;
    cout << os.str() << endl;
}

// (2c) состояние потока: проверка и сброс флагов ошибок
void prog_state() {
    cout << "---- 2c. Stream state ----" << endl;
    ifstream in("no_such_file.txt");
    cout << "open missing file: fail=" << in.fail() << endl; // открыть не удалось
    in.clear();                               // сбрасываем флаги ошибок
    in.open("streams.txt");                   // пробуем существующий файл
    cout << "open streams.txt: good=" << in.good() << endl;
    in.close();
}

// ============ Пункт 3: шифратор из лабораторной работы 5 на потоках ============
// схему шифровки не меняем: c = c ^ key[i]; ключ используется циклически.
// (в лабе 5 применялись fopen/fgetc/fputc — здесь ifstream/ofstream)
void crypt_file(const char *src, const char *dst, const char *key) {
    ifstream in(src, ios::binary);            // двоичные потоки — как в лабе 5
    ofstream out(dst, ios::binary);
    int i = 0;
    char c;
    while (in.get(c)) {                       // чтение посимвольно
        c = (char)(c ^ key[i]);               // XOR с очередным символом ключа
        i++;                                  // циклическое использование ключа
        if (key[i] == '\0') i = 0;
        out.put(c);                           // запись посимвольно
    }
    in.close(); out.close();
}

// ============ Пункт 4: методы управления состоянием потока ============
void prog_format() {
    cout << "---- 4. Stream format methods ----" << endl;
    double x = 123.456789;
    cout.width(12);                           // ширина поля вывода
    cout.fill('*');                           // символ-заполнитель
    cout << x << endl;
    cout.precision(2);                        // точность вывода
    cout << x << " (precision 2)" << endl;
    cout.setf(ios::hex, ios::basefield);      // 16-ричный формат
    cout << 255 << " in hex" << endl;
    cout.unsetf(ios::hex);                    // отмена флага
    cout << 255 << " back to decimal" << endl;
    // флаги состояния при вводе: failbit устанавливается при ошибке чтения
    istringstream bad("abc");
    int v = 0;
    bad >> v;
    cout << "read 'abc' as int: fail=" << bad.fail();
    bad.clear();                              // сброс флагов — поток снова рабочий
    cout << " -> after clear: good=" << bad.good() << endl;
}

int main() {
    // ============ Пункт 1: потоковый ввод-вывод объектов Stroka ============
    cout << "== 1. Stroka stream operators ==" << endl;
    Stroka s1("laboratory"), s2(" work"), s3;
    cout << "s1 = " << s1 << ", len " << s1.dlina() << endl; // вывод через <<
    s3 = s1 + s2;                             // сцепление
    cout << "s1+s2 = " << s3 << endl;

    Stroka s4;
    cout << "enter word: ";                   // ввод через >>
    cin >> s4;
    cout << "you entered: " << s4 << ", len " << s4.dlina() << endl;
    cin.ignore(1024, '\n');                   // чистим буфер перед getline

    Stroka s5;
    cout << "enter line: ";                   // ввод строки целиком
    s5.vvod(cin);
    cout << "you entered: " << s5 << endl;

    cout << (s1 == Stroka("laboratory") ? "s1 == 'laboratory'" : "s1 differs") << endl;

    // ============ Пункт 2 ============
    prog_file();
    prog_stringstream();
    prog_state();

    // ============ Пункт 3: шифратор на потоках ============
    cout << "== 3. Crypter on streams ==" << endl;
    const char *msg = "plain text for stream crypter";
    { ofstream out("plain.txt", ios::binary); out << msg; }
    crypt_file("plain.txt", "enc.dat", "secret");   // шифруем
    crypt_file("enc.dat",  "dec.txt", "secret");    // расшифровываем тем же ключом
    // проверка: расшифрованный файл должен совпасть с исходным
    ifstream a("plain.txt", ios::binary), b("dec.txt", ios::binary);
    char ca, cb; int diff = 0; long cnt = 0;
    while (a.get(ca)) { if (!b.get(cb) || ca != cb) { diff = 1; break; } cnt++; }
    if (b.get(cb)) diff = 1;
    cout << "decrypted == original: " << (diff ? "NO" : "YES")
         << " (" << cnt << " bytes)" << endl;
    a.close(); b.close();

    // ============ Пункт 4 ============
    prog_format();
    return 0;
}
