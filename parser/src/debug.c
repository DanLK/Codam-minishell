/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 19:11:27 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/03 19:18:41 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	pretty_print_tree(t_t_node *root, int depth)
{
	int	i;

	if (!root)
	{
		return ;
	}
	i = 0;
	pretty_print_tree(root->right, depth + 1);
	while (i < depth)
	{
		ft_printf("        ");
		i++;
	}
	ft_printf("%d\n\n", (root->token)->type);
	pretty_print_tree(root->left, depth + 1);
}
void	print_token(t_token *token)
{
	if (!token)
	{
		ft_printf("Token is NULL. Nothing to print\n");
		return ;
	}
	ft_printf("[%d]: %s\n", token->type, token->lexeme);
}
