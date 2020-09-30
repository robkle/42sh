/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:39:32 by dthan             #+#    #+#             */
/*   Updated: 2020/09/30 06:44:42 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static void		exchange_src_des_for_less(t_exe *exe)
// {
// 	char		*temp;
// 	t_redirect	*trav;

// 	trav = exe->redi;
// 	while (trav)
// 	{
// 		if (ft_strequ(trav->redirect_op, "<") || 
// 				ft_strequ(trav->redirect_op, "<<") || 
// 				ft_strequ(trav->redirect_op, "<&"))
// 		{
// 			temp = trav->redirect_des;
// 			trav->redirect_des = trav->redirect_src;
// 			trav->redirect_src = temp;
// 		}
// 		trav = trav->next;
// 	}
// }

void			clear_ast(t_astnode *ast)
{
	//printBinaryTree(ast);
	if (ast->left)
		clear_ast(ast->left);
	if (ast->right)
		clear_ast(ast->right);
	ft_delast(ast);
}

// void			clear_exe(t_exe *exe)
// {
// 	void *ptr;

// 	while (exe->heredoc)
// 	{
// 		ft_strdel(&exe->heredoc->heredoc);
// 		ptr = exe->heredoc;
// 		exe->heredoc = exe->heredoc->next;
// 		free(ptr);
// 	}
// 	while (exe->redi)
// 	{
// 		ptr = exe->redi;
// 		exe->redi = exe->redi->next;
// 		free(ptr);
// 	}
// 	free(exe->av);
// }

// static void		clear_redi(t_exe *exe)
// {
// 	t_redirect	*trav;
// 	t_redirect	*temp_trav;

// 	trav = exe->redi;
// 	temp_trav = NULL;
// 	while (trav)
// 	{
// 		temp_trav = trav;
// 		trav = trav->next;
// 		free(temp_trav);
// 	}
// 	exe->redi = NULL;
// }

char			*get_job_command(char **av)
{
	char		*command;
	int			i;

	command = ft_strdup(av[0]);
	i = 0;
	while (av[++i])
	{
		command = ft_strjoin_and_free_string1(command, " ");
		command = ft_strjoin_and_free_string1(command, av[i]);
	}
	return (command);
}

// int				execute_simple_command(t_astnode *ast, t_exe *exe, t_job *job)
// {
// 	// Job? get command info for job struct
// 	int			status;

// 	if (ast->type == AST_simple_command)
// 	{
// 		get_av_cmd_name(ast->left, exe);
// 		get_av_cmd_suffix(ast->right, exe, 0);
// 		exchange_src_des_for_less(exe);
// 	}
// 	else
// 		get_av_cmd_name(ast, exe);
// 	status = run(exe, job);
// 	if (exe->redi)
// 		clear_redi(exe);
// 	return (status);
// }


void	execute_cmd_name(t_astnode *ast, t_job *j, t_process *p)
{
	if (ast->type == AST_WORD)
	{
		p->ac = 1;
		p->av[0] = ast->data;
		p->av[1] = NULL;
		j->command = ft_strdup(p->av[0]);
	}
}

// int create_file(char *path)
// {
// 	int fd;
// 	fd = open();
// 	if (fd == -1)
// 		return (EXIT_FAILURE);
// 	close(fd);
// 	return (EXIT_SUCCESS);
// }

void	execute_io_redirect(t_astnode *ast, t_list *hd , t_process *p)
{
	t_redirect		redi;
	t_list *node;
	if (ast->left->type == AST_io_file)
	{
		redi.redirect_op = ast->left->data;
		if (ft_strequ(redi.redirect_op, "<") ||
			ft_strequ(redi.redirect_op, "<&"))
		{
			redi.redirect_src = ast->left->left->data;
			redi.redirect_des = ast->data;
		}
		else
		{
			redi.redirect_src = ast->data;
			redi.redirect_des = ast->left->left->data;
		}
	}
	else if (ast->left->type == AST_io_here)
	{
		redi.redirect_op = ast->left->data;
		redi.redirect_src = (char*)hd->content;
		redi.redirect_des = ast->data;
		hd = hd->next;
	}
	node = ft_lstnew(&redi, sizeof(t_redirect));
		if (p->redi == NULL)
	p->redi = node;
	else
		ft_lstadd_tail(&(p->redi), node);
}

void	execute_cmd_suffix(t_astnode *ast, t_list *hd, t_job *j, t_process *p)
{
	if (ast->type == AST_WORD)
	{
		p->ac++;
		p->av[p->ac - 1] = ast->data;
		p->av[p->ac] = NULL;
		ft_strjoin_and_free_string1(j->command, " ");
		ft_strjoin_and_free_string1(j->command, p->av[p->ac - 1]);
	}
	else if (ast->type == AST_cmd_suffix)
	{
		if (ast->left->type == AST_io_redirect && ast->right->type == AST_cmd_suffix)
		{
			execute_io_redirect(ast->left, hd, p);
			execute_cmd_suffix(ast->right, hd, j, p);
		}
		else if (ast->left->type == AST_WORD && ast->right->type == AST_cmd_suffix)
		{
			p->ac++;
			p->av[p->ac - 1] = ast->left->data;
			p->av[p->ac] = NULL;
			ft_strjoin_and_free_string1(j->command, " ");
			ft_strjoin_and_free_string1(j->command, p->av[p->ac - 1]);
			// we should make a new function for ast_word
			execute_io_redirect(ast->right, hd, p);
		}
	}
	else if (ast->type == AST_io_redirect)
		execute_io_redirect(ast, hd, p);
}

void init_process(t_process *p, t_job *j)
{
	// ft_bzero(p, sizeof(t_process));
	p->av = (char**)malloc(sysconf(_SC_ARG_MAX));
	p->ac = 0;
	p->pid = 0;
	p->stdin = j->stdin;
	p->stdout = j->stdout;
	p->stderr = j->stderr;
	p->redi = NULL;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
}

void print_process(t_process p)
{
	ft_printf("=============\nprocess info:\nac: %d\nav[0]: %s\npid: %d\nstdin: %d\nstdout: %d\nstderr: %d\n==================\n", p.ac, p.av[0], p.pid, p.stdin, p.stdout, p.stderr);
}

int				execute_simple_command(t_astnode *ast, t_list *heredoc, t_job *job)
{
	int status;
	t_list *node;
	t_process process;

	status = 1; //need to look at this variable!!!
	init_process(&process, job);
	if (ast->type == AST_simple_command)
	{
		execute_cmd_name(ast->left, job, &process);
		execute_cmd_suffix(ast->right, heredoc, job, &process);
	}
	else
		execute_cmd_name(ast, job, &process);
	node = ft_lstnew(&process, sizeof(t_process));
	if (job->process == NULL)
		job->process = node;
	else
		ft_lstadd_tail(&(job->process), node);
	//extent the job->command here
	// print_process(process);
	lauch_process(job, &process); // no need to pass address, change later
	return (status);
}
