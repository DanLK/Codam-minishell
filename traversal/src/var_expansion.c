/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/29 12:22:12 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*****************************************************************************
 * Traverses the tree and expands the variables
******************************************************************************/
void	expand_var_tree(t_t_node **root, t_vars *vars)
{
	if (!root || !*root | !vars)
		return ;
	expand_var_list((*root)->tokens, vars);
	if ((*root)->left)
		expand_var_tree(&(*root)->left, vars);
	if ((*root)->right)
		expand_var_tree(&(*root)->right, vars);
}

/*****************************************************************************
 * Expands the necessary variables in a token list 
 * 
 * Expands the nodes of type ENV_VAR and the nodes of type DQ_STRING
 * 
******************************************************************************/
void	expand_var_list(t_token_list *tokens, t_vars *vars)
{
	t_token_node	*node;

	if (!tokens || !vars)
		return ;
	node = tokens->head;
	while (node)
	{
		if (node->token->type == TKN_ENV_VAR)
			expand_envvar(node, vars);
		if (node->token->type == TKN_DQ_STRING)
			node->token->lexeme = expand_dqstring(node->token->lexeme, vars);
		node = node->next;
	}
}

/*****************************************************************************
 * Exchanges the environment variable for its value in a given node
 * Assumes the token type of the node is TKN_ENV_VAR
******************************************************************************/
void	expand_envvar(t_token_node *node, t_vars *vars)
{
	t_vars	*var;

	if (!node || !vars)
		return ;
	var = find_vars(vars, node->token->lexeme);
	if (var)
	{
		node->token->lexeme = ft_strdup(var->value); //Not sure whether I should change it for a copy of var instead
		node->token->type = TKN_WORD;
	}
	else
	{
		perror("Variable not found"); //This is a syntax error and should stop and clean everything
		return ;
	}
}

/*****************************************************************************
 * Expands all variables in a double quoted string
 * Returns a new string with all the vars replaced
******************************************************************************/
char	*expand_dqstring(char *string, t_vars *vars)
{
	int		i;
	char	*result;

	if (!string || !vars)
		return (NULL);
	i = get_position(string, '$');
	result = string;
	while (i > 0)
	{
		result = expand_one_dqstring(result, vars);
		i = get_position(result, '$');
	}
	// ft_printf("result: \n%s\n", result);
	return (result);
}

/*****************************************************************************
 * Expands a variable in a double quoted string
 * Returns a string with the var replaced
******************************************************************************/
char	*expand_one_dqstring(char *string, t_vars *vars)
{
	int		i;
	char	*result;
	char	*start;
	char	*var_name;
	t_vars	*var;

	if (!string || !vars)
		return (NULL);
	i = get_position(string, '$');
	start = ft_substr(string, 0, i);
	var_name = get_var_name(string, i);
	var = find_vars(vars, var_name);
	if (!var)
	{
		perror("Variable not found"); //Clean up?
		result = ft_strjoin(start, ""); //At the moment replacing with the empty string
	}
	result = ft_strjoin(start, var->value);
	result = ft_strjoin(result, ft_substr(string, i + 1 + ft_strlen(var_name),
				ft_strlen(string)- i - 1 - ft_strlen(var_name)));
	free(start);
	return (result);
}
