/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 13:36:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/19 12:06:39 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
 *  Executes the src code represented by an AST built by the parser
*******************************************************************************/
int	execute_src(t_t_node **root, t_vars *vars, t_info *info)
{
	int	exit_st;

	if (!root)
		return (1);
	if ((*root)->p_type == PARSER_COMMAND)
		exit_st = execute_command(root, vars, info);
	else if ((*root)->p_type == PARSER_PIPE)
		exit_st = execute_pipe(root, vars, info);
	else if ((*root)->p_type == PARSER_REDIR)
		exit_st = execute_redirection(root, vars, info);
	else
	{
		ft_putendl_fd("Not able to execute right now", STDERR_FILENO);
		exit_st = 127;
	}
	info->exit_code = exit_st;
	return (exit_st);
}

/*******************************************************************************
 *  Experiment to execute a redirection node 
 * -- For now assumming only out redirections are possible
*******************************************************************************/
int	execute_redirection(t_t_node **root, t_vars *vars, t_info *info)
{
	t_redir_node	*cur;
	int				std_out;
	int				std_in;
	int				exit_code;

	exit_code = 0;
	if (!root || !vars || !info)
		return (1);
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (std_out == -1 || std_in == -1)
		return (-1);
	cur = (*(*root)->redirs);
	exec_redirection_aux(cur, info, &exit_code);
	info->exit_code = exit_code;
	if (exit_code == 0)
		if ((*root)->tokens->head)
			exit_code = execute_command(root, vars, info);
	if (dup2(std_out, STDOUT_FILENO) == -1 || dup2(std_in, STDIN_FILENO) == -1)
		return (-1);
	close(std_out);
	close(std_in);
	return (exit_code);
}

int	call_redir(t_redir_node *cur, t_info *info)
{
	t_redir_node	*operator_node;

	(void)info;
	operator_node = cur;
	cur = cur->next;
	if (cur)
	{
		if (operator_node->type == TKN_REDIR_OUT)
			return (exec_redir_out(cur->file));
		else if (operator_node->type == TKN_REDIR_OUT_APP)
			return (exec_redir_append(cur->file));
		else if (operator_node->type == TKN_REDIR_IN)
			return (exec_redir_in(cur->file));
		else if (operator_node->type == TKN_HEREDOC)
			return (exec_heredoc(cur->file));
	}
	return (1);
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND
*******************************************************************************/
int	execute_command(t_t_node **root, t_vars *vars, t_info *info)
{
	t_token_node	*node;
	int				exit_status;

	if (!root)
		return (1);
	node = skip_empty_nodes(root);
	if (!node)
		return (0);
	if (is_builtin_type(node->token->type)
		|| (node->token->type == TKN_VAR_NAME))
	{
		exit_status = execute_builtin(root, vars, info);
		info->exit_code = exit_status;
		return (exit_status);
	}
	if (node->token->type == TKN_WORD)
	{
		exit_status = execute_ext_command(root, vars, info);
		info->exit_code = exit_status;
		return (exit_status);
	}
	info->exit_code = 1;
	return (1);
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND and the head of the
 * token list is one of the builtins
*******************************************************************************/
int	execute_builtin(t_t_node **root, t_vars *vars, t_info *info)
{
	t_token_list	*tokens;
	t_token			*token;

	if (!root || !vars || !info)
		return (1);
	tokens = (*root)->tokens;
	token = tokens->head->token;
	if (token->type == TKN_ECHO || is_cmd(token->lexeme, "echo"))
		return (execute_echo(tokens));
	if (token->type == TKN_CD || is_cmd(token->lexeme, "cd"))
		return (execute_cd(tokens, vars));
	if (token->type == TKN_PWD || is_cmd(token->lexeme, "pwd"))
		return (pwd_builtin());
	if (token->type == TKN_EXPORT || is_cmd(token->lexeme, "export"))
		return (execute_export(tokens, vars));
	if (token->type == TKN_UNSET || is_cmd(token->lexeme, "unset"))
		return (execute_unset(tokens, &vars));
	if (token->type == TKN_ENV || is_cmd(token->lexeme, "env"))
		return (env_builtin(vars));
	if (token->type == TKN_EXIT || is_cmd(token->lexeme, "exit"))
		return (execute_exit(*root, tokens, vars, info));
	if (token->type == TKN_VAR_NAME)
		return (execute_assignment(tokens, vars));
	return (127);
}
