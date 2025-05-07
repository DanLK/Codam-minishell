/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 13:36:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/07 10:18:20 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 *  Executes the src code represented by an AST built by the parser
*******************************************************************************/
int	execute_src(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	if (!root)
		return (125); //For now
	if ((*root)->p_type == PARSER_COMMAND)
		return (execute_command(root, vars, info));
	else if ((*root)->p_type == PARSER_PIPE)
	{
		return (execute_pipe(root, vars, info));
	}
	else if ((*root)->p_type == PARSER_REDIR)
	{
		return (execute_pipe(root, vars, info));
	}
	else
	{
		ft_printf("Not able to execute right now\n");
		return (125); // For now, as an error code
	}
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND
*******************************************************************************/
int	execute_command(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	t_token_list	*tokens;

	if (!root)
		return (125); //Not sure what to return here
	tokens = (*root)->tokens;
	if (is_builtin_type(tokens->head->token->type)
		|| (tokens->head->token->type == TKN_WORD
		&& tokens->head->next && tokens->head->next->token->type == TKN_EQUAL))
		return (execute_builtin(root, vars));
	if (tokens->head->token->type == TKN_WORD)
		return (execute_ext_command(root, vars, info));
	return (125); //For now
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND and the head of the
 * token list is one of the builtins
*******************************************************************************/
int	execute_builtin(t_t_node **root, t_vars *vars)
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
	{
		cd_builtin(tokens->head->next->token->lexeme, vars);
		return (2); // Temporarily
	}
	if (type == TKN_PWD)
	{
		//TO DO: Check that the list only contains pwd --->>> NOT NECESSARY
		pwd_builtin();
		return (3); // Temporarily
	}
	if (type == TKN_EXPORT)
	{
		execute_export(tokens, vars);
		return (4); //For now, further processing of the variable name and variable value are needed
	}
	if (type == TKN_UNSET)
	{
		execute_unset(tokens, &vars);
		return (5); // Temporarily
	}
	if (type == TKN_ENV)
	{
		env_builtin(vars);
		return (6);
	}
	if (type == TKN_EXIT)
	{
		exit_builtin(); // FIXED the exit built in to not take any argument
		return (7);
	}
	if (type == TKN_WORD)
	{
		execute_assignment(tokens, vars);
		return (8);
	}
	return (125); //For now
}

/*******************************************************************************
 *  Transforms the token list on the command node into an array containing 
 * the parameters to echo and calls the echo_builtin function
*******************************************************************************/
int	execute_echo(t_token_list *tokens)
{
	char			**params;
	int				len;
	int				i;
	t_token_node	*node;

	if (!tokens)
		return (125); //For now
	len = len_token_list(tokens);
	params = (char**)malloc((len) * sizeof(char *));
	if (!params)
		return (125);
	params[len - 1] = NULL;
	node = tokens->head->next;
	i = 0;
	while (i < len - 1)
	{
		params[i]  = ft_strdup(node->token->lexeme);
		node = node->next;
		i++;
	}
	echo_builtin(params); //Must return the value this returns
	clear_array(params);
	return (1);
}

int	execute_unset(t_token_list *tokens, t_vars **head)
{
	t_token_node	*node;
	// int		exit_status;

	if (!tokens || !head)
		return (125); //For now
	node = tokens->head->next; //Should be the first argument fot the unset
	if (!node)
		return (0); //Success??
	while (node)
	{
		unset_builtin(head, node->token->lexeme); // Assign to exit_status 
		node = node->next;
	}
	return (0); // If all went well i.e. if all the exit status were 0
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
	{
		export_builtin(vars, NULL, NULL);
		return (0); // For now
	}
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
	export_builtin(vars, var_name, var_value); // Return the exit status
	return (0); //For now
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
