#include <stdio.h>

// Написать программу ввода символов с клавиатуры и записи их в файл(в качестве аргумента при запуске программы вводится имя файла).
// Для чтения или записи файла использовать функции посимвольного ввода - вывода getc(), putc() или им подобные.
// Предусмотреть выход после ввода определённого символа(например: ctrl - F).После запуска и отработки программы просмотреть файл.
// Предусмотреть контроль ошибок открытия / закрытия / чтения файла.

int main(int argc, char *argv[])
{
    FILE* fp;
    fp = fopen(argv[1], "w+");
    if (fp == NULL)
    {
        printf("Error while opening a file! ");
        return;
    }

    char symbol;
    printf("Enter string: ");
    while ((symbol = getchar()) != '\n') 
    {
        putc(symbol, fp);
    }

    int err = fclose(fp);
    if (err != 0)
    {
        printf("Error while closing a file!");
        return;
    }
}
