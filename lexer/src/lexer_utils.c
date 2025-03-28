/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 15:41:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/28 11:56:28 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*read_quoted(int *cur, int start, char *src, char quotes)
{
	char	*substr;
	bool	quot_closed;

	if (!src || *cur >= (int)ft_strlen(src))
		return (NULL);
	quot_closed = false;
	while (src[*cur])
	{
		if (src[*cur] == quotes)
		{
			quot_closed = true;
			break ;
		}
		*cur += 1;
	}
	if (quot_closed)
	{
		*cur += 1;
		substr = ft_substr(src, start + 1, (*cur) - start - 2);
	}
	else
	{
		perror("Unclosed quotations");
		substr = ft_substr(src, start + 1, (*cur) - start - 1);
	}
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
	if (c == '\"')
		return (get_current_char(cur, src), read_quoted(cur, st, src, '"'));
	if (c == '\'')
		return (get_current_char(cur, src), read_quoted(cur, st, src, '\''));	
	while (c)
	{
		if (is_special_char(c))
			break ;
		*cur += 1;
		c = src[*cur];
	}
	return (ft_substr(src, st, (*cur) - st));
}

bool	is_special_char(char c)
{
	return (c == ' ' || c == '|' || c == '&'
			|| c == '<' || c == '>');
}

char	*read_identifier(int *cur, int start, char *src)
{
	char	*substr;
	int		st;
	char	c;

	if (!src || *cur >= (int)ft_strlen(src))
		return (NULL);
	st = start;
	c = src[--(*cur)];
	while (c && (ft_isalnum(c) || issymbol(c)))
	{
		*cur += 1;
		c = src[*cur];
	}
	substr = ft_substr(src, st, (*cur) - st);
	return (substr);
}

const t_map	*get_map(void)
{
	static const t_map	keywords = {
		.words = {"echo", "cd", "pwd", "export", "unset", "env", "exit"},
		.types = {ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT}
	};

	return (&keywords);
}
