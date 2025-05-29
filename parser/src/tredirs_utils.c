/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tredirs_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/11 18:33:48 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/05/27 17:19:06 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir_node	*new_r_node(enum e_Type type, char *file)
{
	t_redir_node	*node;
	char			*file_dup;

	if (!file)
		return (NULL);
	file_dup = ft_strdup(file);
	if (!file_dup)
		return (NULL);
	node = malloc(sizeof(t_redir_node));
	if (!node)
		return (free(file_dup), NULL);
	node->type = type;
	node->file = file_dup;
	node->next = NULL;
	return (node);
}

t_redir_node	*get_last_redir(t_redir_node **head)
{
	t_redir_node	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	append_redir(t_redir_node **head, enum e_Type type, char *file)
{
	t_redir_node	*last;
	t_redir_node	*new;

	if (!head || !file)
		return ;
	new = new_r_node(type, file);
	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = get_last_redir(head);
		last->next = new;
	}
}

void	clear_redirs(t_redir_node **head)
{
	t_redir_node	*node;
	t_redir_node	*tmp;

	if (!head)
		return ;
	node = *head;
	while (node)
	{
		tmp = node;
		free(tmp->file);
		node = node->next;
		free(tmp);
	}
	free(head);
}
