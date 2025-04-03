/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:48:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/03 19:19:17 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	// t_t_node *node0 = new_tree_node(create_token(0, "("));
	// t_t_node *node1 = new_tree_node(create_token(1, "left"));
	// t_t_node *node2 = new_tree_node(create_token(2, "right"));
    // node0->left = node1;
    // node0->right = node2;
	// t_t_node *node3 = new_tree_node(create_token(3, "left"));
	// t_t_node *node4 = new_tree_node(create_token(4, "right"));
	// node1->left = node3;
	// node1->right = node4;
	// t_t_node *node5 = new_tree_node(create_token(5, "left"));
	// t_t_node *node6 = new_tree_node(create_token(6, "right"));
	// node2->left = node5;
	// node2->right = node6;
	// t_tree *tree = init_tree();
	// tree->root = node0;
	// pretty_print_tree(tree->root, 0);
	// clear_tree(tree);
	t_token_list	*list;
	t_tree			*ast;

	list = scan("echo -n Hello");
	// print_token_list(list);
	ft_printf("\n");
	ast = parse(list);
	pretty_print_tree(ast->root, 0);
	clear_token_list(list);
	clear_tree(ast);
	return (0);
}