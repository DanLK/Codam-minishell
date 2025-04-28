/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/18 12:28:34 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/28 12:38:34 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	clear_token_list(t_token_list *list)
{
	t_token_node	*node;
	t_token_node	*tmp;

	if (!list)
		return ;
	node = list->head;
	while (node)
	{
		tmp = node;
		free((tmp->token)->lexeme);
		free(tmp->token);
		node = node->next;
		free(tmp);
	}
	list->head = NULL;
	free(list);
}
