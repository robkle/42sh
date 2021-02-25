#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
	
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	printf("OPENING\n");
	int fd = open("fifo", O_WRONLY);
	printf("OPENED\n");
	// dup2(fd, 0);
	close(fd);
	printf("CLOSED\n");
	return (0);
}