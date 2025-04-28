/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/28 12:38:24 by dloustal      ########   odam.nl         */
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