#include <stdio.h>

// Написать программу просмотра текстового файла и вывода его содержимого на экран
// (в качестве аргумента при запуске программы передаётся имя файла, второй аргумент(N) устанавливает вывод по группам строк(по N –строк) или сплошным текстом(N = 0)).
// Для чтения или записи файла использовать функции посимвольного ввода - вывода getc(), putc() или им подобные.
// Предусмотреть контроль ошибок открытия / закрытия / чтения / записи файла.

int main(int argc, char *argv[])
{
    FILE* fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error while opening a file!");
        return;
    }
    
    int N = 0;
    if (argc >= 2)
    {
		N = atoi(argv[2]);
    }

    char next_char;
    int num_of_lines = 0;
    while ((next_char = getc(fp)) != EOF)
    {
        if (N != 0 && next_char == '\n')
        {
            num_of_lines++;
            if (num_of_lines == N)
            {
                printf("\n");
                num_of_lines = 0;
            }
        }
        printf("%c", next_char);
    }

    int err = fclose(fp);
    if (err != 0)
    {
        printf("Error while closing a file!");
        return;
    }
}
