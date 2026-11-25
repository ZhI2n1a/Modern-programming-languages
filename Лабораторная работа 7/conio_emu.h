
// ============================================================
// conio_emu.h — эмуляция conio: нажатия клавиш берутся из stdin
// ============================================================
#ifndef CONIO_EMU_H
#define CONIO_EMU_H
#include <cstdio>
namespace cemu {
    static char buf[4096];
    static int  len = 0, pos = 0;
}
inline void conio_init() {           // прочитать весь ввод как нажатия
    int ch;
    while ((ch = fgetc(stdin)) != EOF && cemu::len < 4095)
        cemu::buf[cemu::len++] = (char)ch;
}
inline int keypressed() { return 1; }        // нажатие уже в буфере
inline int getch() {                          // взять символ нажатия
    if (cemu::pos < cemu::len) return (unsigned char)cemu::buf[cemu::pos++];
    return 27;                                // ввод закончился — как Esc
}
#endif
