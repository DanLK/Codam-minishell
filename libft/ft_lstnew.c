/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/07 16:34:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/01/06 14:48:06 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (void *)content;
	new->next = NULL;
	return (new);
}
// #include <stdio.h>

// int	main(void)
// {
// 	t_list	n1, n2, n3;
// 	t_list 	*head;
// 	t_list	*new;

// 	n1.content = "Node 1";
// 	n2.content = "Node 2";
// 	n3.content = "Node 3";

// 	head = &n1;
// 	n1.next = &n2;
// 	n2.next = &n3;
// 	n3.next = 0;

// 	t_list *temp = head;
// 	while (temp)
// 	{
// 		printf("%s --> ", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	printf("\n");
// 	new = ft_lstnew((char *)"Hello");
// 	printf("%s\n", (char *)new->content);
// 	return (0);
// }