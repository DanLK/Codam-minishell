/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_clears_parser.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 15:39:13 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/11 10:58:42 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clear_subtree(t_t_node *root)
{
	if (!root)
		return ;
	clear_token_list(root->tokens);
	clear_subtree(root->left);
	clear_subtree(root->right);
	free(root);
}

void	clear_tree(t_tree *tree)
{
	if (!tree)
		return ;
	clear_subtree(tree->root);
	free(tree);
}
