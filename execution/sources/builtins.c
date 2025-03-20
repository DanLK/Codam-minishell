/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:27:48 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/20 17:15:18 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_builtin(void)
{
}

/******************************************************************************
	
	Very barebones echo. so far it prints the text after echo with either a new 
	line or not based on the -n flag.
	
*******************************************************************************
	
	SOME TO DO

	-handle single and double quotes (they are ignored but affect expansion) ⍻
	-ignore backslashes ✔
	-multiple spaces are collapsed into one if not between quotes ✔
	-multiple spaces are not ignored if between quotes
	-ignore empty variables
	-double dash (--) makes echo ignore potential flags (ex: -n)
	
******************************************************************************/
static void	echo_printing(char *string, int i)
{
	while (string[i] != '\0')
	{
		if (string[i] == 34 || string[i] == 39 || string[i] == 92)
			i++;
		else if (string[i] == 32 && string[i + 1] == 32)
		{
			ft_printf("%c", string[i]);
			i++;
			while (string[i] == 32)
				i++;
		}
		else
		{
			ft_printf("%c", string[i]);
			i++;
		}
	}
}

void	echo_builtin(char *string)
{
	int	i;

	i = 5;
	if (string[5] == '-' && string[6] == 'n')
	{
		i = 7;
		echo_printing(string, i);
	}
	else
	{
		echo_printing(string, i);
		ft_printf("\n");
	}
}

/******************************************************************************
	
	-Currently this function simply displays the current working directory if 
	it detects that the user typed pwd
	
	-getcwd gives you the current working directory when given a buffer and 
	size
	
******************************************************************************/
void	pwd_builtin(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = getcwd(buff, PATH_MAX + 1);
	if (current_directory != NULL)
		ft_printf("%s\n", current_directory);
}

void	cd_builtin(void)
{
}
