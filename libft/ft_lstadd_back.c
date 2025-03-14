/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:43:06 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 10:05:04 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*n1, *n2, *n3;
// 	t_list	*head, *new;

// 	n1 = ft_lstnew((char *)"N1");
// 	n2 = ft_lstnew((char *)"N2");
// 	n3 = ft_lstnew((char *)"N3");
// 	new = ft_lstnew((char *)"new node");

// 	head = n1;
// 	n1->next = n2;
// 	n2->next = n3;
// 	ft_lstadd_back(&head, new);
// 	t_list *temp = n1;
// 	while (temp)
// 	{
// 		printf("%s --> ", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	return (0);
// }