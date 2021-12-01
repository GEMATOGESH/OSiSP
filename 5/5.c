#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

#define MSGSIZE 100

// Сравнение строк
int compare(char a[], char b[])
{
    int flag = 1, i = 0;  
    while (a[i] != '\0' && b[i] != '\0')  
    {
        if (a[i] != b[i])
        {
            flag = 0;
            break;
        }
        i++;
    }
    return flag;
}

main()
{
    char inbuf[MSGSIZE];
    int number_of_children = 2;
    int j;
    int pipes[number_of_children][2];
    pid_t children[1000]; // Есть ограничение на кол-во детей
    pid_t father;
    int new_children = 0;
    int actual_number = 2;


    // Начальный список детей
    for (int i = 0; i < number_of_children; i++)
    {
        children[i] = fork();
        char *msg = "Hello\n";
        write(pipes[i][1], msg, MSGSIZE);
    }
    
    father = getppid();

    while (1)
    {
        srand(time(0));
        // Введение новых детей
        for (int i = number_of_children; i < number_of_children + new_children; i++)
        {
            children[i] = fork();
        }   
        number_of_children += new_children;
        new_children = 0;

        // Выход из цикла если детей нет
        if (!actual_number)
        {
            break;
        }

        // Отправка сообщений каждым из детей
        for (int i = 0; i < number_of_children; i++)
        {
            // Ребенок может быть мертв
            if (children[i] == -1)
            {
                // Dead
            }
            else
            {
                read(pipes[i][0], inbuf, MSGSIZE); // Читаем что пишет родитель
                if (compare(inbuf, "Die\n"))
                {
                    kill(children[i], SIGSTOP); // Убиваем ребенка, если родитель попросил
                    close(pipes[i]);
                    actual_number--;
                }
                else
                {
                    int number = (rand() % (1 - 0 + 1)) + 0;
                    char *msg;  // Каждый ребенок рандомит сообщение отцу, шансы на обычное сообщение и доп ребенка равны
                    if (number)
                    {
                        msg = "Hello\n";
                    }
                    else
                    {
                        msg = "More\n";
                    }
                    write(pipes[i][1], msg, MSGSIZE);
                }
            }
        }

        // Ответы родителя
        for (int i = 0; i < number_of_children; i++)
        {
            read(pipes[i][0], inbuf, MSGSIZE);
            if (compare(inbuf, "More\n")) // Если ребенок просит больше детей - делаем больше детей
            {
                actual_number++;
                new_children++;
                char *msg = "Hello\n";
                write(pipes[i][1], msg, MSGSIZE);
            }
            if (compare(inbuf, "Hello\n")) // Если ребенок пишет обычное сообщение - убиваем его
            {
                char *msg = "Die\n";
                write(pipes[i][1], msg, MSGSIZE);
            }
        }
    }
}
