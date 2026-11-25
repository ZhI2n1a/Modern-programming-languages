
// =====================================================================
//  Лабораторная работа 2. Матричные операции
//  Тема: приобретение навыков работы с матричным представлением
//        данных; обработка матриц.
// =====================================================================
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

const int N = 5;   // размер квадратной матрицы (задан макросом в заготовке)

// ---------- 1. Минимум матрицы -------------------------------------
float mat_min(float m[N][N])
{
    float res = m[0][0];                 // предполагаем, что минимум - первый элемент
    for (int i = 0; i < N; i++)          // проходим по всем строкам
        for (int j = 0; j < N; j++)      // и всем столбцам
            if (m[i][j] < res)           // нашли элемент меньше текущего минимума
                res = m[i][j];           // запоминаем его
    return res;                          // возвращаем найденный минимум
}

// ---------- 2. Максимум матрицы ------------------------------------
float mat_max(float m[N][N])
{
    float res = m[0][0];                 // предполагаем, что максимум - первый элемент
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (m[i][j] > res)           // нашли элемент больше текущего максимума
                res = m[i][j];           // запоминаем его
    return res;
}

// ---------- 3-4. Максимум нижне- и верхнетреугольной части ----------
// Нижнетреугольная часть: элементы с индексами i >= j (на диагонали и ниже).
// Верхнетреугольная часть: элементы с индексами i <= j (на диагонали и выше).
float max_lower(float m[N][N])
{
    float res = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)     // j идёт только до i - условие нижнего треугольника
            if (m[i][j] > res) res = m[i][j];
    return res;
}
float max_upper(float m[N][N])
{
    float res = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)      // j начинается с i - условие верхнего треугольника
            if (m[i][j] > res) res = m[i][j];
    return res;
}

// ---------- 5-6. Минимум нижне- и верхнетреугольной части -----------
float min_lower(float m[N][N])
{
    float res = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (m[i][j] < res) res = m[i][j];
    return res;
}
float min_upper(float m[N][N])
{
    float res = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (m[i][j] < res) res = m[i][j];
    return res;
}

// ---------- 7-8. Минимум и максимум главной диагонали ---------------
// Элемент главной диагонали: m[i][i]
float min_diag(float m[N][N])
{
    float res = m[0][0];
    for (int i = 1; i < N; i++)          // диагональ одна - достаточно одного цикла
        if (m[i][i] < res) res = m[i][i];
    return res;
}
float max_diag(float m[N][N])
{
    float res = m[0][0];
    for (int i = 1; i < N; i++)
        if (m[i][i] > res) res = m[i][i];
    return res;
}

// ---------- 9-10. Минимум и максимум второстепенной диагонали -------
// Элемент второстепенной (побочной) диагонали: m[i][N-1-i]
float min_sdiag(float m[N][N])
{
    float res = m[0][N-1];               // первый элемент побочной диагонали
    for (int i = 1; i < N; i++)
        if (m[i][N-1-i] < res) res = m[i][N-1-i];
    return res;
}
float max_sdiag(float m[N][N])
{
    float res = m[0][N-1];
    for (int i = 1; i < N; i++)
        if (m[i][N-1-i] > res) res = m[i][N-1-i];
    return res;
}

// ---------- 11. Среднеарифметическое элементов матрицы --------------
float mat_mean(float m[N][N])
{
    float s = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            s += m[i][j];                // накапливаем сумму всех элементов
    return s / (N * N);                  // среднее = сумма / количество элементов
}

// ---------- 12-13. Среднее нижне- и верхнетреугольной части ---------
float mean_lower(float m[N][N])
{
    float s = 0;
    int k = 0;                           // счётчик элементов треугольной части
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
        {
            s += m[i][j];
            k++;                         // ещё один элемент учтён
        }
    return s / k;                        // делим на число учтённых элементов, а не на N*N
}
float mean_upper(float m[N][N])
{
    float s = 0;
    int k = 0;
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
        {
            s += m[i][j];
            k++;
        }
    return s / k;
}

// ---------- 14. Суммы строк матрицы ---------------------------------
// Результат помещается в одномерный массив s длины N.
void row_sums(float m[N][N], float s[N])
{
    for (int i = 0; i < N; i++)
    {
        s[i] = 0;
        for (int j = 0; j < N; j++)
            s[i] += m[i][j];             // суммируем элементы i-й строки
    }
}

// ---------- 15. Суммы столбцов матрицы ------------------------------
void col_sums(float m[N][N], float s[N])
{
    for (int j = 0; j < N; j++)
    {
        s[j] = 0;
        for (int i = 0; i < N; i++)
            s[j] += m[i][j];             // суммируем элементы j-го столбца
    }
}

// ---------- 16-17. Минимальные значения строк и столбцов ------------
void row_mins(float m[N][N], float s[N])
{
    for (int i = 0; i < N; i++)
    {
        s[i] = m[i][0];                  // минимум строки - её первый элемент
        for (int j = 1; j < N; j++)
            if (m[i][j] < s[i]) s[i] = m[i][j];
    }
}
void col_mins(float m[N][N], float s[N])
{
    for (int j = 0; j < N; j++)
    {
        s[j] = m[0][j];
        for (int i = 1; i < N; i++)
            if (m[i][j] < s[j]) s[j] = m[i][j];
    }
}

