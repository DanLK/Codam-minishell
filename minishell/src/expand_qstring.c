/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_qstring.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/18 15:14:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/18 17:30:53 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*init_var_exp(char *s)
{
	t_exp	*v_exp;

	v_exp = malloc(sizeof(t_exp));
	if (!v_exp)
		return (NULL);
	v_exp->i = 0;
	v_exp->res_i = 0;
	v_exp->in_single = false;
	v_exp->in_double = false;
	v_exp->s = ft_strdup(s);
	return (v_exp);
}

static void	handle_quotes(char *result, t_exp *vexp, char *s)
{
	if (s[vexp->i] == '\'')
	{
		if (vexp->in_double)
			result[vexp->res_i++] = s[vexp->i];
		else
			vexp->in_single = !(vexp->in_single);
	}
	else if (s[vexp->i] == '\"')
	{
		if (vexp->in_single)
			result[(vexp->res_i)++] = s[vexp->i];
		else
			vexp->in_double = !(vexp->in_double);
	}
	vexp->i++;
}

static void	handle_exp(t_exp *vexp, char *res, t_vars *vars, t_info *info)
{
	char	*var_name;
	t_vars	*var; //Not sure if I still have to free this 

	vexp->i++;
	if (vexp->s[vexp->i] && vexp->s[vexp->i] == '?')
	{
		put_exitstatus(&res, info, &(vexp->res_i));
		vexp->i++;
	}
	else if (vexp->s[vexp->i] && (ft_isalpha(vexp->s[vexp->i])
			|| vexp->s[vexp->i] == '_'))
	{
		var_name = get_var_name(vexp->s, (vexp->i) - 1);
		var = find_vars(vars, var_name);
		if (var)
			put_var(&res, var->value, &(vexp->res_i));
		else
			put_var(&res, "", &(vexp->res_i));
		vexp->i += ft_strlen(var_name);
		free(var_name);
	}
	else
		res[vexp->res_i++] = '$';
}

/*****************************************************************************
 * Builds a new string by expanding variables and exit status 
 * 
 * Expands everything that is not in single quotes
******************************************************************************/
char	*expand_qstring(char *s, t_vars *vars, t_info *info)
{
	char	*result;
	int		len;
	t_exp	*vexp;

	if (!s)
		return (NULL);
	len = qstr_exp_len(s, vars, info);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	vexp = init_var_exp(s);
	if (!vexp)
		return (NULL);
	while (s[vexp->i])
	{
		if (s[vexp->i] == '\'' || s[vexp->i] == '\"')
			handle_quotes(result, vexp, s);
		else if (!(vexp->in_single) && s[vexp->i] == '$')
			handle_exp(vexp, result, vars, info);
		else
			result[(vexp->res_i)++] = s[vexp->i++];
	}
	return (result[(vexp->res_i)] = '\0', free(vexp->s), free(vexp), result);
}
