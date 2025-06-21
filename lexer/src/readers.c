/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 13:39:12 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/21 17:29:05 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*read_options(t_scanner *scanner, char *src)
{
	char	*option;
	int		start;
	char	c;

	if (!scanner || !src)
		return (NULL);
	start = scanner->start;
	c = src[(scanner->cur)];
	while (c && ft_isalpha(c))
	{
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	option = ft_substr(src, start, (scanner->cur) - start);
	return (option);
}

char	*read_filepath(t_scanner *scanner, char *src)
{
	char	c;

	if (!src || scanner->cur >= (int)ft_strlen(src))
		return (NULL);
	while (ft_isspace(src[scanner->cur]))
	{
		scanner->cur += 1;
		scanner->start += 1;
	}
	c = src[scanner->cur];
	if (c == '\"')
		return (get_cur_char(&(scanner->cur), src), read_quoted(scanner, src));
	if (c == '\'')
		return (get_cur_char(&(scanner->cur), src), read_quoted(scanner, src));
	while (c)
	{
		if (is_special_char(c))
			break ;
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	return (ft_substr(src, scanner->start, scanner->cur - scanner->start));
}

char	*get_variable(t_scanner *s, char *src)
{
	char	c;
	char	*var_name;

	s->cur--;
	c = src[s->cur];
	if (c == '$')
		c = src[++s->cur];
	while (ft_isalnum(c) || c == '_')
		c = src[++s->cur];
	var_name = ft_substr(src, s->start, s->cur - s->start);
	return (var_name);
}
