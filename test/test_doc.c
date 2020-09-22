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

void init_shell()
{
    pid_t shell_pgid;
    int shell_terminal;
    int shell_is_interactive;
    /* See if we are running interactively.  */
    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty(shell_terminal);
    if (shell_is_interactive)
    {
        /* Loop until we are in the foreground.  */
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
            kill(-shell_pgid, SIGTTIN);
        /* Ignore interactive and job-control signals.  */
        // signal(SIGINT, SIG_IGN);
        // signal(SIGQUIT, SIG_IGN);
        // signal(SIGTSTP, SIG_IGN);
        // signal(SIGTTIN, SIG_IGN);
        // signal(SIGTTOU, SIG_IGN);
        // signal(SIGCHLD, SIG_IGN);
        /* Put ourselves in our own process group.  */
        shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0)
        {
            perror("Couldn't put the shell in its own process group");
            exit(1);
        }
        /* Grab control of the terminal.  */
        if (tcsetpgrp(shell_terminal, shell_pgid) == -1)
		{
			perror("tcsetpgrp fail");
			exit(1);
		}
    }
}

int main()
{
    init_shell();
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
//	signal(SIGTTIN, SIG_IGN);
	//signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
    int status;
    int cpid;
    int ppid;
    char buf[256];
    sigset_t blocked;
    ppid = getpid();
    if (!(cpid = fork()))
    {
        printf("child pid : %d\n", getpid());
        setpgid(0, 0);
        if (tcsetpgrp(0, getpid()) == -1)
        {
            perror("CHILD: tesetpgrp failed");
            exit(1);
        }
        execl("/usr/bin/vi", "vi", NULL);
        exit(-1);
    }
    if (cpid < 0)
        exit(-1);
    setpgid(cpid, cpid);
    tcsetpgrp(0, cpid);
    if ( tcgetpgrp(STDIN_FILENO) == cpid)
    {
        printf("PARENT: child is in foreground but you shouldn't see me\n");
    }
    waitpid(cpid, NULL, 0);
    tcsetpgrp(0, ppid);
    while (1)
    {
        memset(buf, 0, 256);
        fgets(buf, 256, stdin);
        puts("ECHO: ");
        puts(buf);
        puts("\n");
    }
}