/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 15:41:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/21 11:43:29 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*read_quoted(int *cur, int start, char *src, char quotes)
{
	char	*substr;

	if (!src || *cur >= (int)ft_strlen(src))
		return (NULL);
	while (src[*cur])
	{
		if (src[*cur] == quotes)
			break ;
		*cur += 1;
	}
	*cur += 1;
	substr = ft_substr(src, start + 1, (*cur) - start - 2);
	return (substr);
}

void	consume_space(int *cur, int *start, char *src)
{
	if (!src || *cur >= (int)ft_strlen(src))
		return ;
	while (ft_isspace(src[*cur]))
	{
		*cur += 1;
		*start += 1;
	}
}

// Missing accounting for single or double quoted sequences
char	*read_filepath(int *cur, int start, char *src)
{
	char	*substr;
	int		st;
	char	c;

	if (!src || *cur >= (int)ft_strlen(src))
		return (NULL);
	st = start;
	while (ft_isspace(src[*cur]))
	{
		*cur += 1;
		st += 1;
	}
	c = src[*cur];
	while (c)
	{
		c = src[*cur];
		if (c == ' ' || c == '|' || c == '&'
			|| c == '<' || c == '>')
			break ;
		*cur += 1;
	}
	substr = ft_substr(src, st, (*cur) - st);
	return (substr);
}

char	*read_identifier(int *cur, int start, char *src)
{
	char	*substr;
	int		st;
	char	c;

	if (!src || *cur >= (int)ft_strlen(src))
		return (NULL);
	st = start;
	c = src[*cur];
	while (c && (ft_isalnum(c) || c == '_'))
	{
		*cur += 1;
		c = src[*cur];
	}
	substr = ft_substr(src, st, (*cur) - st);
	return (substr);
}