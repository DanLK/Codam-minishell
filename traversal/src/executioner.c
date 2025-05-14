/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 13:36:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/14 15:26:23 by dloustal      ########   odam.nl         */
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
		return (125); //For now
	if ((*root)->p_type == PARSER_COMMAND)
		exit_st = execute_command(root, vars, info);
	else if ((*root)->p_type == PARSER_PIPE)
		exit_st = execute_pipe(root, vars, info);
	else if ((*root)->p_type == PARSER_REDIR)
		exit_st = execute_redirection(root, vars, info);
	else
	{
		ft_printf("Not able to execute right now\n");
		exit_st = 125; // For now, as an error code
	}
	info->last_return_code = exit_st;
	ft_printf("[execute_src] exit status: %d\n", info->last_return_code);
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

	if (!root || !vars || !info)
		return (125);
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (std_out == -1 || std_in == -1)
	{
		ft_printf("[execute_redirection] dup failed\n");
		return (-1);
	}
	cur = (*(*root)->redirs);
	while (cur)
	{
		call_redir(cur);
		cur = cur->next->next;
	}
	execute_command(root, vars, info);
	if (dup2(std_out, STDOUT_FILENO) == -1 || dup2(std_in, STDIN_FILENO) == -1) {
        ft_printf("[execute_redirection] dup2 in restoring out fd failed\n");
        return (-1);
    }
    close(std_out);
	close(std_in);
	// Free redirection node!!!!!
	return (0);
}

void	call_redir(t_redir_node *cur)
{
	t_redir_node	*operator_node;

	operator_node = cur;
	cur = cur->next;
	if (cur)
	{
		if (operator_node->type == TKN_REDIR_OUT)
			tmp_redir_out(cur->file);
		else if (operator_node->type == TKN_REDIR_OUT_APP)
			tmp_redir_append(cur->file);
		else if (operator_node->type == TKN_REDIR_IN)
			tmp_redir_in(cur->file);
	}
	else
		ft_printf("[execute_redirection] file node doesn't exist\n");
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND
*******************************************************************************/
int	execute_command(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	t_token_list	*tokens;
	int				exit_status;

	if (!root)
		return (125); //Not sure what to return here
	tokens = (*root)->tokens;
	if (is_builtin_type(tokens->head->token->type)
		|| (tokens->head->token->type == TKN_WORD
		&& tokens->head->next && tokens->head->next->token->type == TKN_EQUAL))
	{
		exit_status = execute_builtin(root, vars, info);
		info->last_return_code = exit_status;
		return (exit_status);
	}
	if (tokens->head->token->type == TKN_WORD)
	{
		exit_status = execute_ext_command(root, vars, info);
		info->last_return_code = exit_status;
		return (exit_status);
	}
	info->last_return_code = 125;
	return (125);
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND and the head of the
 * token list is one of the builtins
*******************************************************************************/
int	execute_builtin(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	t_token_list	*tokens;
	enum e_Type		type;

	if (!root)
		return (125);
	tokens = (*root)->tokens;
	type = tokens->head->token->type;
	if (type == TKN_ECHO)
		return (execute_echo(tokens));
	if (type == TKN_CD)
		return (execute_cd(tokens, vars));
	if (type == TKN_PWD)
		return (pwd_builtin());
	if (type == TKN_EXPORT)
		return (execute_export(tokens, vars));
	if (type == TKN_UNSET)
		return  (execute_unset(tokens, &vars));
	if (type == TKN_ENV)
		return (env_builtin(vars));
	if (type == TKN_EXIT)
	{
		exit_builtin(vars, info); // FIXED the exit built in to not take any argument
		return (7);
	}
	if (type == TKN_WORD)
		return (execute_assignment(tokens, vars));
	return (125); //For now
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
		return (125); //For now
	len = len_token_list(tokens);
	params = (char**)malloc((len) * sizeof(char *));
	if (!params)
		return (125);
	params[len - 1] = NULL;
	if (len > 1)
		node = tokens->head->next;
	i = 0;
	while (i < len - 1)
	{
		params[i]  = ft_strdup(node->token->lexeme);
		node = node->next;
		i++;
	}
	exit_st = echo_builtin(params); //Must return the value this returns
	clear_array(params);
	return (exit_st);
}

int	execute_cd(t_token_list *tokens, t_vars *vars)
{
	if (!tokens || !vars)
		return (125);
	if (!tokens->head->next)
		return cd_builtin(NULL, vars);
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
	int		exit_status;

	if (!tokens || !head)
		return (125); //For now
	node = tokens->head->next; //Should be the first argument fot the unset
	exit_status = 0;
	if (!node)
		return (0); //Success??
	while (node)
	{
		exit_status = unset_builtin(*head, node->token->lexeme); // Assign to exit_status 
		node = node->next;
	}
	return (exit_status); // If all went well i.e. if all the exit status were 0
}

int	execute_export(t_token_list *tokens, t_vars *vars)
{
	char			*var_name;
	char			*var_value;
	t_token_node	*node;
	//int			exit_status;

	if (!tokens || !vars)
		return (125); //For now
	if (!tokens->head->next)
		return (export_builtin(vars, NULL, NULL));
	node = tokens->head->next;
	var_name = node->token->lexeme;
	var_value = NULL;
	if (node->next && node->next->token->type == TKN_EQUAL) //The equal
	{
		if (node->next->next) //There is a node with the value
			var_value = node->next->next->token->lexeme;
		else
			var_value = "";
	}
	// Should check that the token list has been fully consumed?
	return (export_builtin(vars, var_name, var_value));
}

int	execute_assignment(t_token_list *tokens, t_vars *vars)
{
	char			*var_name;
	char			*var_value;
	t_token_node	*node;

	if (!tokens || !vars)
		return (125); // For now
	node = tokens->head;
	var_name = node->token->lexeme;
	if (node->next->token->type == TKN_EQUAL)
	{
		if (node->next->next)
			var_value = node->next->next->token->lexeme;
		else
			var_value = "";
	}
	else
		return (125); //For now -- on error
	add_var(&vars, var_name, var_value, 0); //Add the variable and mark it as not exported
	return (0); // for now -- on success
}

int	execute_ext_command(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	int				size;
	char			**command;
	t_token_list	*tokens;

	if (!root || !vars || !info)
		return (125); //For now
	tokens = (*root)->tokens;
	size = len_token_list(tokens);
	command = tkn_list_to_array(tokens);
	if (!command)
		return (125); //For now
	exec_external_com(vars, command, size, info);
	clear_array(command);
	return (0);
}
