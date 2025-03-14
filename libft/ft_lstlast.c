/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:33:30 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/11 14:41:17 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*n1, *n2, *n3;
// 	t_list	*head;

// 	n1 = ft_lstnew((char *)"N1");
// 	n2 = ft_lstnew((char *)"N2");
// 	n3 = ft_lstnew((char *)"N3");

// 	head = n1;
// 	n1->next = n2;
// 	n2->next = n3;
// 	printf("Last: %s\n", (char *)ft_lstlast(head)->content);
// 	return (0);
// }