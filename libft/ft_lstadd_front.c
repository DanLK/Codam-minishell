/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:19:27 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 09:59:06 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*n1, *n2, *n3, *new;
// 	t_list	*head;

// 	n1 = ft_lstnew((char *)"N1");
// 	n2 = ft_lstnew((char *)"N2");
// 	n3 = ft_lstnew((char *)"N3");
// 	new = ft_lstnew((char *)"New node");

// 	head = n1;
// 	n1->next = n2;
// 	n2->next = n3;

// 	t_list *temp = n1;
// 	while (temp)
// 	{
// 		printf("%s --> ", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	printf("\nAgain:");
// 	ft_lstadd_front(&head, new);
// 	temp = new;
// 	while (temp)
// 	{
// 		printf("%s --> ", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	printf("\n");
// 	return (0);
// }