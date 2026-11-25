
// ============================================================
// graph_emu.h — эмуляция Borland graphics на символьном экране
// Интерфейс совпадает с графической библиотекой Borland C++:
// initgraph, setcolor, setfillstyle, pieslice, circle, delay
// ============================================================
#ifndef GRAPH_EMU_H
#define GRAPH_EMU_H
#include <cstdio>
#include <cmath>

const int EMU_W = 64, EMU_H = 24;   // размер символьного экрана
const int SCREEN_W = 640, SCREEN_H = 480;  // виртуальные пиксели Borland
const int SOLID_FILL = 1, EMPTY_FILL = 0;

static char emu_screen[EMU_H][EMU_W + 1];  // буфер экрана
static int  emu_color = 7, emu_fill = 7;   // текущие цвета
static int  emu_frames = 0;                // счётчик кадров

// цвет -> отображаемый символ (фон 0 -> пробел)
inline char emu_char(int c) {
    static const char map[16] = {' ','O','o','+','#','%','*','@','X','&','$','=','-','~','W','M'};
    return map[c & 15];
}
inline void initgraph(int*, int*, const char*) {
    for (int i = 0; i < EMU_H; i++) {
        for (int j = 0; j < EMU_W; j++) emu_screen[i][j] = ' ';
        emu_screen[i][EMU_W] = '\0';
    }
}
inline void closegraph() {}
inline void setcolor(int c)      { emu_color = c; }
inline void setfillstyle(int, int c) { emu_fill = c; }

// закрашенный сектор (углы против часовой стрелки, как в Borland)
inline void pieslice(int x, int y, int a1, int a2, int r) {
    double cx = x * EMU_W / (double)SCREEN_W;
    double cy = y * EMU_H / (double)SCREEN_H;
    double rx = r * EMU_W / (double)SCREEN_W;  if (rx < 0.5) rx = 0.5;
    double ry = r * EMU_H / (double)SCREEN_H;  if (ry < 0.5) ry = 0.5;
    for (int i = 0; i < EMU_H; i++)
        for (int j = 0; j < EMU_W; j++) {
            double dx = (j + 0.5 - cx) / rx, dy = (i + 0.5 - cy) / ry;
            if (dx*dx + dy*dy <= 1.0) {
                double ang = atan2(-dy, dx) * 180.0 / M_PI;  // против часовой
                if (ang < 0) ang += 360;
                bool in = (a1 <= a2) ? (ang >= a1 && ang <= a2)
                                     : (ang >= a1 || ang <= a2);
                if (in) emu_screen[i][j] = emu_char(emu_fill);
            }
        }
}
// окружность: клетки внутри эллипса, у которых есть сосед снаружи
inline void circle(int x, int y, int r) {
    double cx = x * EMU_W / (double)SCREEN_W;
    double cy = y * EMU_H / (double)SCREEN_H;
    double rx = r * EMU_W / (double)SCREEN_W;  if (rx < 0.5) rx = 0.5;
    double ry = r * EMU_H / (double)SCREEN_H;  if (ry < 0.5) ry = 0.5;
    int nb[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for (int i = 0; i < EMU_H; i++)
        for (int j = 0; j < EMU_W; j++) {
            double dx = (j + 0.5 - cx) / rx, dy = (i + 0.5 - cy) / ry;
            if (dx*dx + dy*dy <= 1.0) {
                for (int k = 0; k < 4; k++) {
                    double nx = (j + nb[k][0] + 0.5 - cx) / rx;
                    double ny = (i + nb[k][1] + 0.5 - cy) / ry;
                    if (nx*nx + ny*ny > 1.0) { emu_screen[i][j] = emu_char(emu_color); break; }
                }
            }
        }
}
// delay(): выводит текущее состояние экрана как кадр
inline void delay(int ms) {
    (void)ms;
    printf("=== kadr %d ===\n", ++emu_frames);
    for (int i = 0; i < EMU_H; i++) printf("|%s|\n", emu_screen[i]);
    printf("+"); for (int j = 0; j < EMU_W; j++) printf("-"); printf("+\n");
    fflush(stdout);
}
#endif
