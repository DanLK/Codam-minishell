/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_exp_len.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/18 16:44:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/21 17:18:25 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(size_t *len, t_exp *vexp)
{
	if (vexp->s[vexp->i] == '\'')
	{
		if (vexp->in_double)
			(*len)++;
		else	
			vexp->in_single = !vexp->in_single;
		vexp->i++;
	}
	else if (vexp->s[vexp->i] == '\"')
	{
		if (vexp->in_single)
			(*len)++;
		else
			vexp->in_double = !vexp->in_double;
		vexp->i++;
	}
}

static void	advance_var_size(size_t *len, t_exp *vexp, t_vars *vars)
{
	char	*var_name;
	t_vars	*var;

	var_name = get_var_name(vexp->s, vexp->i - 1);
	var = find_vars(vars, var_name);
	if (var)
		*len += ft_strlen(var->value);
	free(var_name);
}

static void	handle_vars(size_t *len, t_exp *vexp, t_vars *vars, t_info *info)
{
	char	*get_len;

	if (!vexp->in_single && vexp->s[vexp->i] == '$')
	{
		vexp->i++;
		if (vexp->s[vexp->i] && vexp->s[vexp->i] == '?')
		{
			get_len = ft_itoa(info->exit_code);
			*len += ft_strlen(get_len);
			vexp->i++;
			free(get_len);
		}
		else if (vexp->s[vexp->i] && (ft_isalpha(vexp->s[vexp->i])
				|| vexp->s[vexp->i] == '_'))
		{
			advance_var_size(len, vexp, vars);
			while (vexp->s[vexp->i] && (ft_isalnum(vexp->s[vexp->i])
					|| vexp->s[vexp->i] == '_'))
				vexp->i++;
		}
		else
			(*len)++;
	}
}

/*****************************************************************************
 * Calculates the length of the expected expanded string
 * 
 * It expands everywhere but in single quotes
 * Ignores single and double quotes in the counting
******************************************************************************/
int	qstr_exp_len(char *s, t_vars *vars, t_info *info)
{
	size_t	len;
	t_exp	*vexp;

	len = 0;
	vexp = init_var_exp(s);
	if (!vexp)
		return (0);
	if (!s)
		return (0);
	while (s[vexp->i])
	{
		if (s[vexp->i] == '\'' || s[vexp->i] == '\"')
			handle_quotes(&len, vexp);
		else if (!vexp->in_single && s[vexp->i] == '$')
			handle_vars(&len, vexp, vars, info);
		else
		{
			len++;
			vexp->i++;
		}
	}
	free(vexp->s);
	free(vexp);
	return (len);
}
