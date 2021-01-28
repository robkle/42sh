#include "shell.h"

static void		ft_init_str(char *str, size_t n_size)
{
	size_t		i;

	i = -1;
	while (++i < n_size)
		str[i] = '\0';
}

static unsigned long	ft_numlen(long long nb)
{
	unsigned long	len;

	len = 0;
	if (!nb)
		return (1);
	else if (nb < 0)
		len++;
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_llitoa(long long n)
{
	size_t		i;
	size_t		n_size;
	char		*str;

	i = 0;
	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	n_size = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (n_size + 1));
	if (str == 0)
		return (0);
	ft_init_str(str, n_size);
	str[n_size] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i += 1;
	}
	while (i < n_size--)
	{
		str[n_size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
