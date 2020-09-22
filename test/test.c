#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t child_pid = fork();

    if (child_pid > 0)
    {
        /*parent*/
        sleep(1);
        int foreground_pid = tcgetpgrp(STDIN_FILENO);
        printf("%d is in foreground\n", foreground_pid);
        if ((tcsetpgrp(STDIN_FILENO, child_pid)) == -1)
        {
            printf("Could not set PGID\n");
        }
        printf("I'm parent. you shouldn't see me\n");
    }
    else if (child_pid == 0)
    {
        /*child*/
        setpgid(0, 0);
        printf("I'm child\n");
    }
    return (EXIT_SUCCESS);
}