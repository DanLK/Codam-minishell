/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:50:04 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/02 12:21:25 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/******************************************************************************
*	
*	Very barebones echo. so far it prints the text after echo with either a new 
*	line or not based on the -n flag.
*
*	32 = SPACE
*	34 = "
*	39 = '
*	92 = \
*
*	SOME TO DO
*
*	-handle single and double quotes (they are ignored but affect expansion) ⍻
*	-ignore backslashes ✔
*	-multiple spaces are collapsed into one if not between quotes ✔
*	-multiple spaces are not ignored if between quotes
*	-ignore empty variables
*	-double dash (--) makes echo ignore potential flags (ex: -n)
*	
******************************************************************************/
static void	echo_printing(char **tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i])
	{
		if (tokens[i][j] == ' ' && tokens[i][j + 1] == ' ')
		{
			ft_putstr_fd(tokens[i], 1);
			while (tokens[i][j] == ' ')
				j++;
		}
		else
		{
			ft_putstr_fd(tokens[i], 1);
			ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

/******************************************************************************
*
*		-This function first checks if echo was passed with no extra arguments
*		 and if thats true it prints a new line.
*		-If echo ws passed with the flag -n it then checks if there is nothing
*		 after that and if its true it gives the prompt
*		 back
*		-If echo is passed with text, it calls the echo_printing function
*		
******************************************************************************/
int	echo_builtin(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens[0])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (ft_strcmp(tokens[0], "-n") == 0)
	{
		i = 1;
		while (tokens[i] && ft_strcmp(tokens[i], "-n") == 0)
			i++;
		if (!tokens[i])
			return (0);
		echo_printing(tokens, i);
	}
	else
	{
		i = 0;
		echo_printing(tokens, i);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

/******************************************************************************
* 
*	-This function prints all the environment variables stored in t_vars list.
*	-Will be called by the env command.
*	-Can be used to see what is currently stored in all the variables.
*
*	EDGE CASES DONE :
*	-env won't print variables with no value attached to them
*
******************************************************************************/
int	env_builtin(t_vars *head)
{
	while (head)
	{
		if (head->value && head->name && head->hidden == 0
			&& head->exported == 1)
			ft_printf("%s=%s\n",
				head->name, head->value, head->exported, head->hidden);
		head = head->next;
	}
	return (0);
}

/******************************************************************************
*
*	-This function will delete the node where the var_name is found
*
******************************************************************************/
int	unset_builtin(t_vars **head, char *var_name)
{
	t_vars	*current;
	t_vars	*previous;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (current->name && ft_strcmp((current)->name, var_name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*head = current->next;
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

/******************************************************************************
*	
*	-Currently this function simply displays the current working directory if 
*	it detects that the user typed pwd
*	
*	-getcwd gives you the current working directory when given a buffer and 
*	size
*	
******************************************************************************/
int	pwd_builtin(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = getcwd(buff, PATH_MAX + 1);
	if (!current_directory)
		return (1);
	ft_printf("%s\n", current_directory);
	return (0);
}
