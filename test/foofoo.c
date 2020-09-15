#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
	char *str = strdup("abcde");
	char *fake_str = str;

	fake_str++;
	fake_str++;
	printf("%ld\n", fake_str - str);

	return (0);
}
