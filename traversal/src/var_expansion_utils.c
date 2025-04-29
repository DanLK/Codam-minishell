/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/29 12:21:37 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/29 12:22:24 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*****************************************************************************
 * Starts reading at position and gets the variable name
******************************************************************************/
char	*get_var_name(char *string, int pos)
{
	char	*name;
	int		i;

	if (pos >= (int)(ft_strlen(string) - 1))
		return (NULL);
	i = 0;
	while (!is_special_char(string[pos + i + 1])
		&& !ft_isspace(string[pos + i + 1]))
		i++;
	name = ft_substr(string, pos + 1, i);
	return (name);
}

/*****************************************************************************
 * Returns the position of char c on strings
******************************************************************************/
int	get_position(char *string, char c)
{
	int	i;
	int	len;

	if (!string)
		return (0);
	i = 0;
	len = ft_strlen(string);
	while (i < len && string[i])
	{
		if (string[i] == c)
			return (i);
		i++;
	}
	return (0);
}
