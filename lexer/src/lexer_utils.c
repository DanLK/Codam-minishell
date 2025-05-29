/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 15:41:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 16:57:27 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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


bool	is_special_char(char c)
{
	return (c == ' ' || c == '|' || c == '&'
			|| c == '<' || c == '>' || c == '\"' || c == '\'');
}

bool	is_builtin_type(enum e_Type type)
{
	return (type >= TKN_ECHO && type <= TKN_EXIT);
}

const t_map	*get_map(void)
{
	static const t_map	keywords = {
		.words = {"echo", "cd", "pwd", "export", "unset", "env", "exit"},
		.types = {TKN_ECHO, TKN_CD, TKN_PWD, TKN_EXPORT, TKN_UNSET, TKN_ENV, TKN_EXIT}
	};

	return (&keywords);
}
