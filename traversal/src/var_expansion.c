/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/28 17:25:07 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*****************************************************************************
 * Exchanges the environment variable for its value in a given node
 * Assumes the token type of the node is TKN_ENV_VAR
******************************************************************************/
void	expand_var(t_token_node *node, t_vars *vars)
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
 * Expands the necessary variables in a token list
******************************************************************************/
void	expand_var_list(t_token_list *tokens, t_vars *vars)
{
	t_token_node *node;

	if (!tokens || !vars)
		return ;
	node = tokens->head;
	while (node)
	{
		if (node->token->type == TKN_ENV_VAR)
			expand_var(node, vars);
		node = node->next;
	}
}

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
 * Expands a variable in a double quoted string
 * Returns a string with the var replaced
******************************************************************************/
char	*expand_dq_string(char *string, t_vars *vars)
{
	int		i;
	char	*result;
	char	*start;
	char	*var_name;
	t_vars	*var;

	if (!string || !vars)
		return (NULL);
	if (!ft_strnstr(string, "$", ft_strlen(string)))//$ exists nowhere in the string
		return (string);
	i = get_position(string, '$');
	while (i)
	{
		start = ft_substr(string, 0, i);
		// ft_printf("start: %s\n", start);
		var_name = get_var_name(string, i);
		var = find_vars(vars, var_name);
		if (!var)
		{
			perror("Variable not found"); //Clean up?
			result = ft_strjoin(start, ""); //At the moment replacing with the empty string
		}
		// ft_printf("var_name: [%s]\n", var_name);
		// ft_printf("var->value: %s\n", var->value);
		result = ft_strjoin(start, var->value);
		result = ft_strjoin(result, ft_substr(string, i + 1 + ft_strlen(var_name), ft_strlen(string) - i - 1 - ft_strlen(var_name)));
		ft_printf("%s\n", result);
		i = get_position(start, '$');
	}
	free(start);
	return (result);
}

char	*get_var_name(char *string, int pos)
{
	char	*name;
	int		i;

	if (pos >= (int)(ft_strlen(string) - 1))
		return (NULL);
	i = 0;
	while (!is_special_char(string[pos + i + 1]))
		i++;
	name = ft_substr(string, pos + 1, i);
	return (name);
}

int	get_position(char *string, char c)
{
	int i;
	int	len;

	if (!string)
		return (0);
	i = 0;
	len = ft_strlen(string);
	while (i < len && string[i])
	{
		if (string[i] == c)
			return (i);
		i++;
	}
	return (0);
}