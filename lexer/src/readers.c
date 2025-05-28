/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 13:39:12 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/28 13:06:13 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*read_quoted(t_scanner *sc, char *src)
{
	bool 	in_single;
	bool 	in_double;
	char	*result;
	int		i;

	result = malloc((ft_strlen(src) + 1) * sizeof (char));
	if (!result)
		return (NULL);
	i = 0;
	sc->cur--;
	in_single = false;
	in_double = false;
	while (src[sc->cur])
	{
		if (!in_single && !in_double)
		{
			if (src[sc->cur] == '\'')
			{
				in_single = true;
				sc->cur++;
				continue ;
			}
			else if (src[sc->cur] == '\"')
			{
				in_double = true;
				result[i++] = src[sc->cur];
				sc->cur++;
				continue ;
			}
			else if (src[sc->cur] == ' ' || src[sc->cur] == '='
					|| src[sc->cur] == '|' || src[sc->cur] == '<'
					|| src[sc->cur] == '>')
				break ;
			else
			{
				result[i++] = src[sc->cur];
				sc->cur++;
			}
		}
		else if (in_single)
		{
			if (src[sc->cur] == '\'')
			{
                in_single = false;
                sc->cur++;
            }
			else
			{
                result[i++] = src[sc->cur];
                sc->cur++;
            }
		}
		else if (in_double)
		{
			result[i++] = src[sc->cur];
			if (src[sc->cur] == '\"')
				in_double = false;
			sc->cur++;
		}
	}
	result[i] = '\0';
	return (result);
}

char	*read_options(t_scanner *scanner, char *src)
{
	char	*option;
	int		start;
	char	c;

	if (!scanner || !src) //|| scanner->cur >= (int)ft_strlen(src)
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
	{
		// ft_printf("[read_filepath] we are at the endof the string\n");
		return (NULL);
	}
	while (ft_isspace(src[scanner->cur]))
	{
		scanner->cur += 1;
		scanner->start += 1;
	}
	c = src[scanner->cur];
	if (c == '\"')
		return (get_current_char(&(scanner->cur), src), read_quoted(scanner, src));
	if (c == '\'')
		return (get_current_char(&(scanner->cur), src), read_quoted(scanner, src));	
	while (c)
	{
		if (is_special_char(c))
			break ;
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	return (ft_substr(src, scanner->start, scanner->cur - scanner->start));
}

char	*read_identifier(t_scanner *scanner, char *src)
{
	char	*substr;
	int		st;
	char	c;
	// bool	in_quotes;

	if (!src || scanner->cur > (int)ft_strlen(src))
		return (NULL);
	st = scanner->start;
	c = src[--(scanner->cur)];
	// in_quotes = false;
	while (c && (ft_isalnum(c) || issymbol(c) || c == ':'))
	{
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	substr = ft_substr(src, st, (scanner->cur) - st);
	return (substr);
}
