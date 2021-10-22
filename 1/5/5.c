#include <stdio.h>
#include <locale.h>
#include <dirent.h>

// Написать программу вывода на экран содержимого текущего каталога.
// Вывести с использованием данной программы содержимое корневого каталога.
// Предусмотреть контроль ошибок открытия / закрытия / чтения каталога.


int main()
{
    char * locale = setlocale(LC_ALL, "");

    DIR* dir;
    struct dirent* entry;

    dir = opendir("/");
    if (!dir) 
    {
        printf("Error while opening catalog!");
        return;
    };

    printf("Корневой каталог: \n");
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    };

    closedir(dir);


    char here[10000];
    getcwd(here, 10000);

    dir = opendir(here);
    if (!dir)
    {
        printf("Error while opening catalog!");
        return;
    };

    printf("\nТекущий каталог (%s): \n", here);
    while ((entry = readdir(dir)) != NULL) 
    {
        printf("%s\n", entry->d_name);
    };

    closedir(dir);
}
