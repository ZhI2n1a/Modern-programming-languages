/* Лабораторная работа 5.
   Организация ввода-вывода; работа с файлами средствами библиотеки
   функций ввода-вывода; использование аргументов функции main(). */
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

/* ============ Пункт 1. Вывод содержимого текстового файла на экран ============ */
/* В исходном варианте символ читался в переменную, затем проверялся
   feof() и только после этого выводился. Текст программы сокращается,
   если проверку конца файла совместить с чтением в условии цикла:
   не нужны отдельный флаг и повторная проверка. */
void printFile(const char *name)
{
    FILE *f = fopen(name, "rb");          /* открыть файл для чтения */
    if (f == NULL)                        /* файл не открылся - */
    {
        printf("Cannot open file %s\n", name);   /* сообщение и выход */
        return;
    }
    int c;
    while ((c = fgetc(f)) != EOF)         /* читать символ... */
        putchar(c);                       /* ...и сразу выводить на экран */
    fclose(f);                            /* закрыть файл */
}

/* ============ Пункт 2. Подсчет "пустых" и "непустых" символов ============ */
/* "Пустой" символ не отображается на экране: управляющие символы
   (перевод строки, табуляция, конец страницы '\f' и прочие) - их
   проверяет iscntrl(), а также пробел. Остальные символы - "непустые". */
void countChars(const char *name)
{
    FILE *f = fopen(name, "rb");
    if (f == NULL) { printf("Cannot open file %s\n", name); return; }
    long blank = 0, nonblank = 0;         /* счетчики пустых и непустых */
    int c;
    while ((c = fgetc(f)) != EOF)
    {
        if (iscntrl(c) || c == ' ')       /* пустой символ? */
            ++blank;
        else
            ++nonblank;                   /* обычный, отображаемый символ */
    }
    fclose(f);
    printf("Blank chars:     %ld\n", blank);
    printf("Non-blank chars: %ld\n", nonblank);
}

/* ============ Пункт 3. Поиск заданной подстроки в текстовом файле ============ */
/* Искомая подстрока передается как параметр функции. Результаты -
   номер строки и позиция каждого вхождения - формируются в отдельном
   файле, там же выводится общее число вхождений. */
void findSubstr(const char *name, const char *pattern, const char *outName)
{
    FILE *in  = fopen(name, "r");
    FILE *out = fopen(outName, "w");
    if (in == NULL || out == NULL) { printf("File error\n"); return; }
    char line[1024];                      /* буфер для очередной строки */
    int  lineNo = 0, total = 0;           /* номер строки и счетчик вхождений */
    while (fgets(line, sizeof(line), in) != NULL)
    {
        ++lineNo;                         /* прочитана очередная строка */
        const char *p = line;
        while ((p = strstr(p, pattern)) != NULL)   /* найдено вхождение */
        {
            fprintf(out, "line %d, position %d\n",
                    lineNo, (int)(p - line) + 1);
            ++total;
            p += strlen(pattern);         /* продолжить поиск после вхождения */
        }
    }
    fprintf(out, "total occurrences of \"%s\": %d\n", pattern, total);
    fclose(in);
    fclose(out);
}

/* ============ Пункт 4. Перенос номеров страниц в последнюю строку ============ */
/* Номер страницы стоит в первой строке страницы в виде "- 34 -".
   Его нужно перенести в последнюю строку страницы (перед символом
   '\f', отмечающим переход на следующую страницу). */
/* Проверка: является ли строка номером страницы "- N -" */
bool isPageNum(const char *line, int &num)
{
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')  ++i;   /* пропустить пробелы */
    if (line[i] != '-')  return false;                /* нет левого дефиса */
    ++i;
    while (line[i] == ' ')  ++i;
    if (!isdigit((unsigned char)line[i]))  return false;  /* нет числа */
    num = 0;
    while (isdigit((unsigned char)line[i]))
        num = num * 10 + (line[i++] - '0');           /* накопить число */
    while (line[i] == ' ')  ++i;
    if (line[i] != '-')  return false;                /* нет правого дефиса */
    ++i;
    while (line[i] == ' ' || line[i] == '\t')  ++i;
    return line[i] == '\0' || line[i] == '\n' || line[i] == '\r';
}

void movePageNumbers(const char *name, const char *outName)
{
    FILE *in  = fopen(name, "r");
    FILE *out = fopen(outName, "w");
    if (in == NULL || out == NULL) { printf("File error\n"); return; }
    char line[1024];
    int  pend = -1;                 /* номер текущей страницы, еще не выведен */
    bool newPage = true;            /* следующая строка может быть номером */
    while (fgets(line, sizeof(line), in) != NULL)
    {
        int num;
        /* строка-номер обрабатывается только в начале страницы */
        if (newPage && isPageNum(line, num))
        {
            pend = num;             /* запомнить номер, строку не печатать */
            newPage = false;
            continue;
        }
        char *ff = strchr(line, '\f');        /* конец страницы в строке? */
        if (ff == NULL)
            fputs(line, out);                 /* обычная строка текста */
        else
        {
            if (ff != line)                   /* текст перед '\f' */
                fwrite(line, 1, ff - line, out);
            if (pend >= 0)                    /* номер - в последнюю строку */
                fprintf(out, "%d\n", pend);
            fputc('\f', out);                 /* разрыв страницы */
            pend = -1;
        }
        newPage = (ff != NULL);               /* после '\f' - новая страница */
    }
    if (pend >= 0)                            /* у последней страницы '\f' */
        fprintf(out, "%d\n", pend);           /* может и не быть */
    fclose(in);
    fclose(out);
}

/* ============ Пункты 5-6. Программа-шифратор файлов ============ */
/* Схема шифровки: c = c ^ key[i], символы ключа используются
   циклически, пока не будет считан весь ввод. Операция XOR обратна
   самой себе, поэтому повторная обработка зашифрованного файла тем
   же ключом дает точную копию исходного файла.
   Имена файлов и ключ вводятся из командной строки (пункт 6). */
void encrypt(const char *inName, const char *outName, const char *key)
{
    FILE *fin  = fopen(inName, "rb");
    FILE *fout = fopen(outName, "wb");
    if (fin == NULL || fout == NULL) { printf("File error\n"); return; }
    size_t i = 0, klen = strlen(key);     /* индекс символа ключа */
    int c;
    while ((c = fgetc(fin)) != EOF)
    {
        c ^= key[i];                      /* закодировать символ */
        fputc(c, fout);
        i = (i + 1) % klen;               /* ключ используется циклически */
    }
    fclose(fin);
    fclose(fout);
}

int main(int argc, char *argv[])
{
    if (argc < 3)                         /* аргументы командной строки */
    {
        printf("Usage: lab5 <command> ...\n"
               "  p <file>                     - print file to screen\n"
               "  c <file>                     - count blank/non-blank chars\n"
               "  f <file> <pattern> <out>     - find substring\n"
               "  m <file> <out>               - move page numbers\n"
               "  e <in> <out> <key>           - encrypt/decrypt file\n");
        return 1;
    }
    switch (argv[1][0])                   /* выбор операции по команде */
    {
        case 'p': printFile(argv[2]);                       break;
        case 'c': countChars(argv[2]);                      break;
        case 'f': findSubstr(argv[2], argv[3], argv[4]);    break;
        case 'm': movePageNumbers(argv[2], argv[3]);        break;
        case 'e': encrypt(argv[2], argv[3], argv[4]);       break;
        default:  printf("Unknown command: %s\n", argv[1]); return 1;
    }
    return 0;
}
