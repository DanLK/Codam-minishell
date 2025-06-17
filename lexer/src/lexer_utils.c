/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 15:41:02 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 12:36:01 by dloustal      ########   odam.nl         */
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

bool	is_builtin_type(enum e_Type type)
{
	return (type >= TKN_ECHO && type <= TKN_EXIT);
}

const t_map	*get_map(void)
{
	static const t_map	keywords = {
		.words = {"echo", "cd", "pwd", "export", "unset", "env", "exit"},
		.types = {TKN_ECHO, TKN_CD, TKN_PWD, TKN_EXPORT,
		TKN_UNSET, TKN_ENV, TKN_EXIT}
	};

	return (&keywords);
}

bool	is_variable_tkn(char *src, t_scanner *scanner)
{
	int	cur;

	if (!src || scanner->cur >= (int)ft_strlen(src))
		return (false);
	cur = scanner->cur;
	while (src[cur] && !is_special_char(src[cur]))
		cur++;
	if (!src[cur] || (src[cur] != '\'' && src[cur] != '\"'))
		return (true);
	else
		return (false);
}
