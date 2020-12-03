#include "shell.h"

static char	**ft_envpath(void)
{
	char	**options;
	int		i;

	options = NULL;
	i = -1;
	while (g_env[++i])
	{
		if (!ft_strncmp(g_env[i], "PATH=", 5))
			options = ft_strsplit(&g_env[i][5], 58);
	}
	return (options);
}

static int	ft_ed_access(char *cmd, char **options)
{
	int		i;
	char	*path;

	i = -1;
	while (options && options[++i])
	{
		path = ft_strjoin(options[i], cmd);
		if (access(path, F_OK) == 0)
		{
			free(cmd);
			free (path);
			ft_arraydel(options);
			return (1);
		}
		free(path);
	}
	ft_arraydel(options);
	return (0);
}

int	ft_check_ed(char *ed)
{
	char	**options;
	char	*cmd;

	options = ft_envpath();
	cmd = ed[0] ?  ft_strjoin("/", ed) : NULL;
	if (!cmd)
	{
		ft_printf("42sh: fc: -e: option requires an argument\n");
		ft_printf("fc: usage: fc [-e ename] [-lnr] [first] [last] or \
		fc -s [pat=rep] [command]\n");
		return (0);
	}
	if (access(cmd, F_OK) == 0)
	{
		free(cmd);
		ft_arraydel(options);
		return (1);
	}
	if (ft_ed_access(cmd, options))
		return (1);
	ft_printf("%s: command not found\n", ed);
	free(cmd);
	free(g_h->tmp);
	g_h->tmp = NULL;
	return (0);
}
