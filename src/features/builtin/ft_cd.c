/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2020/12/28 23:09:42 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int cd_no_arg(void)
{
	char *var_pwd;
	char pwd[PATH_MAX];
	char *home;
	char *old;

	if (!(home = get_var("HOME", g_shell.env, VAL)))
	{
		ft_dprintf(2, "%s cd: HOME not set\n", SHELL_NAME);
		return (EXIT_FAILURE);
	}
	if ((getcwd(pwd, PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
		ft_strcpy(old, pwd);
	if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
		ft_strcpy(pwd, home);
	if ((chdir(home)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int ft_cd_exchange(void)
{
	char pwd[PATH_MAX];
	char *old;
	char *var_pwd;
	char *temp;

	if ((temp = (char *)malloc(PATH_MAX)) == NULL)
		return (EXIT_FAILURE);
	temp[0] = '\0';
	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
	{
		getcwd(pwd, PATH_MAX);
		ft_strcpy(temp, pwd);
		if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
			ft_strcpy(var_pwd, old);
		ft_strcpy(pwd, old);
		chdir(pwd);
		ft_strcpy(old, temp);
		ft_printf("%s\n", pwd);
	}
	else
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_strdel(&temp);
	return (EXIT_SUCCESS);
}

void replace_curpath(t_process *c, const t_opt opt)
{
}

void convert_curpath(char *curpath, char *directory)
{
}

//static void cd_root(t_process *c)
void cd_root(char *curpath, char *dir, t_opt opt)
{
	char *old;
	char *pwd;
	char buf[PATH_MAX];

	if ((pwd = get_var("PWD", g_shell.env, VAL)) == NULL)
		set_pwd();
	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
		ft_strcpy(old, pwd);
	else
		set_oldpwd(pwd);
	if (opt.opt_apply & BUILTIN_CD_OPT_P)
	{
		getcwd(buf, sizeof(buf));
		ft_strcpy(pwd, buf);
	}
	else if (ft_strlen(curpath) + 1 > PATH_MAX &&
			 ft_strstr(curpath, pwd) == curpath)
	{
		look_for_relative_path(curpath, pwd, buf);
		ft_strcpy()
	}

	if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
		ft_strcpy(var_pwd, pwd);
	// else
	// 	need to set pwd
}

void execute_cd(char *dir, char curpath, t_opt opt)
{
	if (dir[0] == '/')
	{
		curpath = dir;
		cd_root(curpath, dir, opt);
	}
}

void step5sub(char *dir, char **curpath, char **path_split, char buf[PATH_MAX])
{
	int i;

	i = 0;
	while (path_split[i])
	{
		ft_strcpy(buf, path_split[i]);
		if (buf[ft_strlen(buf) - 1] != '/')
			ft_strcat(buf, "/");
		ft_strcat(buf, dir);
		if (possible_to_access_dir(buf) == EXIT_SUCCESS)
		{
			*curpath = ft_strcpy(*curpath, buf);
			return ;
		}
		i++;
	}
}

void a(char *directory, char *curpath, t_opt *opt)
{
	int len;
	int i;

	len = (int)ft_strlen(curpath);
	i = 1;
	while (i < len - 1)
	{
		if (curpath[i - 1] == '/' && curpath[i] == '.' && curpath[i + 1] == '/')
		{
			curpath[i] = '\0';
			curpath[i + 1] = '\0';
			if (i + 2 < len - 1)
				ft_strcpy(&(curpath[i]), &(curpath[i + 2]));
		}
		++i;	
	}
}

char chk_prcding_comp(char *cuarpath, int i)
{
	//if there is a prcding comp and the comp is neither dot-dot nor root
	//I can say there is a prcding comp
	int comp_len;

	comp_len = 0;
	while (i > 0)
	{
		
	}
	return (EXIT_FAILURE);
}
//여기하고있었음 
void b(char *directory, char *curpath, t_opt *opt)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(curpath);
	while (i < len)
	{
		if (curpath[i] == '/' && curpath[i + 1] == '.' && \
			curpath[i + 2] == '.' && curpath[i + 3] == '/' && \
			chk_prcding_comp(curpath, i))
		{

		}
	}
}

//opt may be unnecessary in step8
void step8(char *directory, char *curpath, t_opt *opt)
{
	a(directory, curpath, opt);
	b(directory, curpath, opt);
	c(curpath, opt, buf);
}

void step10(char *directory, char *converted_cpath, char *original_cpath, t_opt *opt)
{
	char *pwd;

	if (chdir(curpath) == -1)
	{
		ft_dprintf(2, "%s: cd: chdir() system call failed", SHELL_NAME);
		return (EXIT_FAILURE);
	}
	if (!(opt->opt_apply & BUILTIN_CD_OPT_P))
	{
		if ((pwd = ft_getenv("PWD")))
			ft_strcpy(pwd, curpath);
	}



	if (opt.opt_apply == -1)
		return (error_monitor("42sh: cd: ", opt.invalid_opt,
							  ": invalid option", EXIT_FAILURE));
	set_curpath() else if (opt.opt_apply != BUILTIN_NO_OPT)
		replace_curpath(c, opt);
	if (ft_strequ(c->av[opt.operand_count + 1], "-"))
		//		return (ft_cd_exchange(c));
		return (ft_cd_pathfinder(c));


}

//done
void step7(char *directory, char *curpath, t_opt *opt)
{
	char *pwd;
	char *tmp;

	if (opt->opt_apply & BUILTIN_CD_OPT_P)
		return (step10(directory, curpath, opt));
	if (*curpath != '/')
	{
		if (((pwd = ft_getenv("PWD")) == NULL))
			return (step8(directory, curpath, opt));
		else if (pwd[ft_strlen(pwd - 1)] == '/')
			curpath = ft_strjoin((const char*)pwd, (const char*)curpath);
		else
		{
			tmp = ft_strjoin((const char*)pwd, "/");
			curpath = ft_strjoin_and_free_string1(tmp, curpath); 
		}
		return (step8(directory, curpath, opt));
	}
}

void step5(char *directory, t_opt *opt)
{
	int i;
	char *pathnames;
	char **path_split;
	char *path;

	pathnames = ft_getvar("CDPATH");
	path_split = ft_strsplit(pathnames, ":");
	i = 0;
	while (path_split[i])
	{
		if (path_split[i][ft_strlen(path_split[i]) - 1] != '/')
			path = ft_strjoin((const char*)path_split[i], "/");
		path = ft_strjoin_and_free_string1(path, directory);
		if (!access((const char*)path, X_OK))
			return (step7(directory, path, opt));
		++i;
	}
	return (step7(directory, directory, opt));
}

/*
** Refer to the CD section in the POSIX standard document if you need to analyze this function
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

int ft_cd(t_process *c)
{
	t_opt opt;
	char *directory;

	init_opt(&opt, BUILTIN_CD_OPT_SET);
	opt.opt_apply |= BUILTIN_CD_OPT_L;
	check_builtin_options(c->av, &opt);
	if (opt.opt_apply = BUILTIN_INVALID_OPT)
	{
		ft_dprintf(2, "%s: cd: %s: invalid option", SHELL_NAME, opt.invalid_opt);
		return (EXIT_FAILURE);
	}
	if (opt.opt_apply & BUILTIN_CD_OPT_P && opt.opt_apply & BUILTIN_CD_OPT_L)
		opt.opt_apply = BUILTIN_CD_OPT_P;
	if (c->av[opt.operand_count + 2] != NULL)
	{
		ft_dprintf(2, "%s: cd: too many arguments\n", SHELL_NAME);
		return (EXIT_FAILURE);
	}
	if (c->av[opt.operand_count + 1] == NULL)
		return (cd_no_args());
	directory = c->av[opt.operand_count + 1];
	if (*directory == '/' || ft_strnstr(directory, "..", 2) || ft_strnstr(directory, ".", 1)) //step 3, 4
		return (step7(directory, directory, &opt));
	else if ((ft_getvar("CDPATH")) != NULL)
		return (step5(directory, &opt));
	return (step7(directory, directory, &opt));
}




