/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 11:27:48 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/19 11:50:16 by dloustal      ########   odam.nl         */
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
	int	i;

	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (1);
	i = 1;
	while (var_name[i] && (ft_isalnum(var_name[i]) || var_name[i] == '_'))
		i++;
	if (!var_name[i])
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
		{
			write(STDERR_FILENO, "Minishell: ", 11);
			write(STDERR_FILENO, var_name, ft_strlen(var_name));
			write(STDERR_FILENO, ": not a valid identifier\n", 25);
			return (1);
		}
	}
}
