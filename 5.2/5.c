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
    int number_of_children = 3;
    int number_of_alive = 3;

    int children1_pipes[3][2];
    int children2_pipes[3][2];
    int children3_pipes[3][2];

    int father_pipe_to_childrens[3][2];

    pid_t children[3];
    pid_t father;


    // Начальный список детей
    children[0] = fork();
    char *msg = "Hello\n";
    write(father_pipe_to_childrens[0][1], msg, MSGSIZE);
    for (size_t i = 0; i < number_of_children; i++)
    {
        write(children1_pipes[i][1], msg, MSGSIZE);
    }
    
    children[1] = fork();
    *msg = "Hello\n";
    write(father_pipe_to_childrens[1][1], msg, MSGSIZE);
    for (size_t i = 0; i < number_of_children; i++)
    {
        write(children2_pipes[i][1], msg, MSGSIZE);
    }

    children[2] = fork();
    *msg = "Hello\n";
    write(father_pipe_to_childrens[2][1], msg, MSGSIZE);
    for (size_t i = 0; i < number_of_children; i++)
    {
        write(children3_pipes[i][1], msg, MSGSIZE);
    }
    
    
    father = getppid();

    while (1)
    {
        if (number_of_alive == 0)
        {
            return;
        }

        // Отправка сообщений каждым из детей

        // 1
        read(father_pipe_to_childrens[0][0], inbuf, MSGSIZE);
        if (children[0] != -1)
        {
            if (compare(inbuf, "Die\n"))
            {
                kill(children[0], SIGSTOP); // Убиваем ребенка, если родитель попросил
                close(father_pipe_to_childrens[0]);
                close(children1_pipes);
                number_of_alive--;
            }
            else
            {
                for (int i = 0; i < number_of_children; i++)
                {
                    read(children1_pipes[i][0], inbuf, MSGSIZE);
                    *msg = "Hello\n";
                    write(children2_pipes[i][1], msg, MSGSIZE);
                    write(children3_pipes[i][1], msg, MSGSIZE);
                }
            }
        }


        // 2
        read(father_pipe_to_childrens[1][0], inbuf, MSGSIZE);
        if (children[1] != -1)
        {
            if (compare(inbuf, "Die\n"))
            {
                kill(children[1], SIGSTOP); // Убиваем ребенка, если родитель попросил
                close(father_pipe_to_childrens[1]);
                close(children2_pipes);
                number_of_alive--;
            }
            else
            {
                for (int i = 0; i < number_of_children; i++)
                {
                    read(children2_pipes[i][0], inbuf, MSGSIZE);
                    *msg = "Hello\n";
                    write(children1_pipes[i][1], msg, MSGSIZE);
                    write(children3_pipes[i][1], msg, MSGSIZE);
                }
            }
        }


        // 3
        read(father_pipe_to_childrens[2][0], inbuf, MSGSIZE);
        if (children[2] != -1)
        {
            if (compare(inbuf, "Die\n"))
            {
                kill(children[2], SIGSTOP); // Убиваем ребенка, если родитель попросил
                close(father_pipe_to_childrens[2]);
                close(children3_pipes);
                number_of_alive--;
            }
            else
            {
                for (int i = 0; i < number_of_children; i++)
                {
                    read(children3_pipes[i][0], inbuf, MSGSIZE);
                    *msg = "Hello\n";
                    write(children1_pipes[i][1], msg, MSGSIZE);
                    write(children2_pipes[i][1], msg, MSGSIZE);
                }
            }
        }


        // Ответы родителя
        char *msg = "Die\n";
        write(father_pipe_to_childrens[0][1], msg, MSGSIZE);
        write(father_pipe_to_childrens[1][1], msg, MSGSIZE);
        write(father_pipe_to_childrens[2][1], msg, MSGSIZE);
    }
}
