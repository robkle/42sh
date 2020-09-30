#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	open("abc/abc", O_CREAT);
	perror("open");
	return (0);
}
