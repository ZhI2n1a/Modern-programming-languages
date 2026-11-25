
// Лабораторная работа 1, задание 2
// Иллюстрация операций с указателями для разных типов данных
#include <stdio.h>

int main(void)
{
    int    mas[]  = { 100, 200, 300 };
    double dbas[] = { 1.5, 2.5, 3.5 };
    char   cbas[] = { 'A', 'B', 'C' };
    long   lbas[] = { 1000L, 2000L, 3000L };

    /* ---------- тип int ---------- */
    printf("--- int ---\n");
    int *ptr1 = mas;
    int *ptr2 = &mas[2];
    printf("x=%lu, *x=%d, &x=%lu\n", (unsigned long)ptr1, *ptr1, (unsigned long)&ptr1);
    ptr1++;                                     // сдвиг на sizeof(int) байт
    printf("x=%lu, *x=%d, &x=%lu\n", (unsigned long)ptr1, *ptr1, (unsigned long)&ptr1);
    printf("x=%lu, *x=%d, &x=%lu\n", (unsigned long)ptr2, *ptr2, (unsigned long)&ptr2);
    ++ptr2;                                     // сдвиг на sizeof(int) байт
    printf("ptr2-ptr1=%lu\n", (unsigned long)(ptr2 - ptr1));

    /* ---------- тип double ---------- */
    printf("--- double ---\n");
    double *d1 = dbas, *d2 = &dbas[2];
    printf("x=%lu, *x=%f, &x=%lu\n", (unsigned long)d1, *d1, (unsigned long)&d1);
    d1++;
    printf("x=%lu, *x=%f, &x=%lu\n", (unsigned long)d1, *d1, (unsigned long)&d1);
    printf("x=%lu, *x=%f, &x=%lu\n", (unsigned long)d2, *d2, (unsigned long)&d2);
    ++d2;
    printf("ptr2-ptr1=%lu\n", (unsigned long)(d2 - d1));

    /* ---------- тип char ---------- */
    printf("--- char ---\n");
    char *c1 = cbas, *c2 = &cbas[2];
    printf("x=%lu, *x=%c, &x=%lu\n", (unsigned long)c1, *c1, (unsigned long)&c1);
    c1++;
    printf("x=%lu, *x=%c, &x=%lu\n", (unsigned long)c1, *c1, (unsigned long)&c1);
    printf("x=%lu, *x=%c, &x=%lu\n", (unsigned long)c2, *c2, (unsigned long)&c2);
    ++c2;
    printf("ptr2-ptr1=%lu\n", (unsigned long)(c2 - c1));

    /* ---------- тип long ---------- */
    printf("--- long ---\n");
    long *l1 = lbas, *l2 = &lbas[2];
    printf("x=%lu, *x=%ld, &x=%lu\n", (unsigned long)l1, *l1, (unsigned long)&l1);
    l1++;
    printf("x=%lu, *x=%ld, &x=%lu\n", (unsigned long)l1, *l1, (unsigned long)&l1);
    printf("x=%lu, *x=%ld, &x=%lu\n", (unsigned long)l2, *l2, (unsigned long)&l2);
    ++l2;
    printf("ptr2-ptr1=%lu\n", (unsigned long)(l2 - l1));

    printf("--- razmery tipov ---\n");
    printf("int=%lu, double=%lu, char=%lu, long=%lu\n",
           (unsigned long)sizeof(int), (unsigned long)sizeof(double),
           (unsigned long)sizeof(char), (unsigned long)sizeof(long));

    return 0;
}
