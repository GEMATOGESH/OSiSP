#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int which_one = 0; // Переменная определяющая от какого ребенка идет сигнал.
int N = 0; // Номер сообщения для каждого процесса.
pid_t parent, child1, child2;

int main()
{
    void p_action(int), c1_action(int), c2_action(int), g_exit(int), ignore(int);
    static struct sigaction pact, cact1, cact2;

    // Обработка принятия сигнала родителем.
    pact.sa_handler = p_action;
    sigaction(SIGUSR2, &pact, NULL);

    // Создание первого дочернего процесса.
    child1 = fork();
    if (child1 == 0)
    {
        // Обработка принятия сигнала первым ребенком.
        cact1.sa_handler = c1_action;
        sigaction(SIGUSR1, &cact1, NULL);

        // Обработка сигнала прерывания.
        cact1.sa_handler = ignore;
        sigaction(SIGINT, &cact1, NULL);

        parent = getppid();
        for (;;)
        {
            sleep(1);
            // Отправка сигнала родителю.
            printf("%d %d сын 1 put SIGUSR2\n", ++N, getpid());
            kill(parent, SIGUSR2);
            pause();
        }
    }
    else
    {
        // Создание второго дочернего процесса.
        child2 = fork();
        if (child2 == 0)
        {
            // Обработка принятия сигнала вторым ребенком.
            cact2.sa_handler = c2_action;
            sigaction(SIGUSR1, &cact2, NULL);

            // Обработка сигнала прерывания.
            cact2.sa_handler = ignore;
            sigaction(SIGINT, &cact2, NULL);
        
            parent = getppid();
            for (;;)
            {
                sleep(1);
                // Отправка сигнала родителю.
                printf("%d %d сын 2 put SIGUSR2\n", ++N, getpid());
                kill(parent, SIGUSR2);
                pause();
            }
        }
        else
        {
            // Обработка сигнала прерывания.
            pact.sa_handler = g_exit;
            sigaction(SIGINT, &pact, NULL);

            for (;;)
            {
                pause();
                sleep(1);

                // Отправка сигнала сыновьям.
                printf("%d %d родитель put SIGUSR1 for сын 1\n", ++N, getpid());
                kill(child1, SIGUSR1);
                printf("%d %d родитель put SIGUSR1 for сын 2\n", ++N, getpid());
                kill(child2, SIGUSR1);
            }
        }
    }
}

// Отображаем что родитель принял сигнал.
void p_action(int sig)
{
    if (which_one == 0)
    {
        printf("%d %d родитель get SIGUSR2 from сын 1\n", ++N, getpid());
        which_one = 1;
    }
    else
    {
        printf("%d %d родитель get SIGUSR2 from сын 2\n", ++N, getpid());
        which_one = 0;
    }
}

// Отображаем что сын 1 принял сигнал.
void c1_action(int sig)
{
    printf("%d %d сын 1 get SIGUSR1\n", ++N, getpid());
}

// Отображаем что сын 2 принял сигнал.
void c2_action(int sig)
{
    printf("%d %d сын 2 get SIGUSR1\n", ++N, getpid());
}

// Ожидание подтверждения от пользователя перед выходом.
void g_exit(int sig)
{
    kill(child1, SIGSTOP);
    kill(child2, SIGSTOP);
    char c;
    printf("\nAre you sure? Enter 1 to yes, anything else - to no. ");
    scanf("%c", &c);
    if (c == '1')
    {
        printf("\nStopping\n");
        exit(0);
    }
    else
    {
        printf("\nContinuing\n");
        kill(child1, SIGCONT);
        kill(child2, SIGCONT);
    }
}

// Метод перехватывающий сигнал прерывания для детей.
void ignore(int sig) 
{

}
