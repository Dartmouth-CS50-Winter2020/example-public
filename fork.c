#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void parent();
void child();

int main()
{
        signal(SIGCHLD, SIG_IGN);

        int i;
        printf("type 1 to start: ");
        scanf("%d", &i);
        if (fork()) {        
                parent(); // parent process 
        }
        else {  
                child();   // child process 
        }
        return 0;
}

void parent()
{
        while (1)
        {       for (int j = 0; j < 10; j++)
                {
                        sleep(1);
                        printf("parent process: %d\n", j);
                }
        }        
}

void child()
{
        while (1)
        {
                for (char c = 'a'; c < 'z'; c++)
                {
                        sleep(1);
                        printf("child process: %c", c);
                }
        }        
}
