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


// static int ft_cd_exchange(void)
// {
// 	char pwd[PATH_MAX];
// 	char *old;
// 	char *var_pwd;
// 	char *temp;

// 	if ((temp = (char *)malloc(PATH_MAX)) == NULL)
// 		return (EXIT_FAILURE);
// 	temp[0] = '\0';
// 	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
// 	{
// 		getcwd(pwd, PATH_MAX);
// 		ft_strcpy(temp, pwd);
// 		if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
// 			ft_strcpy(var_pwd, old);
// 		ft_strcpy(pwd, old);
// 		chdir(pwd);
// 		ft_strcpy(old, temp);
// 		ft_printf("%s\n", pwd);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	ft_strdel(&temp);
// 	return (EXIT_SUCCESS);
// }

// void replace_curpath(t_process *c, const t_opt opt)
// {
// }

// void convert_curpath(char *curpath, char *directory)
// {
// }

//static void cd_root(t_process *c)
// void cd_root(char *curpath, char *dir, t_opt opt)
// {
// 	char *old;
// 	char *pwd;
// 	char buf[PATH_MAX];

// 	if ((pwd = get_var("PWD", g_shell.env, VAL)) == NULL)
// 		set_pwd();
// 	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
// 		ft_strcpy(old, pwd);
// 	else
// 		set_oldpwd(pwd);
// 	if (opt.applied & BUILTIN_CD_OPT_P)
// 	{
// 		getcwd(buf, sizeof(buf));
// 		ft_strcpy(pwd, buf);
// 	}
// 	else if (ft_strlen(curpath) + 1 > PATH_MAX &&
// 			 ft_strstr(curpath, pwd) == curpath)
// 	{
// 		look_for_relative_path(curpath, pwd, buf);
// 		ft_strcpy()
// 	}

// 	if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
// 		ft_strcpy(var_pwd, pwd);
// 	// else
// 	// 	need to set pwd
// }

// void execute_cd(char *dir, char curpath, t_opt opt)
// {
// 	if (dir[0] == '/')
// 	{
// 		curpath = dir;
// 		cd_root(curpath, dir, opt);
// 	}
// }

// void step5sub(char *dir, char **curpath, char **path_split, char buf[PATH_MAX])
// {
// 	int i;

// 	i = 0;
// 	while (path_split[i])
// 	{
// 		ft_strcpy(buf, path_split[i]);
// 		if (buf[ft_strlen(buf) - 1] != '/')
// 			ft_strcat(buf, "/");
// 		ft_strcat(buf, dir);
// 		if (possible_to_access_dir(buf) == EXIT_SUCCESS)
// 		{
// 			*curpath = ft_strcpy(*curpath, buf);
// 			return ;
// 		}
// 		i++;
// 	}
// }

void step_a(char *curpath)
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
			if (i + 1 < len)
				ft_strcpy(&(curpath[i]), &(curpath[i + 2]));
			len = ft_strlen(curpath);
		}
		else
			++i;
	}
}

//stick to b
static char chk_prcding_comp(char *curpath, int idx)
{
	char dotdot[5];

	ft_strcpy(dotdot, "/../");
	if (idx == 0)
		return (FALSE);
	if (idx - 3 >= 0 && ft_strnstr(&curpath[idx - 3], dotdot, 4))
		return (FALSE);
	return (TRUE);
}

