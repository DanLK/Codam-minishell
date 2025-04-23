/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 15:41:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/15 14:23:39 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*read_quoted(t_scanner *scanner, char *src, char quotes)
{
	char	*substr;
	bool	quot_closed;

	if (!src || scanner->cur >= (int)ft_strlen(src))
		return (NULL);
	quot_closed = false;
	while (src[scanner->cur])
	{
		if (src[scanner->cur] == quotes)
		{
			quot_closed = true;
			break ;
		}
		scanner->cur += 1;
	}
	if (quot_closed)
	{
		scanner->cur += 1;
		substr = ft_substr(src, scanner->start + 1, scanner->cur - scanner->start - 2);
	}
	else
	{
		perror("Unclosed quotations");
		substr = ft_substr(src, scanner->start + 1, scanner->cur - scanner->start - 1);
	}
	return (substr);
}

void	consume_space(t_scanner *scanner, char *src)
{
	if (!src || scanner->cur >= (int)ft_strlen(src))
		return ;
	while (ft_isspace(src[scanner->cur]))
	{
		scanner->cur += 1;
		scanner->start += 1;
	}
}

// Missing accounting for single or double quoted sequences
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
		return (get_current_char(&(scanner->cur), src), read_quoted(scanner, src, '"'));
	if (c == '\'')
		return (get_current_char(&(scanner->cur), src), read_quoted(scanner, src, '\''));	
	while (c)
	{
		if (is_special_char(c))
			break ;
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	return (ft_substr(src, scanner->start, scanner->cur - scanner->start));
}

bool	is_special_char(char c)
{
	return (c == ' ' || c == '|' || c == '&'
			|| c == '<' || c == '>');
}

char	*read_identifier(t_scanner *scanner, char *src)
{
	char	*substr;
	int		st;
	char	c;

	if (!src || scanner->cur > (int)ft_strlen(src))
		return (NULL);
	st = scanner->start;
	c = src[--(scanner->cur)];
	while (c && (ft_isalnum(c) || issymbol(c)))
	{
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	substr = ft_substr(src, st, (scanner->cur) - st);
	return (substr);
}

const t_map	*get_map(void)
{
	static const t_map	keywords = {
		.words = {"echo", "cd", "pwd", "export", "unset", "env", "exit"},
		.types = {TKN_ECHO, TKN_CD, TKN_PWD, TKN_EXPORT, TKN_UNSET, TKN_ENV, TKN_EXIT}
	};

	return (&keywords);
}
