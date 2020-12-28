#include "shell.h"

void		ft_swap(int *nums)
{
	int	tmp;
	
	tmp = nums[0];
	nums[0] = nums[1];
	nums[1] = tmp;
}
