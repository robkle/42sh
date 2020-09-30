/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 08:35:52 by dthan             #+#    #+#             */
/*   Updated: 2020/09/28 10:50:07 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	open_iofile(t_astnode *ast, char *redirect_op)
{
	int fd;

	if (ast->type == AST_io_file && (ft_strequ(">", ast->data) || \
		ft_strequ(">&", ast->data) || ft_strequ(">>", ast->data)))
		open_iofile(ast->left, ast->data);
	else if (ast->type == AST_WORD)
	{
		if (!(ft_strequ(redirect_op, ">&") && (ft_strequ(ast->data, "-") || \
			is_made_of_digits(ast->data))))
		{
			fd = open(ast->data, O_CREAT, 0644);
			close(fd);
		}
	}
}

void	find_iofile(t_astnode *ast)
{
	if (ast->type == AST_io_redirect)
		open_iofile(ast->right, NULL);
	else if (ast->type == AST_pipe_sequence)
	{
		find_iofile(ast->left);
		find_iofile(ast->right);
	}
	else if (ast->type == AST_simple_command)
		find_iofile(ast->right);
	else if (ast->type == AST_cmd_suffix)
	{
		find_iofile(ast->left);
		find_iofile(ast->right);
	}
}

// void	execute_and_or(t_astnode *ast, t_exe *exe, t_job *job)
// {
// 	int status;

// 	if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
// 	{
// 		find_iofile(ast->left);
// 		status = execute_pipeline(ast->left, exe, job);
// 		if (WIFEXITED(status) != 0)
// 			execute_and_or(ast->right, exe, job);
// 	}
// 	else if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
// 	{
// 		find_iofile(ast->left);
// 		status = execute_pipeline(ast->left, exe, job);
// 		if (WIFEXITED(status) == 0)
// 			execute_and_or(ast->right, exe, job);
// 	}
// 	else
// 	{
// 		find_iofile(ast);
// 		execute_pipeline(ast, exe, job);
// 	}
// 	//execute_pipeline(ast, exe);
// }

// need to check for the logical AND OR

void	execute_and_or(t_astnode *ast, t_list *heredoc, t_job *job)
{
	int status;

	if (ast->type == AST_and_or && ft_strequ(ast->data, "&&"))
	{
		find_iofile(ast->left);
		status = execute_pipeline(ast->left, heredoc, job);
		if (WIFEXITED(status) != 0)
			execute_and_or(ast->right, heredoc, job);
	}
	else if (ast->type == AST_and_or && ft_strequ(ast->data, "||"))
	{
		find_iofile(ast->left);
		status = execute_pipeline(ast->left, heredoc, job);
		if (WIFEXITED(status) == 0)
			execute_and_or(ast->right, heredoc, job);
	}
	else
		execute_pipeline(ast, heredoc, job);
	//execute_pipeline(ast, exe);
}
