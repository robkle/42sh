#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid = getpid();

    printf("%d\n", pid);

    printf("%d\n", setpgid(pid, 92795));
    perror("");

    printf("%d\n", getpgrp());

    return (0);
}
