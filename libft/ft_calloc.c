/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:52:15 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/11 12:20:52 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	tot_size;

	tot_size = nmemb * size;
	if (tot_size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (0);
	p = malloc(tot_size);
	if (!p)
		return (p);
	ft_bzero(p, tot_size);
	return (p);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	n = 0;
// 	int i = 0;
// 	int	*array;
// 	long *number;

// 	array = (int *)ft_calloc(n, sizeof(int));
// 	if (array == NULL)
//       printf("Memory allocation failed!\n");
// 	else
// 	{
// 		printf("Array elements after calloc: ");
// 		while (i < n)
// 		{
// 		printf("%d ", array[i]);
// 		i++;
// 		}
// 		printf("\n");
// 		free(array);
// 	}
// 	number = (long *)ft_calloc(10, sizeof(long));
// 	if( number != NULL )
// 		printf( "Allocated 10 long integers.\n" );    
// 	else 
// 		printf( "\nCan't allocate memory.\n" );
//    	free( number );
//    	return (0);
// }