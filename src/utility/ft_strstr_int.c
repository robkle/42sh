#include "shell.h"

int	ft_strstr_int(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

