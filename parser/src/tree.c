/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/02 12:48:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 17:19:34 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_t_node	*new_tree_node(enum e_Ptype p_type,  t_token_list *tokens)
{
	t_t_node	*node;
	
	if (!tokens)
	return (NULL);
	node = malloc(sizeof(t_t_node));
	if (!node)
	return (NULL);
	node->tokens = tokens;
	node->p_type = p_type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	insert_left(t_t_node *root, enum e_Ptype p_type, t_token_list *tokens)
{
	t_t_node	*new;
	
	new = new_tree_node(p_type, tokens);
	if (!new)
	return ;
	root->left = new;
}

void	insert_right(t_t_node *root, enum e_Ptype p_type, t_token_list *tokens)
{
	t_t_node	*new;
	
	new = new_tree_node(p_type, tokens);
	if (!new)
	return ;
	root->right = new;
}

// t_tree	*init_tree(void)
// {
// 	t_tree	*tree;

// 	tree = malloc(sizeof(t_tree));
// 	if (!tree)
// 		return (NULL);
// 	tree->root = NULL;
// 	return (tree);
// }