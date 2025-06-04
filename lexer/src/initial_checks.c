/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:45:20 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/04 16:26:02 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	closed_quotes(char *src)
{
	bool	in_single;
	bool	in_double;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(src);
	in_double = false;
	in_single = false;
	while (i < len)
	{
		if (!in_single && !in_double)
		{
			if (src[i] == '\'')
			{
				in_single = true;
				i++;
				continue ;
			}
			else if (src[i] == '\"')
			{
				in_double = true;
				i++;
				continue ;
			}
			else
				i++;
		}
		else
		{
			if (in_single && src[i] == '\'')
				in_single = false;
			if (in_double && src[i] == '\"')
				in_double = false;
			i++;
		}
	}
	return (!in_single && !in_double);
}

t_scanner	*init_scanner(int cur, int start)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(t_scanner));
	if (!scanner)
		return (NULL);
	scanner->cur = cur;
	scanner->start = start;
	return (scanner);
}
