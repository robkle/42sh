#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

void init_shell()
{
    pid_t pid;

    if (!isatty(STDIN_FILENO))
    {
        perror("isatty failed");
        exit(1);
    }
    //signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    setpgid(0, 0);
    tcsetpgrp(STDIN_FILENO, getpid());
}

int main(void)
{
    init_shell();
    pid_t cpid = fork();

    if (cpid == 0)
    { /* CHILD PROCESS */
        if (setpgid(0, 0) == 0)
            printf("CHILD: setpgid successful\n");
        else
            printf("CHILD: setpgid successful\n");
        if (tcsetpgrp(STDIN_FILENO, getpid()) == 0)
            printf("CHILD: tcsetpgrp successful\n");
        else
        {
            printf("CHILD: tcsetpgrp failed\n");
            exit(1);
        }
        if (tcgetpgrp(STDIN_FILENO) == getpid())
            printf("CHILD: HI?\n");
        //execl("/usr/bin/vi", "vi", NULL);
        // execl("/bin/ls", "ls", NULL);
        // exit(-1);
    }
    else
    {
        /* PARENT PROCESS */
        while (tcgetpgrp(STDIN_FILENO) != cpid)
            NULL;
        if (tcgetpgrp(STDIN_FILENO) == getpid())
            printf("PARNET: 1\n");
        // wait(NULL);
        printf("PARNET: 2\n");
    }
    return (0);
}