/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:18:00 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/17 16:27:49 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	handle_no_quote(t_scanner *sc, char *src, char *result, t_qt_st *st)
{
	if (src[sc->cur] == '\'')
		st->in_single = true;
	else if (src[sc->cur] == '\"')
		st->in_double = true;
	result[(*st->i)++] = src[sc->cur++];
}

static void	handle_in_quote(t_scanner *sc, char *src, char *result, t_qt_st *st)
{
	result[(*st->i)++] = src[sc->cur];
	if (st->in_single && src[sc->cur] == '\'')
	{
		st->in_single = false;
		sc->cur++;
	}
	else if (st->in_double && src[sc->cur] == '\"')
	{
		st->in_double = false;
		sc->cur++;
	}
	else
		sc->cur++;
}

static t_qt_st	*init_quoted_state(int *i, bool in_single, bool in_double)
{
	t_qt_st	*state;

	state = malloc(sizeof(t_qt_st));
	if (!state)
		return (NULL);
	state->i = i;
	state->in_single = in_single;
	state->in_double = in_double;
	return (state);
}

/******************************************************************************
 * Reads and copies a string taking the quotes into account
******************************************************************************/
char	*read_quoted(t_scanner *sc, char *src)
{
	t_qt_st	*st;
	char	*result;
	int		i;

	result = malloc((ft_strlen(src) + 1) * sizeof (char));
	if (!result)
		return (NULL);
	i = 0;
	sc->cur--;
	st = init_quoted_state(&i, false, false);
	while (src[sc->cur])
	{
		if (!st->in_single && !st->in_double)
		{
			if (is_token_breaker(src[sc->cur]))
				break ;
			handle_no_quote(sc, src, result, st);
		}
		else
			handle_in_quote(sc, src, result, st);
	}
	free(st);
	result[i] = '\0';
	return (result);
}
// char	*read_quoted_cpy(t_scanner *sc, char *src)
// {
// 	bool	in_single;
// 	bool	in_double;
// 	char	*result;
// 	int		i;

// 	result = malloc((ft_strlen(src) + 1) * sizeof (char));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	sc->cur--;
// 	in_single = false;
// 	in_double = false;
// 	while (src[sc->cur])
// 	{
// 		if (!in_single && !in_double)
// 		{
// 			if (src[sc->cur] == '\'')
// 			{
// 				in_single = true;
// 				result[i++] = src[sc->cur];
// 				sc->cur++;
// 				continue ;
// 			}
// 			else if (src[sc->cur] == '\"')
// 			{
// 				in_double = true;
// 				result[i++] = src[sc->cur];
// 				sc->cur++;
// 				continue ;
// 			}
// 			else if (src[sc->cur] == ' '
// 				|| src[sc->cur] == '|' || src[sc->cur] == '<'
// 				|| src[sc->cur] == '>')
// 				break ;
// 			else
// 			{
// 				result[i++] = src[sc->cur];
// 				sc->cur++;
// 			}
// 		}
// 		else if (in_single)
// 		{
// 			result[i++] = src[sc->cur];
// 			if (src[sc->cur] == '\'')
// 				in_single = false;
// 			sc->cur++;
// 		}
// 		else if (in_double)
// 		{
// 			result[i++] = src[sc->cur];
// 			if (src[sc->cur] == '\"')
// 				in_double = false;
// 			sc->cur++;
// 		}
// 	}
// 	result[i] = '\0';
// 	return (result);
// }
