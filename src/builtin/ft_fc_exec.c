#include "shell.h"

static char	*ft_fc_e(int *r_ind, char *ed)
{
	int		fd;
	int		i;
	char	*tmp;
	char 	*cmd;
	
	fd = open("/tmp/fc_42sh", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	i = r_ind[0];
	while (i <= r_ind[1])
	{
		write (fd, g_h->hist[i] , ft_strlen(g_h->hist[i]));
		if (i  < r_ind[1])
			write(fd, "\n", 1);
		i++;
	}
	close(fd);
	tmp = ft_strjoin(ed, " /tmp/fc_42sh");
	ft_execute(&tmp);
	free(tmp);
	fd = open("/tmp/fc_42sh", O_RDONLY, 0644);
	cmd = ft_memalloc(4096);
	while (get_next_line(fd, &tmp))
	{
		ft_strcat(cmd, tmp);
		//check quotes
		ft_strcat(cmd, ";");
	}
	close(fd);
	return (cmd);
}

static char	*ft_fc_s(int *r_ind, char *pat)
{
	char	*old;
	char	*new;
	char	*cmd;
	int		i;
	int		j;
	
	old = NULL;
	if (pat)
	{
		old = ft_memalloc(ft_strlen(pat));
		new = ft_memalloc(ft_strlen(pat));
		i = 0;
		while (pat[i] && pat[i] != '=')
		{
			old[i] = pat[i];
			i++;
		}
		j = 0;
		while (pat[++i])
			new[j++] = pat[i];
	}
	cmd = (old && ft_strnequ(g_h->hist[r_ind[0]], old, ft_strlen(old))) ?
		ft_strdup(new) : ft_strdup(g_h->hist[r_ind[0]]);
	return (cmd);
}

int	ft_fc_exec(int flags, char *ed, char **range)
{
	int		r_ind[2];
	char	*cmd;
	char	*tmp;

	r_ind[0] = range[0] ? ft_fc_range(range[0]) : g_h->curr - 2;
	r_ind[1] = range[1] && !flags ? ft_fc_range(range[1]) : r_ind[0];
	if (r_ind[0] < 0 || r_ind[1] < 0)
	{
		ft_printf("bash: fc: history specification out of range\n");
		return (0);
	}
	if (flags & 4 && r_ind[0] < r_ind[1])
		ft_swap(r_ind);
	cmd = flags & 8 ? ft_fc_s(r_ind, range[2]) : ft_fc_e(r_ind, ed);
	tmp = g_h->hist[g_h->curr - 1];
	g_h->hist[g_h->curr - 1] = ft_strdup(cmd);
	free(tmp);
	ft_execute(&cmd);
	free(cmd);
	return (1);
}
