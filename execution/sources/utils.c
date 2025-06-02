/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:42:47 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/02 16:11:40 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

/******************************************************************************
*
*	-Function that frees an array of memory
*
******************************************************************************/
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/******************************************************************************
*
*	-This function converts the linked list t_vars to a **env_copy so it can be
*	 passed as an argument for child processes.
*	
*	HOW IT WORKS :
*	- We figure out how many nodes the t_vars list has
*	-After that we can assign memory to our env_copy array which will store the
*	 elements
*	-We loop through the list again and copy all the varaibles which are 
*	 exported
*	 (when current->exported=1)
*	-The loop stops when current->next is NULL meaning that's the last node
*
******************************************************************************/
char	**convert_env(t_vars *head)
{
	t_vars	*current;
	int		i;
	char	**env_copy;
	char	*temp;

	i = 0;
	current = head;
	while (current)
	{
		if (current->exported == 1)
			i++;
		current = current->next;
	}
	env_copy = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (current)
	{
		if (current->exported == 1)
		{
			if (!current->value)
			{
				env_copy[i] = ft_strdup(current->name);
				if (!env_copy[i])
					return (free_array(env_copy), NULL);
			}
			else
			{
				temp = ft_strjoin(current->name, "=");
				env_copy[i] = ft_strjoin(temp, current->value);
				free(temp);
			}
			i++;
		}
		current = current->next;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

/******************************************************************************
*
*	-This function will turn on a sort of debug mode where you can print debug
*	 messages throught the code.
*	-They are turned on by changing the values to 1 and off on 0
*	-To not be cluttured with messages, I made it so we can each turn on our
*	 our messages by passing a char r(oberto) or d(aniela). We can turn off the
*	 the other ones prints by turning the values (val_d or val_r) to 0.
*	 this way it will be easier to debug each of our own code.
*
******************************************************************************/

void	free_vars(t_vars *head)
{
	t_vars	*current;

	while (head)
	{
		current = head;
		head = head->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
	}
}
