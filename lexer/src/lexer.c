/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/20 17:16:42 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token_list	*scan(char *src)
{
	t_token_list	*tokens;

	if (!src)
		return (NULL);
	tokens = init_token_list();
	if (!tokens)
		return (NULL);
	tokens = populate_tokens(tokens, src);
	return (tokens);
}

t_token_list	*populate_tokens(t_token_list *tokens, char *src)
{
	int	current;
	int	start;

	if (!tokens || !src)
		return (NULL);
	current = 0;
	while (src[current])
	{
		start = current;
		get_cur_token(tokens, src, start, &current);
	}
	append_token(tokens, EOF, "EOF");
	return (tokens);
}

void	get_cur_token(t_token_list *tokens, char *src, int s, int *cur)
{
	char	c;
	char	*lexeme;

	if (!tokens || !src)
		return ;
	c = get_current_char(cur, src);
	lexeme = "";
	if (c == '|')
		append_token(tokens, PIPE, "|");
	if (c == '(')
		append_token(tokens, LEFT_PAREN, "(");
	if (c == ')')
		append_token(tokens, RIGHT_PAREN, ")");
	if (c == '=')
		append_token(tokens, EQUAL, "=");
	if (c == '>')
	{
		if (is_next(cur, src, '>'))
		{	
			append_token(tokens, RED_OUT_APP, ">>");
			s += 2;
		}
		else
		{
			append_token(tokens, RED_OUTPUT, ">");
			s++;
		}
		lexeme = read_filepath(cur, s, src);
		append_token(tokens, FILE_PATH, lexeme);
		free(lexeme);
	}
	if (c == '<')
	{
		if (is_next(cur, src, '<'))
			append_token(tokens, HEREDOC, "<<");
		else
			append_token(tokens, RED_INPUT, "<");
	}
	if (c == '$')
	{
		if (is_next(cur, src, '?'))
			append_token(tokens, EXIT_STATUS, "$?");
		else
			append_token(tokens, ENV_VAR, "$");
	}
	if (c == '"')
	{
		lexeme = read_quoted(cur, s, src, '"');
		append_token(tokens, DQ_STRING, lexeme);
		free(lexeme);
	}
	if (c == '\'')
	{
		lexeme = read_quoted(cur, s, src, '\'');
		append_token(tokens, SQ_STRING, lexeme);
		free(lexeme);
	}
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
