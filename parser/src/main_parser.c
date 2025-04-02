/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:48:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/02 16:04:04 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	t_t_node *root = new_tree_node(create_token(0, "("));
	t_t_node *node1 = new_tree_node(create_token(1, "left"));
	t_t_node *node2 = new_tree_node(create_token(2, "right"));
    root->left = node1;
    root->right = node2;
	t_t_node *node3 = new_tree_node(create_token(3, "left"));
	t_t_node *node4 = new_tree_node(create_token(4, "right"));
	node1->left = node3;
	node1->right = node4;
	t_t_node *node5 = new_tree_node(create_token(5, "left"));
	t_t_node *node6 = new_tree_node(create_token(6, "right"));
	node2->left = node5;
	node2->right = node6;
	pretty_print_tree(root, 0);
	return (0);
}