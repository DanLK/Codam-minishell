/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/24 11:46:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/24 14:33:52 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_keyword(char *lexeme)
{
	const t_map	*keywords;
	int			i;

	keywords = get_map();
	i = 0;
	while (i < 7)
	{
		if (kw_compare(keywords, lexeme, i))
			return (keywords->types[i]);
		i++;
	}
	return (-1);
}

bool	kw_compare(const t_map *keywords, char *lexeme, int i)
{
	int	lex_len;
	int	kw_len;

	kw_len = ft_strlen(keywords->words[i]);
	lex_len = ft_strlen(lexeme);
	if (kw_len != lex_len)
		return (false);
	if (ft_strncmp(keywords->words[i], lexeme, kw_len) == 0)
		return (true);
	return (false);
}
char	get_current_char(int *cur, char *src)
{
	char	c;

	if (!src || *cur >= (int)ft_strlen(src))
		return ('\0');
	c = src[*cur];
	*cur += 1;
	return (c);
}

bool	is_next(int *cur, char *src, char expected)
{
	char	c;
	int		i;

	if (!src || *cur >= (int)ft_strlen(src) - 1)
		return (false);
	i = *cur;
	c = src[i];
	if (src[i] == expected)
	{
		*cur += 1;
		return (true);
	}
	return (false);
}
