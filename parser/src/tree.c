/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/02 12:48:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/03 19:11:47 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->root = NULL;
	return (tree);
}

t_t_node	*new_tree_node(t_token *token)
{
	t_t_node	*node;

	if (!token)
		return (NULL);
	node = malloc(sizeof(t_t_node));
	if (!node)
		return (NULL);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	insert_left(t_t_node *root, t_token *token)
{
	t_t_node	*new;

	new = new_tree_node(token);
	if (!new)
		return ;
	root->left = new;
}

void	insert_right(t_t_node *root, t_token *token)
{
	t_t_node	*new;

	new = new_tree_node(token);
	if (!new)
		return ;
	root->right = new;
}
