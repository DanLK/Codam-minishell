/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/22 11:38:05 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_vars	initialize_data(void)
// {
// 	t_vars *head;
// 	ft_printf("initializing date\n");
// 	// head = malloc(sizeof(t_vars));
// 	// if (!head)
// 	// {
// 	// 	perror("malloc on vars initialization");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	head->name = NULL;
// 	head->value = NULL;
// 	head->exported = 0;
// 	head->hidden = 0;
// 	head->next = NULL;
// 	ft_printf("date initialized");
// 	return (NULL);
// }

t_vars	*initialize_data(void)
{
	t_vars	*head;
	debug_print("initializing extra", 'r');

	head = malloc(sizeof(t_vars));
	debug_print("malloced struct", 'r');
	if (!head)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

t_exe_info	*initialize_info(void)
{
	t_exe_info	*info;
	debug_print("initializing extra", 'r');

	info = malloc(sizeof(t_exe_info));
	debug_print("malloced struct", 'r');
	if (!info)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

char	*get_home_dir(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = NULL;
	if (!getcwd(buff, PATH_MAX + 1))
		return (NULL);
	current_directory = ft_strdup(buff);
	// ft_printf("assigned directory\n");
	// ft_printf("exiting functions...\n");
	// ft_printf("cd is %s\n", current_directory);
	return (current_directory);
}

/******************************************************************************
*
*	-Creates the file .shell_history which will store all 
*	commands typed by user
*	
*	-The file is created in the root directory
*	
******************************************************************************/
void	create_history_file(void)
{
	int	fd;

	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	// ft_printf("history file created\n");
	close(fd);
}

/******************************************************************************
*
*	-This function takes the input from the command line and appends it to the 
*	.shell_history file
*	
******************************************************************************/
void	write_history_file(char *read)
{
	int		fd;
	int		i;
	//char	*number;
	
	i = 0;
	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (read[i] != '\0')
		i++;
	write(fd, read, i);
	write(fd, "\n", 1);
}

void	print_environment(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