static char		check_access(char *path)
{
	t_stat		sb;

	stat(path, &sb);
	if (access(path, F_OK))
	{
		ft_dprintf(2, "%s: cd: %s: No such file or directory\n", \
			SHELL_NAME, path);
		return (EXIT_FAILURE);
	}
	else if ((sb.st_mode & F_TYPE_MASK) != S_IFDIR)
	{
		ft_dprintf(2, "%s: cd: %s: Not a directory\n", SHELL_NAME, path);
		return (EXIT_FAILURE);
	}
	else if (access(path, X_OK))
	{
		ft_dprintf(2, "%s: cd: %s: Permission denied\n", SHELL_NAME, path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int			get_pos_prcding_comp(char *path, int idx)
{
	while (--idx > 0)
		if (path[idx] == '/')
			break;
	return (idx);
}

char step_b(char *curpath)
{
	int i;
	int len;
	//char dotdot[5];
	char dotdot[4];
	int pos_prcding_comp;

	i = -1;
	len = (int)ft_strlen(curpath);
	//ft_strcpy(dotdot, "/../");
	ft_strcpy(dotdot, "/..");
	//while (++i < len - 3)
	while (++i < len - 2)
	{
		if (ft_strnstr(&curpath[i], dotdot, 3) && chk_prcding_comp(curpath, i))
		{
			if ((check_access(curpath)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			pos_prcding_comp = get_pos_prcding_comp(curpath, i);
            ft_strcpy(&curpath[i + 1], "\0\0\0");
			// curpath[i + 1] = '\0';
			// curpath[i + 2] = '\0';
			// curpath[i + 3] = '\0';
			if (i + 3 < len)
				ft_strcpy(&curpath[i + 1], &(curpath[i + 3]));
			len = ft_strlen(curpath);
		}
	}
	return (EXIT_SUCCESS);
}

char step_c(char *curpath)
{
	int idx;
	int len;
	int	slash_count;

	idx = -1;
	len = (int)ft_strlen(curpath);
	while (++idx < len)
	{
		if (curpath[idx] == '/')
		{
			slash_count = idx;
			while (slash_count == '/')
				++slash_count;
			slash_count = slash_count - idx;
			if (idx + slash_count < len)
				ft_strcpy(&(curpath[idx]), &(curpath[idx + slash_count]));
			len = ft_strlen(curpath);
		}
	}
	if (len == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	manipulate_var(t_cd *cd)
{
	char 	*pwd;
	char	*oldpwd;
	char	absolute_path[PATH_MAX];

	if ((pwd = ft_getenv("PWD")) && (oldpwd = ft_getenv("OLDPWD")))
		ft_strcpy(oldpwd, pwd);
	if (!(cd->opt.applied & BUILTIN_CD_OPT_P))
	{
		if (pwd && cd->prev_curpath)
			ft_strcpy(pwd, cd->prev_curpath);
		else if (pwd && cd->curpath)
			ft_strcpy(pwd, cd->curpath);
	}
	else
	{
		ft_memset((void*)absolute_path, 0, sizeof(absolute_path));
		if (getcwd(absolute_path, sizeof(absolute_path)) != NULL && pwd)
			ft_strcpy(pwd, absolute_path);
	}
}

int step10(t_cd *cd)
{
	if (chdir(cd->curpath) == -1)
	{
		ft_dprintf(2, "%s: cd: chdir() system call failed\n", SHELL_NAME);
		return (EXIT_FAILURE);
	}
	manipulate_var(cd);
	if (cd->print_info == TRUE)
		ft_printf("%s\n", cd->curpath);
	return (EXIT_SUCCESS);
}

static char *cnvt_curpath_to_relative_path(char *curpath)
{
	char	*relative_path;
	char	buf[PATH_MAX];

	ft_memset(buf, 0, PATH_MAX);
	getcwd(buf, PATH_MAX);
	relative_path = &curpath[ft_strlen(buf) - 1];
	relative_path[0] = '.';
	return (ft_strdup(relative_path));
}

//stick to step9
static char is_initial_path_of(char *curpath, char *path_var)
{
	return (ft_strnstr(curpath, path_var, ft_strlen(path_var)) != NULL);
}

//stick to step 9
# define NULL_LEN 1

int step9(t_cd *cd)
{
	char *var;
	size_t cpath_len;
	size_t dir_len;

	cpath_len = ft_strlen(cd->curpath);
	dir_len = ft_strlen(cd->directory);
	if (cpath_len + NULL_LEN > PATH_MAX && dir_len + NULL_LEN < PATH_MAX)
	{
		var = ft_getenv("PWD");
		if (var != NULL)
			var = ft_strdup(var);
		if (var[ft_strlen(var) - 1] != '/')
			var = ft_strjoin_and_free_string1(var, "/");
		if (is_initial_path_of(cd->curpath, var))
		{
			cd->prev_curpath = cd->curpath;
			cd->curpath = cnvt_curpath_to_relative_path(cd->curpath);
		}
		free(var);
	}
	return (step10(cd));
}

int step8(t_cd *cd)
{
	step_a(cd->curpath);
	if (step_b(cd->curpath) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (step_c(cd->curpath) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (step9(cd));
}


//done
int step7(t_cd *cd)
{
	char *pwd;
	char *tmp;

	if (cd->opt.applied & BUILTIN_CD_OPT_P)
		return (step10(cd));
	if (*cd->curpath != '/')
	{
		if (((pwd = ft_getenv("PWD")) == NULL))
			return (step8(cd));
		else if (pwd[ft_strlen(pwd - 1)] == '/')
			cd->curpath = ft_strjoin((const char*)pwd, (const char*)cd->curpath);
		else
		{
			tmp = ft_strjoin((const char*)pwd, "/");
			cd->curpath = ft_strjoin_and_free_string1(tmp, cd->curpath); 
		}
	}
	return (step8(cd));
}

char		step6(t_cd *cd)
{
	cd->curpath = ft_strdup(cd->directory);
	return (step7(cd));
}

static char is_valid_cdpath(t_cd *cd, char *path)
{
	size_t path_len;

	path_len = ft_strlen(path);
	if (path[path_len - 1] != '/')
		path = ft_strjoin_and_free_string1(ft_strjoin((const char*)path, "/"), cd->directory);
	else
		path = ft_strjoin((const char*)path, cd->directory);
	if (!access((const char*)path, X_OK))
	{
		ft_strdel(&path);
		return (TRUE);
	}
	else
	{
		ft_strdel(&path);
		return (FALSE);
	}
}

static char *get_curpath_from_cdpath(t_cd *cd, char *path)
{
	size_t path_len;

	path_len = ft_strlen(path);
	if (path[path_len - 1] != '/')
		path = ft_strjoin_and_free_string1(ft_strjoin((const char*)path, "/"), cd->directory);
	else
		path = ft_strjoin((const char*)path, cd->directory);
	return (path);
}

static char	is_valid_relative_path(char *directory)
{
	char	*path;

	path = ft_strdup("./");
	path = ft_strjoin_and_free_string1(path, directory);
	if (!access((const char*)path, X_OK))
	{
		ft_strdel(&path);
		return (TRUE);
	}
	else
	{
		ft_strdel(&path);
		return (FALSE);
	}
}

static char	*get_curpath_from_directory(t_cd *cd)
{
	char	*path;

	path = ft_strdup("./");
	path = ft_strjoin_and_free_string1(path, cd->directory);
	return (path);
}

int step5(t_cd *cd)
{
	int i;
	char **path_split;

	//need to implement ft_getvar first
	if(ft_getvar("CDPATH") != NULL)
	{
		path_split = ft_strsplit(ft_getvar("CDPATH"), ':');
		i = -1;
		while (path_split[++i])
		{
			if(cd->curpath == NULL && is_valid_cdpath(cd, path_split[i]))
			{
				cd->curpath = get_curpath_from_cdpath(cd, path_split[i]);
				cd->print_info = TRUE;
			}
		}
		ft_strlst_del(&path_split, i);
	}
	if (cd->curpath == NULL && is_valid_relative_path(cd->directory))
		cd->curpath = get_curpath_from_directory(cd);
	if (cd->curpath == NULL)
		return (step6(cd));
	else
		return (step7(cd));
}

/*
** Refer to the CD section in the POSIX standard document if you need to analyze this function
** link: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

// static int cd_no_arg(void)
// {
// 	char *var_pwd;
// 	char pwd[PATH_MAX];
// 	char *home;
// 	char *old;

// 	if (!(home = get_var("HOME", g_shell.env, VAL))) //step1
// 	{
// 		ft_dprintf(2, "%s cd: HOME not set\n", SHELL_NAME);
// 		return (EXIT_FAILURE);
// 	}
// 	if ((getcwd(pwd, PATH_MAX)) == NULL)
// 		return (EXIT_FAILURE);
// 	if ((old = get_var("OLDPWD", g_shell.env, VAL)))
// 		ft_strcpy(old, pwd);
// 	if ((var_pwd = get_var("PWD", g_shell.env, VAL)))
// 		ft_strcpy(pwd, home);
// 	if ((chdir(home)) == -1)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

static char	basic_error_check(char **av, t_opt opt)
{
	char	status;

	status = 0;
	if (opt.applied == BUILTIN_INVALID_OPT)
		status = ft_dprintf(2, "%s: cd: %s: invalid option", SHELL_NAME, opt.invalid_opt);
	if (av[opt.operand_count + 2] != NULL)
		status = ft_dprintf(2, "%s: cd: too many arguments\n", SHELL_NAME);
	if (av[opt.operand_count + 1] == NULL && !ft_getenv("HOME")) //step1
		status = ft_dprintf(2, "%s cd: HOME not set\n", SHELL_NAME);
	return (status);	
}

// if (ft_strequ(c->av[opt.operand_count + 1], "-"))
// 		//		return (ft_cd_exchange(c));
// 		return (ft_cd_pathfinder(c));


static void	integrate_cd_options(t_opt *opt)
{
	opt->applied |= BUILTIN_CD_OPT_L;
	if (opt->applied & BUILTIN_CD_OPT_P && opt->applied & BUILTIN_CD_OPT_L)
		opt->applied = BUILTIN_CD_OPT_P;
}

static char	get_directory(t_process *c, t_cd *cd, t_opt *opt)
{
	if (c->av[opt->operand_count + 1] == NULL)
	{
		if ((ft_getenv("HOME") == NULL))
		{
			ft_dprintf(2, "%s: cd: HOME not set\n", SHELL_NAME);
			return (EXIT_FAILURE);
		}
		cd->directory = ft_getenv("HOME");
	}
	else if (ft_strequ(c->av[opt->operand_count + 1], "-"))
	{
		if ((ft_getenv("OLDPWD") == NULL))
		{
			ft_dprintf(2, "%s: cd: OLDPWD not set\n", SHELL_NAME);
			return (EXIT_FAILURE);
		}
		cd->print_info = TRUE;
		cd->directory = ft_getenv("OLDPWD");
	}
	else if (c->av[opt->operand_count + 1] != NULL)
		cd->directory = c->av[opt->operand_count + 1];
	return (EXIT_SUCCESS);
}



int			ft_cd(t_process *c)
{
	t_opt	opt;
	t_cd	cd;

	ft_memset(&cd, 0, sizeof(t_cd));
	init_opt(&opt, BUILTIN_CD_OPT_SET);
	check_builtin_opts(c->av, &opt);
	if (basic_error_check(c->av, opt) != 0)
		return (EXIT_FAILURE);
	integrate_cd_options(&opt);
	cd.opt = opt;
	if (get_directory(c, &cd, &opt) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (*(cd.directory) == '/') // step3
	{
		cd.curpath = ft_strdup(cd.directory);
		return (step7(&cd));
	}
	else if (ft_strnstr(cd.directory, "..", 2) || ft_strnstr(cd.directory, ".", 1)) //step4
		return (step6(&cd));
	else
		return (step5(&cd));
}
