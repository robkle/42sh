#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int pid;
	int ppid;
	int cpid;
	int status = 100;

	pid = fork();
	if (pid == 0)
	{
		pid = getpid();
		setpgid(pid, pid);
		for(int i = 0; i < 10; i++)
		{
			printf("%d\n", i);
			sleep(1);
		}
		// pid = fork();
		// if (pid == 0)
		// {
		// 	for(int i = 0; i < 10; i++)
		// 	{
		// 		printf("%d\n", i);
		// 		sleep(1);
		// 	}
		// 	exit(EXIT_SUCCESS);
		// }
		// cpid = waitpid(-getpid(), &status, WUNTRACED);
		// printf("cpid: [%d] and exit p1\n", cpid);
		exit(EXIT_SUCCESS);
	}
	setpgid(pid, pid);
	ppid = getpid();
	cpid = waitpid(pid, &status, WUNTRACED);
	printf("status: %d\n", status);
	printf("pid: %d\n", pid);
	printf("cpid: %d\n", cpid);
	return (0);
}
