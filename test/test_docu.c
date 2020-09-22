#include <sys/types.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* Make sure the shell is running interactively as the foreground job
   before proceeding. */

void init_shell()
{
    pid_t shell_pgid;
    struct termios shell_tmodes;
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
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);

        /* Put ourselves in our own process group.  */
        shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0)
        {
            perror("Couldn't put the shell in its own process group");
            exit(1);
        }

        /* Grab control of the terminal.  */
        int ret = tcsetpgrp(shell_terminal, shell_pgid);

        /* Save default terminal attributes for shell.  */
        tcgetattr(shell_terminal, &shell_tmodes);
    }
}

void launch_job(job *j, int foreground)
{
    process *p;
    pid_t pid;
    int infile, outfile;

    infile = j->stdin;
    for (p = j->first_process; p; p = p->next)
    {

        /* 자식 프로세스들을 만들어라 */
        pid = fork();
        if (pid == 0)
        { /* 이것은 자식 프로세스이다. */
            launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
        }
        else
        { /* 이것은 부모 프로세스이다. */
            p->pid = pid;
            if (shell_is_interactive)
            {
                if (!j->pgid)
                    j->pgid = pid;
                setpgid(pid, j->pgid);
            }
        }

        /* pipe들을 정리하라. */
        if (infile != j->stdin)
            close(infile);
        if (outfile != j->stdout)
            close(outfile);
        infile = mypipe[0];
    }

    format_job_info(j, "launched");

    if (!shell_is_interactive)
        wait_for_job(j);
    else if (foreground)
        put_job_in_foreground(j, 0);
    else
        put_job_in_background(j, 0);
}

int main(void)
{
    init_shell();
    return (0);
}