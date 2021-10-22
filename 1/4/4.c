#include <stdio.h>

// Написать программу копирования одного файла в другой.
// В качестве параметров при вызове программы передаются имена первого и второго файлов.
// Для чтения или записи файла использовать функции посимвольного ввода - вывода getc(), putc() или им подобные.
// Предусмотреть копирование  прав доступа к файлу и контроль ошибок открытия / закрытия / чтения / записи файла.

int main(int arc, char* argv[])
{
    FILE* from_file_p;
    from_file_p = fopen(argv[1], "r");
    if (from_file_p == NULL)
    {
        printf("Error while opening first file! ");
        return;
    }

    FILE* to_file_p;
    to_file_p = fopen(argv[2], "w");
    if (to_file_p == NULL)
    {
        printf("Error while opening second file! ");
        return;
    }

    char symbol;
    while ((symbol = getc(from_file_p)) != EOF)
    {
        putc(symbol, to_file_p);
    }

    int err = fclose(from_file_p);
    if (err != 0)
    {
        printf("Error while closing first file!");
        return;
    }

    err = fclose(to_file_p);
    if (err != 0)
    {
        printf("Error while closing second file!");
        return;
    }

    printf("Success!");
}