// ---------- 18-19. Максимальные значения строк и столбцов -----------
void row_maxs(float m[N][N], float s[N])
{
    for (int i = 0; i < N; i++)
    {
        s[i] = m[i][0];
        for (int j = 1; j < N; j++)
            if (m[i][j] > s[i]) s[i] = m[i][j];
    }
}
void col_maxs(float m[N][N], float s[N])
{
    for (int j = 0; j < N; j++)
    {
        s[j] = m[0][j];
        for (int i = 1; i < N; i++)
            if (m[i][j] > s[j]) s[j] = m[i][j];
    }
}

// ---------- 20-21. Среднеарифметические значения строк и столбцов ---
void row_means(float m[N][N], float s[N])
{
    for (int i = 0; i < N; i++)
    {
        s[i] = 0;
        for (int j = 0; j < N; j++)
            s[i] += m[i][j];
        s[i] /= N;                       // сумма строки / число элементов в ней
    }
}
void col_means(float m[N][N], float s[N])
{
    for (int j = 0; j < N; j++)
    {
        s[j] = 0;
        for (int i = 0; i < N; i++)
            s[j] += m[i][j];
        s[j] /= N;
    }
}

// ---------- 22. Суммы нижне- и верхнетреугольной части --------------
float sum_lower(float m[N][N])
{
    float s = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            s += m[i][j];
    return s;
}
float sum_upper(float m[N][N])
{
    float s = 0;
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            s += m[i][j];
    return s;
}

// ---------- 23. Элемент, ближайший к среднеарифметическому ----------
// Ищем элемент, для которого |m[i][j] - avg| минимален.
float closest_to_mean(float m[N][N], float avg)
{
    float best = m[0][0];                // лучший кандидат
    float dmin = fabs(m[0][0] - avg);    // минимальное найденное отклонение
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            float d = fabs(m[i][j] - avg);
            if (d < dmin)                // этот элемент ближе к среднему
            {
                dmin = d;                // запоминаем отклонение
                best = m[i][j];          // и сам элемент
            }
        }
    return best;
}

// ---------- Вспомогательная функция: печать одномерного массива -----
void print_vector(const char* title, float s[N])
{
    cout << title;
    for (int i = 0; i < N; i++)
        cout << setw(12) << setprecision(2) << fixed << s[i];
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(42);                           // фиксируем зерно генератора - результат воспроизводим
    float m[N][N];
    int i, j;

    // Заполнение матрицы случайными числами (как в заготовке: rand()/10)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            m[i][j] = (rand() % 10000) / 10.0f;  // в старых компиляторах rand() давал 0..32767,
                                         // поэтому берём остаток - значения 0..999.9

    // Печать матрицы
    cout << "Исходная матрица:" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            cout << setw(10) << setprecision(2) << fixed << m[i][j];
        cout << endl;
    }
    cout << endl;

    // Скалярные характеристики
    cout << "Минимум матрицы:                        " << mat_min(m) << endl;
    cout << "Максимум матрицы:                       " << mat_max(m) << endl;
    cout << "Максимум нижнетреугольной части:        " << max_lower(m) << endl;
    cout << "Максимум верхнетреугольной части:       " << max_upper(m) << endl;
    cout << "Минимум нижнетреугольной части:         " << min_lower(m) << endl;
    cout << "Минимум верхнетреугольной части:        " << min_upper(m) << endl;
    cout << "Минимум главной диагонали:              " << min_diag(m) << endl;
    cout << "Максимум главной диагонали:             " << max_diag(m) << endl;
    cout << "Минимум второстепенной диагонали:       " << min_sdiag(m) << endl;
    cout << "Максимум второстепенной диагонали:      " << max_sdiag(m) << endl;
    cout << "Среднеарифметическое матрицы:           " << mat_mean(m) << endl;
    cout << "Среднее нижнетреугольной части:         " << mean_lower(m) << endl;
    cout << "Среднее верхнетреугольной части:        " << mean_upper(m) << endl;
    cout << "Сумма нижнетреугольной части:           " << sum_lower(m) << endl;
    cout << "Сумма верхнетреугольной части:          " << sum_upper(m) << endl;

    // Векторные характеристики
    float r[N], c[N];
    row_sums(m, r);    print_vector("Суммы строк:            ", r);
    col_sums(m, r);    print_vector("Суммы столбцов:         ", r);
    row_mins(m, r);    print_vector("Минимумы строк:         ", r);
    col_mins(m, r);    print_vector("Минимумы столбцов:      ", r);
    row_maxs(m, r);    print_vector("Максимумы строк:        ", r);
    col_maxs(m, r);    print_vector("Максимумы столбцов:     ", r);
    row_means(m, r);   print_vector("Средние по строкам:     ", r);
    col_means(m, r);   print_vector("Средние по столбцам:    ", r);

    cout << "Элемент, ближайший к среднему:          "
         << closest_to_mean(m, mat_mean(m)) << endl;

    return 0;
}
