#include "../includes/libft.h"

void        ft_putnstr(char const *s, size_t len)
{
    size_t  i;

    i = 0;
    while (s[i] && i < len)
    {
        write(STDOUT_FILENO, &s[i++], 1);
    }
}
