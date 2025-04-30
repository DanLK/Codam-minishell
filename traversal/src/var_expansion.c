/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/30 11:08:22 by dloustal      ########   odam.nl         */
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
	char			*old_lexeme;

	if (!tokens || !vars)
		return ;
	node = tokens->head;
	while (node)
	{
		if (node->token->type == TKN_ENV_VAR)
			expand_envvar(node, vars);
		if (node->token->type == TKN_DQ_STRING)
		{
			old_lexeme = node->token->lexeme;
			node->token->lexeme = expand_dqstring(node->token->lexeme, vars);
			free(old_lexeme);
		}
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
	char	*old_lexeme;

	if (!node || !vars)
		return ;
	var = find_vars(vars, node->token->lexeme);
	if (var)
	{
		old_lexeme = node->token->lexeme;
		free(old_lexeme);
		node->token->lexeme = ft_strdup(var->value); //Not sure whether I should change it for a copy of var instead
		node->token->type = TKN_WORD;
	}
	else
	{
		perror("Variable not found"); //This is a syntax error and should stop and clean everything
		return ; //Clear memory
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
	char	*tmp;
	int		len;

	if (!string || !vars)
		return (NULL);
	if (!ft_strnstr(string, "$", ft_strlen(string)))
		return (ft_strdup(string));
	i = get_position(string, '$');
	result = ft_strdup(string);
	if (!result)
		return (NULL);
	len = (int)ft_strlen(string);
	while (i < len)
	{
		tmp = result;
		result = expand_one_dqstring(tmp, vars);
		free(tmp);
		if (!result)
			return (NULL);
		i = get_position(result, '$');
		len = (int)ft_strlen(result);
	}
	return (result);
}

/*****************************************************************************
 * Expands a variable in a double quoted string
 * Returns a string with the var replaced
 * 
 * aux[0] = start
 * aux[1] = var_name
 * aux[2] = start + var value
 * aux[3] = rest
 * 
******************************************************************************/
char	*expand_one_dqstring(char *string, t_vars *vars)
{
	int		i;
	char	*result;
	char	**aux;
	t_vars	*var;
	
	i = get_position(string, '$');
	aux = malloc(5 * sizeof(char *));
	if (!aux)
		return (NULL);
	aux[0] = ft_substr(string, 0, i);
	aux[1] = get_var_name(string, i);
	var = find_vars(vars, aux[1]);
	if (!var || !var->value)
	{
		perror("Variable not found"); //Clean up?
		aux[2] = ft_strjoin(aux[0], ""); //At the moment replacing with the empty string
	}
	else
		aux[2] = ft_strjoin(aux[0], var->value);
	aux[3] = ft_substr(string, i + 1 + ft_strlen(aux[1]),
				ft_strlen(string)- i - 1 - ft_strlen(aux[1]));
	aux[4] = NULL;
	result = ft_strjoin(aux[2], aux[3]);
	clear_array(aux);
	return (result);
}
