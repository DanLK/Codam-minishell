/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 11:42:47 by rojornod      #+#    #+#                 */
/*   Updated: 2025/04/17 16:07:57 by dloustal      ########   odam.nl         */
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
*	-Small function that shows the pid of the current process
*
******************************************************************************/
void	show_pid(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("pid: [%d]\n", pid);
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
*	-We loop through the list again and copy all the varaibles which are exported
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
	env_copy = malloc((i + 1) * sizeof(char *)); //malloc is used here. needs to be free
	current = head;
	i = 0;
	while (current)
	{
		if (current->exported == 1)
		{
			if (!current->value)
				env_copy[i] = ft_strdup(current->name); //malloc is used here, needs to be free
			else
			{
				temp = ft_strjoin(current->name, "="); //malloc is used here, needs to be free
				env_copy[i] = ft_strjoin(temp, current->value); //malloc is used here. needs to be free
			}
			i++;
		}
		current = current->next;
	}
	env_copy[i] = NULL;
	//ft_printf("there are [%d] elements in the env list\n", i);
	//ft_printf("first element of array is [%s]\n", env_copy[0]);
	return (env_copy);
}

void	debug_print(char *debug_message)
{
	int	val;
	
	val = 0;
	if (val == 1)
		ft_printf("[%s]\n", debug_message);
}

