/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 11:27:48 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/12 16:42:02 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static void	print_export(t_vars	*temp)
{
	while (temp)
	{
		if ((!temp->value || ft_strlen(temp->value) == 0)
			&& temp->exported == 1)
			ft_printf("declare -x %s\n", temp->name);
		else if (temp->value && temp->exported == 1)
			ft_printf("declare -x %s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

static int	validate_var_name(char *var_name)
{
	if (ft_isalpha(var_name[0]) == 1 || var_name[0] == '_')
		return (0);
	else
		return (1);
}

void	set_exp_value(t_vars *temp, char *var_value)
{
	temp->exported = 1;
	temp->hidden = 0;
	if (var_value)
	{
		if (temp->value)
			free(temp->value);
		temp->value = ft_strdup(var_value);
	}
}

/******************************************************************************
*
*		This function will print out all the exported variables
*		If the value is null and it is exported 
*
******************************************************************************/
int	export_builtin(t_vars **head, char *var_name, char *var_value)
{
	t_vars	*temp;

	if (!var_name)
		return (temp = *head, print_export(temp), 0);
	else
	{
		if (validate_var_name(var_name) == 0)
		{
			temp = find_vars(*head, var_name);
			if (temp)
			{
				set_exp_value(temp, var_value);
				return (0);
			}
			else
				return (add_var(head, var_name, var_value, 1), 0);
		}
		else
			return (ft_printf("`%s': not a valid identifier\n", var_name), 1);
	}
}
