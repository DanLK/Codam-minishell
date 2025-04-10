/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:48:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/10 16:40:35 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	t_token_list	*list;
	t_tree			*ast;

	list = scan("unset EXACT >> echo Hello World | another pipe");
	// print_token_list(list);
	ast = parse(list);
	ft_printf("Is ast->root == NULL?: %d\n", ast->root == NULL);
	// print_token_list(ast->root->tokens);
	// print_token_list(ast->root->left->tokens);
	// print_token_list(ast->root->right->tokens);
	print_parse_tree(ast);
	// print_token_list(list);
	// ft_printf("\n");
	// ast = parse(list);
	// pretty_print_tree(ast->root, 0);
	// clear_token_list(list);
	// clear_tree(ast);
	return (0);
}