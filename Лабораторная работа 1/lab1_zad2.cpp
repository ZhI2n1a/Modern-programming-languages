
// Лабораторная работа 1, задание 2
// Иллюстрация операций с указателями для разных типов данных
#include <stdio.h>
#include <stdlib.h>

// Макрос PR выводит: адрес в указателе, значение по адресу, адрес самого указателя
#define PR(x) printf("x=%u, *x=%d, &x=%u\n", (unsigned)(x), (int)(*(int*)(x)), (unsigned)(&(x)))

#define PRG(fmt, x) printf("x=%u, *x=" fmt ", &x=%u\n", (unsigned)(x), *(x), (unsigned)(&(x)))

int main(void)
{
    int    mas[] = { 100, 200, 300 };
    double dbas[] = { 1.5, 2.5, 3.5 };
    char   cbas[] = { 'A', 'B', 'C' };
    long   lbas[] = { 1000L, 2000L, 3000L };

    int  *ptr1;
    int  *ptr2;

    /* ---------- тип int ---------- */
    printf("--- int ---\n");
    ptr1 = mas;
    ptr2 = &mas[2];
    PRG("%d", ptr1);
    ptr1++;                       // сдвиг на sizeof(int) байт
    PRG("%d", ptr1);
    PRG("%d", ptr2);
    ++ptr2;                       // сдвиг на sizeof(int) байт
    printf("ptr2-ptr1=%u\n", (unsigned)(ptr2 - ptr1));

    /* ---------- тип double ---------- */
    printf("--- double ---\n");
    {
        double *p1 = dbas, *p2 = &dbas[2];
        printf("p1=%u, *p1=%f, &p1=%u\n", (unsigned)p1, *p1, (unsigned)&p1);
        p1++;
        printf("p1=%u, *p1=%f, &p1=%u\n", (unsigned)p1, *p1, (unsigned)&p1);
        printf("p2=%u, *p2=%f, &p2=%u\n", (unsigned)p2, *p2, (unsigned)&p2);
        ++p2;
        printf("p2-ptr1(v double)=%u\n", (unsigned)(p2 - p1));
    }

    /* ---------- тип char ---------- */
    printf("--- char ---\n");
    {
        char *p1 = cbas, *p2 = &cbas[2];
        printf("p1=%u, *p1=%c, &p1=%u\n", (unsigned)p1, *p1, (unsigned)&p1);
        p1++;
        printf("p1=%u, *p1=%c, &p1=%u\n", (unsigned)p1, *p1, (unsigned)&p1);
        printf("p2=%u, *p2=%c, &p2=%u\n", (unsigned)p2, *p2, (unsigned)&p2);
        ++p2;
        printf("p2-p1=%u\n", (unsigned)(p2 - p1));
    }

    /* ---------- тип long ---------- */
    printf("--- long ---\n");
    {
        long *p1 = lbas, *p2 = &lbas[2];
        printf("p1=%u, *p1=%ld, &p1=%u\n", (unsigned)p1, *p1, (unsigned)&p1);
        p1++;
        printf("p1=%u, *p1=%ld, &p1=%u\n", (unsigned)p1, *p1, (unsigned)&p1);
        printf("p2=%u, *p2=%ld, &p2=%u\n", (unsigned)p2, *p2, (unsigned)&p2);
        ++p2;
        printf("p2-p1=%u\n", (unsigned)(p2 - p1));
    }

    printf("--- razmery tipov ---\n");
    printf("int=%u, double=%u, char=%u, long=%u\n",
           (unsigned)sizeof(int), (unsigned)sizeof(double),
           (unsigned)sizeof(char), (unsigned)sizeof(long));

    return 0;
}
