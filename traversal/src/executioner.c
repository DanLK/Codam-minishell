/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 13:36:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/10 16:34:40 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 *  Executes the src code represented by an AST built by the parser
*******************************************************************************/
int	execute_src(t_t_node **root, t_vars *vars, t_shell_info *info)
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
		ft_printf("Not able to execute right now\n");
		exit_st = 127;
	}
	info->last_return_code = exit_st;
	return (exit_st);
}

/*******************************************************************************
 *  Experiment to execute a redirection node 
 * -- For now assumming only out redirections are possible
*******************************************************************************/
int	execute_redirection(t_t_node **root, t_vars *vars, t_shell_info *info)
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
	while (cur)
	{
		exit_code = call_redir(cur, info);
		if (exit_code == 1)
			break ;
		cur = cur->next->next;
	}
	info->last_return_code = exit_code;
	if (exit_code == 0)
		exit_code = execute_command(root, vars, info);
	if (dup2(std_out, STDOUT_FILENO) == -1 || dup2(std_in, STDIN_FILENO) == -1)
		return (-1);
	close(std_out);
	close(std_in);
	// info->cur_hd = 0;
	// Free redirection node!!!!!
	return (exit_code);
}

int	call_redir(t_redir_node *cur, t_shell_info *info)
{
	t_redir_node	*operator_node;

	(void)info;
	operator_node = cur;
	cur = cur->next;
	if (cur)
	{
		if (operator_node->type == TKN_REDIR_OUT)
			return (tmp_redir_out(cur->file));
		else if (operator_node->type == TKN_REDIR_OUT_APP)
			return (tmp_redir_append(cur->file));
		else if (operator_node->type == TKN_REDIR_IN)
			return (tmp_redir_in(cur->file));
		else if (operator_node->type == TKN_HEREDOC)
			return (exec_heredoc(cur->file));
	}
	else
		return (ft_printf("[execute_redirection] file node doesn't exist\n"), 1);
	return (0);
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND
*******************************************************************************/
int	execute_command(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	t_token_list	*tokens;
	int				exit_status;

	if (!root)
		return (1);
	tokens = (*root)->tokens;
	if (is_builtin_type(tokens->head->token->type)
		|| (tokens->head->token->type == TKN_WORD
			&& tokens->head->next
			&& tokens->head->next->token->type == TKN_EQUAL))
	{
		exit_status = execute_builtin(root, vars, info);
		info->last_return_code = exit_status;
		return (exit_status);
	}
	if (tokens->head->token->type == TKN_WORD
		|| tokens->head->token->type == TKN_Q_STRING)
	{
		exit_status = execute_ext_command(root, vars, info);
		info->last_return_code = exit_status;
		return (exit_status);
	}
	info->last_return_code = 1;
	return (1);
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND and the head of the
 * token list is one of the builtins
*******************************************************************************/
int	execute_builtin(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	t_token_list	*tokens;
	t_token			*token;

	if (!root)
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
		exit_builtin(vars, info);
	if (token->type == TKN_WORD)
		return (execute_assignment(tokens, vars));
	return (127);
}

/*******************************************************************************
 *  Transforms the token list on the command node into an array containing 
 * the parameters to echo and calls the echo_builtin function
 * 
 * 
 * Maybe the ignoring should happen inside the builtin!!!
*******************************************************************************/
int	execute_echo(t_token_list *tokens)
{
	char			**params;
	int				len;
	int				i;
	int				exit_st;
	t_token_node	*node;

	if (!tokens)
		return (1);
	len = len_token_list(tokens);
	params = (char **)malloc((len) * sizeof(char *));
	if (!params)
		return (1);
	params[len - 1] = NULL;
	if (len > 1)
		node = tokens->head->next;
	i = 0;
	while (len > 1 && node != NULL && (i < len - 1))
	{
		params[i] = ft_strdup(node->token->lexeme);
		node = node->next;
		i++;
	}
	exit_st = echo_builtin(params);
	clear_array(params);
	return (exit_st);
}

int	execute_cd(t_token_list *tokens, t_vars *vars)
{
	if (!tokens || !vars)
		return (1);
	if (!tokens->head->next)
		return (cd_builtin(NULL, vars));
	if (tokens->head->next->next)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (cd_builtin(tokens->head->next->token->lexeme, vars));
}

int	execute_unset(t_token_list *tokens, t_vars **head)
{
	t_token_node	*node;
	int				exit_status;

	if (!tokens || !head)
		return (1);
	node = tokens->head->next;
	exit_status = 0;
	if (!node)
		return (0);
	while (node)
	{
		exit_status = unset_builtin(head, node->token->lexeme);
		node = node->next;
	}
	return (exit_status);
}

static void	loop_export(t_token_node *node, t_vars *vars, int *exit_code)
{
	char			*var_name;
	char			*var_value;
	
	while (node)
	{
		var_name = node->token->lexeme;
		var_value = NULL;
		if (node->next && node->next->token->type == TKN_EQUAL)
		{
			if (node->next->next)
			{
				var_value = node->next->next->token->lexeme;
				node = node->next->next->next;
			}
			else
			{
				var_value = "";
				node = node->next->next;
			}
		}
		else
			node = node->next;
		*exit_code = export_builtin(&vars, var_name, var_value);
	}
}

int	execute_export(t_token_list *tokens, t_vars *vars)
{
	int				exit_code;
	t_token_node	*node;

	if (!tokens || !vars)
		return (1);
	if (!tokens->head->next)
	{
		export_builtin(&vars, NULL, NULL);
		return (0);
	}
	node = tokens->head->next;
	exit_code = 0;
	loop_export(node, vars, &exit_code);
	return (exit_code);
}

//divided this from execute assignment
static char	*get_var_value(t_token_node *node, char *var_value)
{
	if (node->next->token->type == TKN_EQUAL)
	{
		if (node->next->next)
			var_value = node->next->next->token->lexeme;
		else
			var_value = "";
		return (var_value);
	}
	else
		return (NULL);
}

int	execute_assignment(t_token_list *tokens, t_vars *vars)
{
	char			*var_name;
	char			*var_value;
	t_token_node	*node;
	t_vars			*temp;

	var_value = NULL;
	if (!tokens || !vars)
		return (1);
	node = tokens->head;
	var_name = node->token->lexeme;
	var_value = get_var_value(node, var_value);
	if (!var_value)
		return (1);
	temp = find_vars(vars, var_name);
	if (temp)
	{
		if (temp->value)
			free(temp->value);
		temp->value = ft_strdup(var_value);
	}
	else
		add_var(&vars, var_name, var_value, 0);
	return (0);
}

int	execute_ext_command(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	int				size;
	char			**command;
	t_token_list	*tokens;
	int				exit_code;

	if (!root || !vars || !info)
		return (1);
	exit_code = 0;
	tokens = (*root)->tokens;
	size = len_token_list(tokens);
	command = tkn_list_to_array(tokens);
	if (!command)
		return (1);
	exit_code = exec_external_com(vars, command, size, info);
	clear_array(command);
	return (exit_code);
}

// int	execute_abs_path(t_t_node **root, t_vars *vars, t_shell_info *info)
// {
// 	int				size;
// 	char			**command;
// 	t_token_list	*tokens;
// 	char			*path;

// 	if (!root || !vars || !info)
// 	return (125); //For now
// 	tokens = (*root)->tokens;
// 	size = len_token_list(tokens);
// 	//command = tkn_list_to_array(tokens);
// 	path = ft_strdup(command[0]);
// 	if (!command)
// 		return (125); //For now
// 	create_child_proc(vars, command, path, size, info);
// 	clear_array(command);
// 	return (0);
// }
