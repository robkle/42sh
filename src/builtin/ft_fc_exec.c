#include "shell.h"

static char *ft_fc_e_exec(void)
{
	char	*line;
	char	*cmd;
	int		fd;

	fd = open("/tmp/fc_42sh", O_RDONLY, 0644);
	cmd = ft_memalloc(4096);
	while (get_next_line(fd, &line))
	{
		if (cmd[0] && !ft_check_cont(cmd))
			ft_strcat(cmd, ";");
		ft_strcat(cmd, line);
		if (ft_check_cont(cmd))
			ft_strcat(cmd, "\n");
	}
	close(fd);
	return (cmd);
}

static char	*ft_fc_e(int *r_ind, char *ed)
{
	int		fd;
	int		i;
	char	*tmp;
	
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
	return (ft_fc_e_exec());
}

static char *ft_fc_s_cmd(char *str, char *old, char *new)
{
	char	*cmd;
	int		i;
	int		j;

	cmd = ft_memalloc(4096);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (old[j] == str[i + j])
		{
			if (old[j + 1] == '\0')
			{
				ft_strcat(cmd, new);
				i += j;
				break;
			}
			j++;
		}
		if (j == 0)
			cmd[ft_strlen(cmd)] = str[i];
		i++;
	}
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
	cmd = old ? ft_fc_s_cmd(g_h->hist[r_ind[0]], old, new) :
		g_h->hist[r_ind[0]];
	return (cmd);
}

int	ft_fc_exec(int flags, char *ed, char **range)
{
	int		r_ind[2];
	char	*cmd;
	//char	*tmp;//UNUSED

	//r_ind[0] = range[0] ? ft_fc_range(range[0]) : g_h->curr - 2;
	r_ind[0] = range[0] ? ft_fc_range(range[0]) : g_h->curr - 1; //NEW
	r_ind[1] = range[1] && !flags ? ft_fc_range(range[1]) : r_ind[0];
	if (r_ind[0] < 0 || r_ind[1] < 0)
	{
		ft_printf("42sh: fc: history specification out of range\n");
		return (0);
	}
	if (flags & 4 && r_ind[0] < r_ind[1])
		ft_swap(r_ind);
	cmd = flags & 8 ? ft_fc_s(r_ind, range[2]) : ft_fc_e(r_ind, ed);
	free(g_h->tmp);
	g_h->tmp = ft_strdup(cmd);
	/*tmp = g_h->hist[g_h->curr - 1];
	g_h->hist[g_h->curr - 1] = ft_strdup(cmd);
	free(tmp);*///NO NEED FOR THIS ANYMORE
	ft_execute(&cmd);
	free(cmd);
	return (1);
}
