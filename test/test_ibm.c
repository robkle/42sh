#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* NOTE: This example illustrates tcsetgrp() and setpgrp(), but doesn’t
function correctly because SIGTTIN and SIGTTOU aren’t handled.*/

int main()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
    int status;
    int cpid;
    int ppid;
    char buf[256];
    sigset_t blocked;
    ppid = getpid();
    if (!(cpid = fork()))
    {
       // printf("child pid : %d\n", getpid());
        //setpgid(0, 0);
        //tcsetpgrp(0, getpid());
        execl("/usr/bin/vi", "vi", NULL);
        exit(-1);
    }
    if (cpid < 0)
        exit(-1);
  //  setpgid(cpid, cpid);
   // tcsetpgrp(0, cpid);
   // printf("foreground : %d\n", tcgetpgrp(STDIN_FILENO));
    waitpid(cpid, NULL, 0);
   // tcsetpgrp(0, ppid);
    while (1)
    {
        memset(buf, 0, 256);
        fgets(buf, 256, stdin);
        puts("ECHO: ");
        puts(buf);
        puts("\n");
    }
}