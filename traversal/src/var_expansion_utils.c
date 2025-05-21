/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/29 12:21:37 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/21 16:04:40 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*****************************************************************************
 * Calculates the length of the expected expanded string
******************************************************************************/
int	qstr_exp_len(char *s, t_vars *vars, t_shell_info *info)
{
	size_t	len;
	bool	in_double;
	int		i;
	char	*var_name;
	t_vars	*var;

	len = 0;
	in_double = false;
	i = 0;
	// ft_printf("[qstr_exp_len] Entering function...\n");
	while (s[i])
	{
		if (s[i] == '\"')
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		if (in_double && s[i] == '$') //start of a variable expansion or exit status
		{
			i++;
			// ft_printf("[qstr_exp_len] Found a $...\n");
			// ft_printf("[qstr_exp_len] pos: [%d]\n", i);
			if (s[i] && s[i] == '?') //It is an exit status
			{
				len += ft_strlen(ft_itoa(info->last_return_code));
				i++;
			}
			else if (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			{
				var_name = get_var_name(s, i - 1);
				// ft_printf("[qstr_exp_len] var_name: [%s]\n", var_name);
				var = find_vars(vars, var_name);
				if (var)
					len += ft_strlen(var->value);
				// ft_printf("[qstr_exp_len] var val:[%s] var len: [%d]\n", var->value, ft_strlen(var->value));
				free(var_name);
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
					i++;
			}
			else //It was just a $
				len++;
		}
		else //Any other character
		{
			len++;
			i++;
		}
	}
	// ft_printf("[qstr_exp_len] Leaving function...\n");
	return (len);
}

/*****************************************************************************
 * Writes char by char the exit status string in the result string
******************************************************************************/
void	put_exitstatus(char **result, t_shell_info *info, int *res_i)
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
	// ft_printf("[put_var] Entering function...\n");
	while (var[k])
	{
		(*result)[*res_i] = var[k];
		k++;
		(*res_i)++;
	}
	// ft_printf("[put_var] Leaving function...\n");
}

/*****************************************************************************
 * Starts reading at position and gets the variable name
******************************************************************************/
char	*get_var_name(char *string, int pos)
{
	char	*name;
	int		i;

	// ft_printf("DEBUG: get_var_name -- entering functino: string: [%s], pos: [%d]\n", string, pos);
	// ft_printf("DEBUG: get_var_name -- strlen: [%d]\n", (int)ft_strlen(string));
	if (pos >= (int)(ft_strlen(string) - 1))
		return (NULL);
	// ft_printf("DEBUG: get_var_name -- managed to pass initial check\n");
	i = 0;
	while (string[pos + i + 1] && (ft_isalnum(string[pos + i + 1])
		|| string[pos + i + 1] == '_'))
		i++;
	// ft_printf("DEBUG: get_var_name -- i: [%d]\n", i);
	name = ft_substr(string, pos + 1, i);
	return (name);
}

// /*****************************************************************************
//  * Returns the position of char c on string
// ******************************************************************************/
// int	get_position(char *string, char c)
// {
// 	int	i;
// 	int	len;

// 	if (!string)
// 		return (0);
// 	i = 0;
// 	len = ft_strlen(string);
// 	while (i < len && string[i])
// 	{
// 		if (string[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (len);
// }
