#include "shell.h"

// this is for l option
// int init_range_first()
// {
// 	int max;
// 	int pos;
	
// 	max = g_shell.history->curr;
// 	pos = max - 16; // 16 is the default if first is not set
// 	if (pos == )
// }

int	fc_exec(int ops, char *editor, char **block)
{
	if (ops & FC_S_OP)
		return (fc_s_op(block[REPLACE], block[FIRST]));
	return (fc_e_op(ops, editor, block[FIRST], block[LAST]));
}

