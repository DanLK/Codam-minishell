/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes_reader.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 13:39:12 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/21 16:14:15 by dloustal      ########   odam.nl         */
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
			else if (src[sc->cur] == ' ' || src[sc->cur] == '=')
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
