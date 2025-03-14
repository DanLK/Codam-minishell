/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:25:02 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/11 14:41:35 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		count;

	if (!lst)
		return (0);
	count = 0;
	temp = lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
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
// 	printf("List size: %d\n", ft_lstsize(head));
// 	return (0);
// }