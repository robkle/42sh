#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>

int main(void)
{
	char buf[10];
	DIR *dirp;
	struct dirent *dir;

	strcpy(buf, "./");
	dirp = opendir(buf);
	while ((dir = readdir(dirp)))
		printf("%s\n", dir->d_name);
	closedir(dirp);
	return (0);
}
