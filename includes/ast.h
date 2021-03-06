/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 07:06:11 by dthan             #+#    #+#             */
/*   Updated: 2021/03/06 13:37:04 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "struct.h"

/*
** =================== BUILT TREE FUNCTIONS ============================
*/

t_astnode	*complete_command(t_token **token);
t_astnode	*list(t_token **token);
t_astnode	*and_or(t_token **token);
t_astnode	*pipeline(t_token **token);
t_astnode	*pipe_sequence(t_token **token);
t_astnode	*command(t_token **token);
t_astnode	*compound_command(t_token **token);
t_astnode	*subshell(t_token **token);
t_astnode	*compound_list(t_token **token);
t_astnode	*term(t_token **token);
t_astnode	*for_clause(t_token **token);
t_astnode	*name(t_token **token);
t_astnode	*in(t_token **token);
t_astnode	*wordlist(t_token **token);
t_astnode	*case_clause(t_token **token);
t_astnode	*case_list_ns(t_token **token);
t_astnode	*case_list(t_token **token);
t_astnode	*case_item_ns(t_token **token);
t_astnode	*case_item(t_token **token);
t_astnode	*pattern(t_token **token);
t_astnode	*if_clause(t_token **token);
t_astnode	*else_part(t_token **token);
t_astnode	*while_clause(t_token **token);
t_astnode	*until_clause(t_token **token);
t_astnode	*function_definition(t_token **token);
t_astnode	*function_body(t_token **token);
t_astnode	*fname(t_token **token);
t_astnode	*brace_group(t_token **token);
t_astnode	*do_group(t_token **token);
t_astnode	*simple_command(t_token **token);
t_astnode	*cmd_name(t_token **token);
t_astnode	*cmd_prefix(t_token **token);
t_astnode	*cmd_suffix(t_token **token);
t_astnode	*redirect_list(t_token **token);
t_astnode	*io_redirect(t_token **token);
t_astnode	*io_file(t_token **token);
t_astnode	*io_number(t_token **token);
t_astnode	*filename(t_token **token);
t_astnode	*io_here(t_token **token);
t_astnode	*here_end(t_token **token);
t_astnode	*newline_list(t_token **token);

void	linebreak(t_token **token);

t_astnode	*separator_op(t_token **token);
t_astnode	*separotor(t_token **token);
t_astnode	*sequential_sep(t_token **token);
t_astnode	*word(t_token **token);
t_astnode	*assignment_word(t_token **token);
t_astnode	*io_file1(t_token **token);
t_astnode	*io_file2(t_token **token);
t_astnode	*io_file3(t_token **token);
t_astnode	*io_file4(t_token **token);
t_astnode	*io_file5(t_token **token);

/*
** ======================= UTILS FUNCTIONS ============================
*/

t_astnode	*build_node(t_astnode_type type);
void		ft_delast(t_astnode *node);
void		clear_ast(t_astnode *ast);

/*
** Debug tree
*/
void        printBinaryTree(t_astnode *t);

#endif
