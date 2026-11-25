// lab6.cpp - glavnaya funkciya
#include "stroka.h"

int main() {
    Stroka s1("laboratory");             // konstruktor iz C-stroki
    Stroka s2;                           // pustaya
    s2 = s1;                             // operator= (prisvaivanie)
    Stroka s3 = s1 + Stroka(" work");    // operator+ (sceplenie)

    cout << "=== Demonstracia klassa Stroka ===" << endl;
    cout << "s1 = "; s1.vyvod();
    cout << " (dlina " << s1.dlina() << ")" << endl;
    cout << "posle prisvaivaniya: s2 = "; s2.vyvod();
    cout << " (dlina " << s2.dlina() << ")" << endl;
    cout << "s3 = s1 + \" work\": "; s3.vyvod();
    cout << " (dlina " << s3.dlina() << ")" << endl;

    cout << "s1 == s2 : " << (s1 == s2 ? "ravny" : "ne ravny") << endl;
    cout << "s1 == s3 : " << (s1 == s3 ? "ravny" : "ne ravny") << endl;

    Stroka s4(20);                       // p.4: zadannyi razmer pamyati
    cout << "Vvedite stroku (do 19 simvolov): ";
    s4.vvod();
    cout << "s4 = "; s4.vyvod();
    cout << " (dlina " << s4.dlina() << ")" << endl;
    return 0;
}
