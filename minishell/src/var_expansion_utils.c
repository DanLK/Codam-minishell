/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:21:37 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/17 14:47:04 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * Calculates the length of the expected expanded string
 * 
 * It expands everywhere but in single quotes
 * Ignores single and double quotes in the counting
******************************************************************************/
int	qstr_exp_len(char *s, t_vars *vars, t_info *info)
{
	size_t	len;
	bool	in_double;
	bool	in_single;
	int		i;
	char	*var_name;
	t_vars	*var;

	len = 0;
	in_double = false;
	in_single = false;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\'') //Ignore the quotes -- advance the index
		{
			in_single = !in_single;
			if (in_double)
				len++;
			i++;
			continue ;
		}
		if (s[i] == '\"') //Ignore the quotes -- advance the index
		{
			in_double = !in_double;
			if (in_single)
				len++;
			i++;
			continue ;
		}
		if (!in_single && s[i] == '$')
		{
			i++;
			if (s[i] && s[i] == '?')
			{
				len += ft_strlen(ft_itoa(info->last_return_code));
				i++;
			}
			else if (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			{
				var_name = get_var_name(s, i - 1);
				var = find_vars(vars, var_name);
				if (var)
					len += ft_strlen(var->value);
				free(var_name);
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
					i++;
			}
			else
				len++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

/*****************************************************************************
 * Writes char by char the exit status string in the result string
******************************************************************************/
void	put_exitstatus(char **result, t_info *info, int *res_i)
{
	int		exit_status;
	int		k;
	char	*st_exitstatus;

	exit_status = info->last_return_code;
	k = 0;
	st_exitstatus = ft_itoa(exit_status);
	while (st_exitstatus[k])
	{
		(*result)[*res_i] = st_exitstatus[k];
		(*res_i)++;
		k++;
	}
}

/*****************************************************************************
 * Writes char by char the variable string in the result string
******************************************************************************/
void	put_var(char **result, char *var, int *res_i)
{
	int	k;

	k = 0;
	while (var[k])
	{
		(*result)[*res_i] = var[k];
		k++;
		(*res_i)++;
	}
}

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
	while (string[pos + i + 1] && (ft_isalnum(string[pos + i + 1])
			|| string[pos + i + 1] == '_'))
		i++;
	name = ft_substr(string, pos + 1, i);
	return (name);
}

/*****************************************************************************
* Returns the position of char c on string
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
	return (len);
}
