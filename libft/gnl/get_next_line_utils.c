/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 21:53:10 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/01/03 11:21:49 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (char *)content;
	new->next = 0;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new_node;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

/* Traverses the list until it finds the character '\n'
If not found, in mode 'f' for find, it returns 0; and in mode 'c', for 
count, it returns the total number of characters read */
int	find_new_line(t_list *node, char mode)
{
	int	i;
	int	count;

	count = 0;
	if (!node)
		return (0);
	while (node)
	{
		i = 0;
		while (node->content[i])
		{
			if (node->content[i] == '\n')
				return (++count);
			i++;
			count++;
		}
		node = node->next;
	}
	if (mode == 'f')
		return (0);
	else if (mode == 'c')
		return (count);
	else
		return (-1);
}

/* Clears the list. If there is a new node with relevant
information, it makes the list point to the new node. Otherwise it 
frees the node and the relevant buffer. */
void	clear_list(t_list **list, t_list *node, char *buffer)
{
	t_list	*to_clear;
	t_list	*temp;

	if (list == NULL)
		return ;
	to_clear = *list;
	while (to_clear)
	{
		temp = to_clear->next;
		free(to_clear->content);
		free(to_clear);
		to_clear = temp;
	}
	if (node != NULL && node->content != NULL && node->content[0])
	{
		*list = node;
	}
	else
	{
		free(node);
		free(buffer);
		*list = NULL;
	}
}
// void	pretty_print(t_list *stash)
// {
// 	printf("Current stash:\n\n");
// 	while (stash)
// 	{
// 		printf("%s\n", stash->content);
// 		printf("--\n");
// 		stash = stash->next;
// 	}
// 	printf("\nEnd of stash\n");
// }
