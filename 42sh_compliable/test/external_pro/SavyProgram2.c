#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int time;
	time = 10;
	while (time > 0) {
		time--;
		sleep(1);
		printf("SavvyProgram Time Elapsed: %d\n", time);
	}
	return (0);
}
