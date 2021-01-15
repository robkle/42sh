#include <string.h>
#include <stdio.h>
int main(void)
{
	char *orig = "testtest";
	char name[256];
	char value[256];

	bzero(name, 256);
	bzero(value, 256);
	strncpy(name, orig, strchr(orig, '=') - &orig[0]);
	strcpy(value, strchr(orig, '=') + 1);
	printf("name = %s\n", name);
	printf("value = %s\n", value);
	return (0);
}
