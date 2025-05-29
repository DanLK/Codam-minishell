/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/27 16:29:06 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/05/27 16:31:01 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_token_list(t_token_list *list)
{
	t_token_node	*node;

	if (!list)
		return ;
	node = list->head;
	if (!node)
		ft_printf("Token list is empty.\n");
	while (node)
	{
		printf("%d: %s\n", (node->token)->type, (node->token)->lexeme);
		node = node->next;
	}
}

int	len_token_list(t_token_list *list)
{
	t_token_node	*head;
	int				len;

	if (!list)
		return (0);
	len = 0;
	head = list->head;
	if (!head)
		return (0);
	len++;
	head = head->next;
	while (head)
	{
		len++;
		head = head->next;
	}
	return (len);
}

char	**tkn_list_to_array(t_token_list *tokens)
{
	int				len;
	char			**command;
	t_token_node	*node;
	int				i;

	if (!tokens)
		return (NULL);
	len = len_token_list(tokens);
	command = malloc((len + 1) * sizeof(char *));
	if (!command)
		return (NULL);
	command[len] = NULL;
	node = tokens->head;
	i = 0;
	while (i < len)
	{
		command[i]  = ft_strdup(node->token->lexeme);
		node = node->next;
		i++;
	}
	return (command);
}
